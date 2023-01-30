-- SELECT
# 1.주문 테이블에서 제품별(그룹) 판매수량을 검색하라.
select p_code, sum(o_count) as 판매수량
from orders
group by p_code order by p_code;

# 2.주문 테이블에서 제품별로 가장 많이 주문된 오더를 검색하라
select p_code, max(o_count)
from orders
group by p_code order by p_code;

# 3.주문 테이블, 제품 테이블에서 제품별(그룹) 판매수량을 검색하여, 제품 이름과 총판매수량을 출력하라.
select p_name, sum(o_count) as 판매수량
from orders, product
where orders.p_code=product.p_code group by orders.p_code
order by product.p_code;

# 4.제조업체별로 제조한 제품의 개수를 검색하라.
select p_maker, count(p_stock)
from product
group by p_maker;

# 5.제조업체별로 제조한 제품의 개수와 제품중 가장 비싼 단가를 검색하되, 제품명, 제조업체, 제품수, 최고단가를 출력하라
select p_name, p_maker, p_ucost
from product
where p_ucost=max(p_ucost) ;

# 6. 나이가 50세 이상인 고객이 주문한 제품을 검색하여 주문제품과, 주문수량을 출력하라.
select p_code, o_count
from customer,orders
where customer.c_age>30 && customer.c_id=orders.c_id;


#7. 나이가 50세 이상인 고객이 주문한 제품을 검색하여 주문제품 코드와 주문제품의 이름, 주문수량을 출력하라.
select product.p_code, p_name, sum(o_count)
from orders, product, customer
where  orders.p_code=product.p_code && (customer.c_age>30) 
group by product.p_code;

#8. 나이가 50세 이상인 고객이 주문한 제품을 검색하여 주문제품별로 제품코드와 주문제품의 이름, 주문수량, 주문액합계를 출력하라.
select orders.p_code, p_name, sum(o_count), (sum(o_count)*p_ucost)
from orders, product, customer
where  orders.p_code=product.p_code && (customer.c_age>30) 
group by product.p_code
order by product.p_code;

#9. 주문 테이블에서 가장 많이 팔린 제품을 찾아서, 그 제품의 판매금액 합계를 구하라
select orders.p_code, p_ucost*count(o_count)
from orders, product
where product.p_code=(select orders.p_code from orders where max(orders.o_count)=orders.o_count)
group by orders.p_code;

#Professor ansser
select orders.p_code, product.p_ucost*sum(orders.o_count)
from product, orders
where product.p_code=orders.p_code
group by orders.p_code
order by product.p_ucost*sum(orders.o_count);

# 주문 테이블의 고객코드에 ㅎ당하는 고객이름을 찾아, 주문번호, 고객코드, 고객이름, 주문날짜를 출력하라
select o_idx, c_id, c_name, o_date
from orders, customer
where orders.c_id=(select orders.c_id from orders where orders.c_id=20);

select o_idx, customer.c_id, c_name, o_date
from orders, customer
where customer.c_id=orders.c_id;


# 주문 테이블의 고객코드에 ㅎ당하는 고객이름을 찾아, 주문번호, 고객코드, 고객이름, 주문날짜, 주문수량을 출력하라
select o_idx, customer.c_id, c_name, o_date, orders.o_count 
from orders, customer
where customer.c_id=orders.c_id;


# 주문 테이블의 고객코드에 ㅎ당하는 고객이름을 찾아, 주문번호, 고객코드, 고객이름, 주문제품, 주문수량, 주문단가를 출력하라
select o_idx, customer.c_id, c_name, orders.p_code, orders.o_count, product.p_ucost 
from orders, customer, product
where customer.c_id=orders.c_id ;

# 주문 테이블의 고객코드에 ㅎ당하는 고객이름을 찾아, 주문번호, 고객코드, 고객이름, 주문제품, 주문금액을 출력하라

# 주문 테이블의 고객코드에 ㅎ당하는 고객이름을 찾아, 주문번호, 고객코드, 고객이름, 총주문수량을 출력하라

