"""
Number=[1,2,3,6,7,8,9,3,4,,6,7,8] 입력
각각의 숫자가 몇번 등장 하는지
"""
Number=[1,2,3,6,7,8,9,3,4,6,7,8]
num_curr=0
num_count=0
known_list=[]
for i in Number:
    num_curr=Number[i]

    if known_list.count(num_curr) == 0:
        known_list.append(num_curr)
        num_count=Number.count(num_curr)
        print(f"{num_curr} 의 개수:{num_count}")