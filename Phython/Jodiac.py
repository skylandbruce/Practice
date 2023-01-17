"""
연도를 입력하면 각 연도의 띠를 출력
"""
jodic_dic={0:'원숭이',1:'닭',2:'개',3:'돼지',4:'쥐',5:'소',6:'범',7:'토끼',8:'용',9:'뱀',10:'말',11:'양'}
year_max=12
print("연도 입력:")
year_curr=int(input())
n_jodiac=year_curr%year_max
str_jodiac=jodic_dic[n_jodiac]
print("{0} 년의 띠:{1}".format(year_curr, str_jodiac))
