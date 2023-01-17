"""
패밀리 레스토랑에 테이블이 여러개 있다
최소 앉을 인원은 2명, 최대 앉을 인원은 10명이다

100명의 사람이 테이블에 앉을수 있는 모든 패턴
"""
num_gest=10
cap_table_min=2
cap_table_max=10
num_rest=0
chair_rest=0
str_chair=""
str_rest=""
for i in range(2,11):
    num_chair=num_gest/i
    num_rest=num_gest%i
    str_chair="%d명 "%i
    str_chair=str_chair*int(num_chair)
    if(num_rest>0):
        str_rest="%d명"%num_rest
        str_chair+=str_rest
    if i <= num_gest:
        print(f"배석:{str_chair}")
