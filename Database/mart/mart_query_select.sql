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


