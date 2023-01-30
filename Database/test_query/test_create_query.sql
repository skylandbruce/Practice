use test_query;

# table 생성과, column 추가
create table addr
(a_idx int not null unique, 
c_id varchar(45), 
a_addr varchar(45), 
a_cnt int);

# table명 변경
rename table_name1 to table_name2 

# table명 제거하기
drop table table_name

# table 의 모든 field 제거(조건 없음)
truncate table table_name

# table copy: column과 field
create table table_copy
as
select *
from table_name;

# table copy: column만 copy
create table table_copy
as
select column1, column2
from table_name
where 0=1;

# column 추가 
alter table table_name
add [column_name type, ...];

# column 변경
alter table table_name
modify [column_name type,...]

# column 제거
alter table table_name
drop column column_name