"""
1부터 하나씩 증가 시켜서 더라히를 할 때
몇번 까지 더하기를 하면 1000원을 넘는지?
"""
MAX_NUM=1000
cnt=0
sum=0
while sum<MAX_NUM:
    cnt+=1
    sum+=cnt

print(f"{cnt} 번 더하기")