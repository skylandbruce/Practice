select *
from maker,product
order by m_idx asc;

select *
from product,maker
order by p_idx asc;

# maker01 이 만드는 상품 리스트
select p_name
from maker, product
where m_name='maker01'   and maker.m_code=product.m_code;

# maker01 이 만든 상품
select p_name
from product 
where m_code = (select m_code from maker where m_name='maker01');

# silver grade seller 가 판매한 p_name 과 o_count  (select s_code from seller where s_grade='silver')결과가 한개일 때
select p_name, o_count 
from product, orders
where  product.s_code=(select s_code from seller where s_grade='silver') and product.p_code=orders.p_code;

# silver grade seller 가 판매한 p_name 과 o_count  (select s_code from seller where s_grade='silver') 결과가 두개 이상 일 때
select c_id, p_name, o_count 
from product, orders
where product.s_code in (select s_code from seller where s_grade='gold') and product.p_code=orders.p_code;

# silver grade seller 가 판매한 p_name 과 o_count  (select s_code from seller where s_grade='silver')결과가 두개 이상 일 때
select c_id, p_name, o_count 
from product, orders, seller
where seller.s_grade='silver' and orders.p_code=product.p_code and seller.s_code=product.s_code;
