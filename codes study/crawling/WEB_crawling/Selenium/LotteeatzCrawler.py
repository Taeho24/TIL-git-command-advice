# lotteeatz.com 25-10-18 매장 정보 크롤링
from bs4 import BeautifulSoup
import urllib.request
import pandas as pd
import datetime
from selenium import webdriver
import time
#[CODE 1]
def Crawling_store(result):
    Crawling_URL = "https://www.lotteeatz.com/searchStore?divcd=10"
    wd = webdriver.Chrome()
    
    
    for i in range(1, 200): #modified 매장 수만큼 반복
        wd.get(Crawling_URL)
        time.sleep(1) #웹페이지 연결할 동안 1초 대기
        try:
            wd.execute_script("showStoreInfo(%d, 10)" % (i + 11000))
            time.sleep(1) #스크립트 실행할 동안 1초 대기
            html = wd.page_source
            soup = BeautifulSoup(html, 'html.parser')
            store_name_span = soup.select("div.tit-lg > span.store-name")
            store_name = store_name_span[0].string
            print(store_name) #매장 이름 출력하기
            store_address_info = soup.select("div.address-copy-wrap > span.info-address")
            store_address = store_address_info[0].string
            store_phone_span = soup.select("div.store-with-wrap > div.left-box > a.btn-sm > span.text")
            store_phone = store_phone_span[0].string
            result.append([store_name]+[store_address]+[store_phone])
        except Exception as e:
            # logging.exception(f"예외 발생: {e}")
            # print(f"오류 발생: {e} >>> continue")
            continue
    return
#[CODE 0]
def main():
    result = []
    print('LotteEatz store crawling >>>>>>>>>>>>>>>>>>>>>>>>\n')
    Crawling_store(result) #[CODE 1]
    SAP_tbl = pd.DataFrame(result, columns = ('store', 'address', 'phone'))
    SAP_tbl.to_csv('C:/Temp/LotteEatz0.csv', encoding = 'cp949', mode = 'w', index = True)

if __name__ == '__main__':
    main()
