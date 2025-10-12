# (http://www.data.go.kr)
# 한국문화관광연구원_출입국관광통계서비스
# 입국자 수를 json & csv 파일 저장 & 라인차트표시

import os
import sys
import urllib.request
import datetime
import time
import json
import pandas as pd

import matplotlib.pyplot as plt
import matplotlib
from matplotlib import font_manager, rc

ServiceKey = "[인증키]"

#[CODE 1]
def getRequestUrl(url):
    req = urllib.request.Request(url)
    try:
        response = urllib.request.urlopen(req)
        if response.getcode() == 200:
            print("[%s] Url Request Success" % datetime.datetime.now())
            return response.read().decode('utf-8')
    except Exception as e:
        print(e)
        print("[%s] Error for URL : %s" % (datetime.datetime.now(), url))
        return None
#[CODE 2]
def getTourismStatsItem(yyyymm, national_code, ed_cd):
    service_url = "http://openapi.tour.go.kr/openapi/service/EdrcntTourismStatsService/getEdrcntTourismStatsList"
    parameters = "?_type=json&serviceKey=" + ServiceKey #인증키
    parameters += "&YM=" + yyyymm
    parameters += "&NAT_CD=" + national_code
    parameters += "&ED_CD=" + ed_cd
    url = service_url + parameters
    
    retData = getRequestUrl(url) #[CODE 1]
    
    if (retData == None):
        return None
    else:
        return json.loads(retData)
#[CODE 3]
def getTourismStatsService(nat_cd, ed_cd, nStartYear, nEndYear):
    jsonResult = []
    result = []
    natName=''
    dataEND = "{0}{1:0>2}".format(str(nEndYear), str(12)) #데이터 끝 초기화
    isDataEnd = 0 #데이터 끝 확인용 flag 초기화 
    for year in range(nStartYear, nEndYear+1): 
        for month in range(1, 13):
            if(isDataEnd == 1): break #데이터 끝 flag 설정되어있으면 작업 중지.
            yyyymm = "{0}{1:0>2}".format(str(year), str(month)) 
            jsonData = getTourismStatsItem(yyyymm, nat_cd, ed_cd) #[CODE 2] 
            if (jsonData['response']['header']['resultMsg'] == 'OK'): 
                if jsonData['response']['body']['items'] == '': 
                    isDataEnd = 1 #데이터 끝 flag 설정
                    dataEND = "{0}{1:0>2}".format(str(year), str(month-1))
                    print("데이터 없음.... \n 제공되는 통계 데이터는 %s년 %s월까지입니다." %(str(year), str(month-1))) 
                    break
                print (json.dumps(jsonData, indent=4, sort_keys=True, ensure_ascii=False)) # 데이터정보확인을 위한 print
                natName = jsonData['response']['body']['items']['item']['natKorNm']
                natName = natName.replace(' ', '') # 공백제거
                num = jsonData['response']['body']['items']['item']['num']
                ed = jsonData['response']['body']['items']['item']['ed']
                print('[ %s_%s : %s ]' %(natName, yyyymm, num))
                print('--------------------------------------------------------------') 
                jsonResult.append({'nat_name': natName, 'nat_cd': nat_cd, 'yyyymm': yyyymm, 'visit_cnt': num})
                result.append([natName, nat_cd, yyyymm, num])
    return (jsonResult, result, natName, ed, dataEND)

def convert_year(year_input):
    """한 자리나 두 자리 숫자를1900년대나 2000년대로 보정"""
    if 0 <= year_input <= 25:
        return 2000 + year_input
    if 25 < year_input <= 99:
        return 1900 + year_input
    return year_input

def get_valid_year_range():
    while True:
        try:
            nStartYear_raw = int(input('데이터를 몇 년부터 수집할까요? : '))
            nEndYear_raw = int(input('데이터를 몇 년까지 수집할까요? : '))

            nStartYear = convert_year(nStartYear_raw)
            nEndYear = convert_year(nEndYear_raw)
            
            if nStartYear < 0 or nEndYear < 0:
                print("error: 연도는 0 이상이어야 합니다.")
            elif nStartYear > nEndYear:
                print("error: 시작 연도는 종료 연도보다 작거나 같아야 합니다.")
            elif nStartYear > 9999 or nEndYear > 9999:
                print("error: 연도는 9999 이하로 입력해주세요.")
            else:
                return nStartYear, nEndYear

        except ValueError:
            print("error: 숫자만 입력해주세요.")

#[CODE 0]
def main():
    jsonResult = []
    result = []
    print("<< 국내 입국한 외국인의 통계 데이터를 수집합니다. >>")
    nat_cd = input('국가 코드를 입력하세요(중국: 112 / 일본: 130 / 미국: 275) : ')
    nStartYear, nEndYear = get_valid_year_range()
    print(f"{nStartYear}년부터 {nEndYear}년까지 데이터를 수집합니다.")
    
    ed_cd = "E" #E : 방한외래관광객, D : 해외 출국
    jsonResult, result, natName, ed, dataEND = getTourismStatsService(nat_cd, ed_cd, nStartYear, nEndYear) #[CODE 3]
    #파일저장 1 : json 파일
    with open('./%s_%s_%d_%s.json' % (natName, ed, nStartYear, dataEND), 'w', encoding = 'utf8') as outfile:
        jsonFile = json.dumps(jsonResult, indent = 4, sort_keys = True, ensure_ascii = False)
        outfile.write(jsonFile)
    #파일저장 2 : csv 파일
    columns = ["입국자국가", "국가코드", "입국연월", "입국자 수"]
    result_df = pd.DataFrame(result, columns = columns)
    result_df.to_csv('./%s_%s_%d_%s.csv' % (natName, ed, nStartYear, dataEND), index=False, encoding='cp949')

    cnVisit = []
    visitYM = []
    index = [] # 변수값
    i = 0
    for item in jsonResult:
        index.append(i)
        cnVisit.append(item['visit_cnt'])
        visitYM.append(item['yyyymm'])
        i += 1
    
    try:
    # 말굽폰트가 있는 경우
        font_path = 'c:/windows/fonts/malgun.ttf'
        font_name = font_manager.FontProperties(fname=font_path).get_name()
        matplotlib.rc('font', family=font_name)
        print(f"폰트 설정 완료: {font_name}")
    except Exception as e:
        print(f"한글 폰트를 설정할 수 없습니다. 기본 폰트를 사용합니다.\n{e}")
        matplotlib.rc('font', family='sans-serif')  # 대체 폰트 설정

    plt.xticks(index, visitYM, rotation=90) # x 변수값
    plt.plot(index, cnVisit, label=natName, color='blue', marker='o') # y 변수값
    plt.xlabel('입국연월') # x 변수명
    plt.ylabel('입국자 수') # y 변수명
    plt.title('입국연월별 국가별 입국자 수')
    plt.legend(loc='upper left')
    plt.grid(True)
    plt.tight_layout()  # 레이아웃 깨짐 방지
    plt.show()

if __name__ == '__main__':
    main()
