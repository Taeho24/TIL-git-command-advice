import os
import sys
import urllib.request
import datetime
import time
import json

import naver_search

client_id = "YOUR_CLIENT_ID"
client_secret = "YOUR_CLIENT_SECRET"

def main():
    node = 'news' #크롤링할 대상
    srcText = input('검색어를 입력하세요:')
    cnt = 0
    jsonResult = []
    jsonResponse = naver_search.getNaverSearch(node, srcText, 1, 100) #[CODE 2]
    total = jsonResponse['total']
    while ((jsonResponse != None) and (jsonResponse['display'] != 0)):
        for post in jsonResponse['items']:
            cnt += 1
            naver_search.getPostData(post, jsonResult, cnt) #[CODE 3]
        start = jsonResponse['start'] + jsonResponse['display']
        jsonResponse = naver_search.getNaverSearch(node, srcText, start, 100) #[CODE 2]
    print('전체 검색 : %d 건' %total)
    with open('%s_naver_%s.json' % (srcText, node), 'w', encoding='utf8') as outfile:
        jsonFile = json.dumps(jsonResult, indent = 4, sort_keys = True, ensure_ascii = False)
        outfile.write(jsonFile)
    print("가져온 데이터 : %d 건" %(cnt))
    print('%s_naver_%s.json SAVED' % (srcText, node))
if __name__ == '__main__':
    main()
