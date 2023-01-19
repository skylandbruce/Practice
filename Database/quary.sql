
-- c_id 가 banana 인 고객이 구매한 상품을 부질의문으로 
select p_name, p_maker 
from product
where p_code NOT IN(select p_code from orders where c_id='banana');

-- c_id 가 banana 인 고객이 구매한 상품을 join으로
select product.p_name, product.p_maker
from product, orders
where orders.c_id='banana'and product.p_code=orders.p_code
	group by product.p_code;

select product.p_name, product.p_maker
from product, orders
where product.p_code=orders.p_code
	group by product.p_code;


select *
from product, orders

