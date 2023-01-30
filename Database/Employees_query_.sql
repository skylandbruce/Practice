-- employees 스키마 에서
# 사원의 번호와 급여를 가져옵니다.
select emp_no, salary
from salaries;

# d005 부서 현재 근무하고 있는 사원들의 수를 가져옵니다
select count(dept_no)
from dept_emp
where to_date='9999-01-01' and dept_no='d005';

# d001 부서와 d002 부서 매니저의 사원 번호, 부서 번호를 가져 온다.
select emp_no, dept_no
from dept_manager;

# d001 부서와 d002 부서 매니저의 사원명, 부서명을 가져온다as
select emp_no, dept_name
from dept_manager, departments
where to_date='9999-01-01'
	and dept_manager.dept_no=departments.dept_no
    and dept_manager.dept_no='d001' or dept_manager.dept_no='d002'
    
#현재 근무중인 직함이 staff인 사원과 enginner인 사원의 사원버노, 직함을 가져온다.

#현재 근무중인 직함이 staff인 사원과 engineer인 사원의 사원번호, 사원명, 직함을 가져온다.

#현재 근무하고 있는 사원이 받고 있는 급여의 총합을 구합니다.

#현재 근무하고 있는 사원의 수와 급여의 평균을 구합니다.