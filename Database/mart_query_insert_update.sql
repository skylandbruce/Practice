-- INSERT
# INTO 테이블_이름(속성 리스트)
# VALUES (자료)
-- 특정 column에만 자료 삽입 할 때
insert into customer( c_id, c_name, c_age, c_grade, c_job, c_point )
values('strawberry','김유경','30','vip','공무원',1000);

insert into customer
values('watermelon','정성용','30','vip','학생',1000000);

insert
into customer
values('tomato', '정은심', '36', 'gold', NULL, 4000);


-- UPDATE
#UPDATE 테이블_이름
#SET 속성이름1=값1, 속성_이름2=값2, ...
#[WHERE 조건]; 

update product
set p_name='통통변경'
where p_code='p06';

-- Error 체크
update product
set p_ucost=(p_ucost*1.1)
where p_code!=null;

-- column 지우기-- Dangerlous!!!
#delete
#from orders;


