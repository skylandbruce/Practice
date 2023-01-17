
cash_50th=50000
cash_10th=10000
cash_1000=1000
cash_100=100
cash_50=50
cash_10=10

print("Total Money?:")
money_total=int(input())
#count_50tsd=money_total/cash_50th
#rest_50tsd=money_total%cash_50th

rest_money=money_total
count_50tsd=0
count_10tsd=0
count_1000=0
count_100=0
count_10=0

while True:

    if rest_money >= cash_50th:
        count_50tsd=money_total/cash_50th
        rest_money=money_total%cash_50th
    elif rest_money >= cash_10th:
        count_10tsd = rest_money / cash_10th
        rest_money = money_total % cash_10th
    elif rest_money >= cash_1000:
        count_1000 = rest_money / cash_1000
        rest_money = money_total % cash_1000
    elif rest_money >= cash_100:
        count_100 = rest_money / cash_100
        rest_money = money_total % cash_100
    elif rest_money >= cash_10:
        count_10 = rest_money / cash_10
        rest_money = money_total % cash_10

        break
    else:
        break
#print("5만원권:%d" %count_50tsd)
print("5만원권:%d 1만원권:%d 천원권:%d 100원:%d 10원:%d" %(count_50tsd, count_10tsd, count_1000, count_100, count_10))

"""
print("5만원권:%d" %count_50tsd)
print("5만원권:%d" %count_10tsd)
print("5만원권:%d" %count_1000)
print("5만원권:%d" %count_100)
print("5만원권:%d" %count_10)
"""