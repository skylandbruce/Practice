select *
from maker,product;
-- order by m_idx asc;

select *
from product,maker;
-- order by p_idx asc;

# maker01 이 만든 상품 리스트 INLINE
select p_name
from product 
where m_code = 
(select m_code from maker where m_name='maker01');

# gray grade seller 의 s_code 리스트
select s_code
from seller
where s_grade='gray';

# silver grade seller 의 s_code 리스트
select s_code
from seller
where s_grade='silver';

# gray grade seller 등급의 seller 코드인, s_code 가 납품한 상품의 p_code
# INLINE // Sub Query의 결과가 1개 일 때
select p_code
from product
where s_code=
(select s_code from seller where s_grade='gray'); 

#-------------------------------------------------
# silver grade seller 등급의 seller 코드인, s_code 가 납품한 상품의 p_code
# INLINE // Sub Query의 결과가 2개 이상일 때
select s_code, p_code
from product
where s_code
in (select s_code from seller where s_grade='silver'); 

# silver grade seller 등급의 seller 코드인, s_code 가 납품한 상품의 p_code
# JOIN // Sub Query의 결과가 2개 이상일 때
select product.s_code, p_code
from seller, product
where product.s_code
in (select s_code from seller where s_grade='silver')
and seller.s_code=product.s_code; 

#-------------------------------------------------
# silver grade seller 가 납품한 상품 중, 
# order tabale에 판매된 상품의 cid 와 p_code 와 o_count 부질의문 결과가 두개 이상 일 때
# INLINE 
select c_id, p_code, o_count 
from orders
where orders.p_code in
(select p_code from product where s_code in
(select s_code from seller where s_grade='silver'));

# silver grade seller 가 납품한 상품 중, 
# 판매된 상품의 cid 와 p_code 와 o_count
# JOIN 
select c_id, orders.p_code, o_count 
from product, orders, seller
where seller.s_grade='silver' and orders.p_code=product.p_code and seller.s_code=product.s_code;

#-------------------------------------------------
# gray grade seller 납품한 상품 중, 
# 판매된 상품의 p_name 과 o_count 		결과가 한개일 때
# 부분 INLINE
select p_name, o_count 
from product, orders
where  product.s_code = (select s_code from seller where s_grade='gray') and product.p_code=orders.p_code;

# gold grade seller 가 납품한 상품 중, 
# 판매된 상품의 고객ID(c_id) 상품이름(p_name) 과 o_count
# 부분 INLINE
select c_id, p_name, o_count
from product, orders
where product.s_code in 
(select s_code from seller where s_grade='gold') and product.p_code=orders.p_code;

# silver grade seller 가 납품한 상품 중, 
# 판매된 상품의 고객ID(c_id) 상품이름(p_name) 과 o_count 
# JOIN
select c_id, p_name, o_count 
from product, orders, seller
where seller.s_grade='silver' and orders.p_code=product.p_code and seller.s_code=product.s_code;

#-------------------------------------------------
# silver grade seller 가 납품한 상품 중, 
# 판매된 상품의 고객이름(c_name) 상품이름(p_name) 과 o_count 
# 부분 INLINE
select c_name, p_name, o_count 
from product, orders, customer
where product.s_code in (select s_code from seller where s_grade='silver') 
and orders.p_code=product.p_code and orders.c_id=customer.c_id;

# silver grade seller 가 납품한 상품 중, 
# 판매된 상품의 고객이름(c_name) 상품이름(p_name) 과 o_count 
# JOIN 
select c_name, p_name, o_count 
from product, orders, seller, customer
where seller.s_grade='silver' and orders.p_code=product.p_code and seller.s_code=product.s_code and orders.c_id=customer.c_id;

