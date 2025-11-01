// .env
NAVER_CLEINT_ID = 
NAVER_CLIENT_SECRET = 
NAVER_REDIRECT_URI = 
NAVER_STATE =
 

// social.router.js
require("dotenv").config();
const express = require('express');
const router = express.Router();

const SoicalController = require('../controllers/social');
const soicalController = new SoicalController();

router.post('/naver/isNaver', soicalController.isNaver);

router.post('/naver/callback', soicalController.naver_callback);

module.exports = router;
 

// controllers/social.js

// const Acess_ = require('../models/access_token');
require("dotenv").config();
const SocialService = require("../services/social");

// 순서
// 1. 프론트에게 인가코드 받기
// 2. 받은 인가코드를 백이 kakao쪽에 token요청
// 3. token받은 걸로 유저 정보 체크 후 DB에 저장
// 4. DB에 저장 후 token을 다시 만들어서 프론트에게 보내기

class SoicalController {
  socialService = new SocialService();

  isNaver = async (req, res, next) => {
    try {
      // 프론에게 인가코드 받기
      const { code } = req.body;

      // console.log('인가 코드' + code);
      try {
        const isNaver = await this.socialService.isNaver(code)

        const findNaverUser = await this.socialService.findUser(
            isNaver
        );
        if (!findNaverUser) {
          res.status(200).json({ userId: isNaver });
        } else {
          const accessToken = await this.socialService.accessToken(isNaver);
          const refresh_token = await this.socialService.refreshToken();

          // refreshtoken DB에 업데이트
          await this.socialService.updateRefresh(isNaver, refresh_token);

          res.status(201).json({
            accessToken: `Bearer ${accessToken}`,
            refresh_token: `Bearer ${refresh_token}`,
          });
        }
      } catch (error) {
        console.log(error);
        res.send(error);
      }
    } catch (err) {
      res.status(400).send({
        success: false,
        errorMessage: err.message,
        message: "에러가 발생했습니다.",
      });
    }
  };

  naver_callback = async (req, res, next) => {
    try {
      // 프론에게 인가코드 받기
      const { userId, nickName, myPlace, age, gender, likeGame } = req.body;

      // 회원가입에 필요한 내용 싹다 넣기 -> kakao에 있는 schema를 users로 변경
      // console.log(nickName)
      // console.log(address)
      try {
        await this.socialService.createUser(
            userId,
            nickName,
            myPlace,
            age,
            gender,
            likeGame
        );

        const accessToken = await this.socialService.accessToken(userId);
        const refresh_token = await this.socialService.refreshToken();

        await this.socialService.updateRefresh(userId, refresh_token);

        res.status(201).json({
          accessToken: `Bearer ${accessToken}`,
          refresh_token: `Bearer ${refresh_token}`,
        });
      } catch (error) {
        console.log(error);
        res.status(409).json({message : error.message, statusCode : error.status});
      }
    } catch (err) {
      res.status(400).send({
        success: false,
        errorMessage: err.message,
        message: "에러가 발생했습니다.",
      });
    }
  };
}

module.exports = SoicalController;
 

// services/social.js
require("dotenv").config();
const axios = require("axios");
const jwt = require("jsonwebtoken");
const SocialRepository = require('../repositories/social')

const NAVER_CLIENT_ID = process.env.NAVER_CLIENT_ID;
const NAVER_REDIRECT_URL = process.env.NAVER_REDIRECT_URL;
const NAVER_CLIENT_SECRET = process.env.NAVER_CLIENT_SECRET;
const NAVER_STATE = process.env.NAVER_STATE;

class SocialService {
    socialRepository = new SocialRepository();

    isNaver = async (code) => {
        const {data} = await axios.post(
            `https://nid.naver.com/oauth2.0/token?grant_type=authorization_code&client_id=${NAVER_CLIENT_ID}&client_secret=${NAVER_CLIENT_SECRET}&code=${code}&state=${NAVER_STATE}`,
            {
                headers: {
                    "Content-type": "application/x-www-form-urlencoded;charset=utf-8",
                },
            }
        );

        let access_token = data.access_token;

        const naverUser = await axios("https://openapi.naver.com/v1/nid/me", {
                headers: {
                    Authorization: `Bearer ${access_token}`
                },
            });
        return naverUser.data.id
    }


    createUser = async (userId, nickName, myPlace, age, gender, likeGame, admin) => {
        const isSameNickname = await this.socialRepository.findUserAccountNick(nickName);

        // 유저 nickname 중복 검사
        if (isSameNickname) {
            const err = new Error(`UserService Error`);
            err.status = 409;
            err.message = "이미 가입된 닉네임이 존재합니다.";
            throw err;
        }

        const createUser = await this.socialRepository.createUser(userId, nickName, myPlace, age, gender, likeGame, admin);
        return createUser;
    }

    findUser = async (userId) => {
        const findUser = await this.socialRepository.findUser(userId)
        return findUser;
    }

    updateRefresh = async (userId, refresh_token) => {
        const updateRefresh = await this.socialRepository.updateRefresh(userId, refresh_token);
        return updateRefresh;
    }

    accessToken = async (userId) => {
        const accessToken = jwt.sign(
            {userId: userId},
            process.env.DB_SECRET_KEY,
            {
                expiresIn: "5m",
            }
        );
        return accessToken;
    }

    refreshToken = async () => {
        const refreshToken = jwt.sign({}, process.env.DB_SECRET_KEY, {
            expiresIn: "2h",
        });
        return refreshToken;
    }
}

module.exports = SocialService;
