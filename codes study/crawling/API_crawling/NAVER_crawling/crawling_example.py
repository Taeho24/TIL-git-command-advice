# (https://developers.naver.com/docs/common/openapiguide/)
# 네이버 카페 API예제는 카페 가입과 카페 글쓰기 및 multipart 이미지 첨부 예제로 구성되어 있습니다.
""" 
# 네이버 API 예제 - 카페 가입하기
import os
import sys
import urllib.request
token = "YOUR_ACCESS_TOKEN"
header = "Bearer " + token # Bearer 다음에 공백 추가
clubid = "CLUB_ID" # 카페의 고유 ID값
url = "https://openapi.naver.com/v1/cafe/" + clubid + "/members"
nickname = urllib.parse.quote("Python")
data = "nickname=" + nickname
request = urllib.request.Request(url, data=data.encode("utf-8"))
request.add_header("Authorization", header)
response = urllib.request.urlopen(request)
rescode = response.getcode()
if(rescode==200):
    response_body = response.read()
    print(response_body.decode('utf-8'))
else:
    print("Error Code:" + rescode)


# 네이버 카페 Open API 예제 - 글쓰기
import os
import sys
import urllib.request
token = "YOUR_ACCESS_TOKEN"
header = "Bearer " + token # Bearer 다음에 공백 추가
clubid = "CLUB_ID" # 카페의 고유 ID값
menuid = "MENU_ID" # (상품게시판은 입력 불가)
url = "https://openapi.naver.com/v1/cafe/" + clubid + "/menu/" + menuid + "/articles"
subject = urllib.parse.quote("[subject] 네이버 Cafe api Test Python")
content = urllib.parse.quote("[content] 네이버 Cafe api Test Python")
data = "subject=" + subject + "&content=" + content
request = urllib.request.Request(url, data=data.encode("utf-8"))
request.add_header("Authorization", header)
response = urllib.request.urlopen(request)
rescode = response.getcode()
if(rescode==200):
    response_body = response.read()
    print(response_body.decode('utf-8'))
else:
    print("Error Code:" + rescode)


# cafe mulipart upload - python
import os
import sys
import requests
import urllib.request


token = "YOUR_ACCESS_TOKEN"
header = "Bearer " + token # Bearer 다음에 공백 추가
clubid = "YOUR_CAFE_ID" # 카페의 고유 ID값
menuid = "YOUR_CAFE_BBS_ID"  # (상품게시판은 입력 불가)
url = "https://openapi.naver.com/v1/cafe/" + clubid + "/menu/" + menuid + "/articles"


subject = urllib.parse.quote("네이버 Cafe api Test Python")
content = urllib.parse.quote("<font color='red'>python multi-part</font>로 첨부한 글입니다. <br> python 이미지 첨부 <br>")
data = {'subject': subject, 'content': content}
files = [
    ('image', ('YOUR_FILE_1', open('YOUR_FILE_1', 'rb'), 'image/jpeg', {'Expires': '0'})),
    ('image', ('YOUR_FILE_2', open('YOUR_FILE_2', 'rb'), 'image/jpeg', {'Expires': '0'}))
    ]


headers = {'Authorization': header }
response = requests.post(url, headers=headers, data=data, files=files)


rescode = response.status_code
if(rescode==200):
    print (response.text)
else:
    print(rescode)
"""
