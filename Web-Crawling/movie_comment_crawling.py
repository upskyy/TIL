import requests
from bs4 import BeautifulSoup


def movie_comment(url) :
    html = requests.get(url)
    soup = BeautifulSoup(html.text, 'html.parser')

    for item, i in zip(soup.select(".score_result .score_reple"), range(1,11)):
        result = item.text
        result = result.replace("관람객",'')
        result = result.replace('\t','')
        result = result.replace('\r','')
        result = result.replace('\n','')
        print(result)
    

movie_comment("https://movie.naver.com/movie/bi/mi/pointWriteFormList.nhn?code=136990&type=after&onlyActualPointYn=Y&isActualPointWriteExecute=false&isMileageSubscriptionAlready=false&isMileageSubscriptionReject=false&page=1")


# select 할때
# class 찾을 땐 .땡땡땡 (위에 보면 result 다음에 띄고 . 이다) 저거 붙이면 결과 안나옴
# id 찾을 땐 #으로 찾는다.

# find 할 때
# select랑 용도는 동일하지만 경로를 써주어야 한다.
# find('span',{'class': 'todaytemp'}).text

# find, findAll, select_one, select