-- ex 1
select full_name, department
    from department d join employee e on d.mngr_no=e.emp_n;

-- ex 2
select e.full_name, d.department
    from department d join employee e using(dept_no)
    where e.job_country = 'USA';

-- ex 3
select e.full_name, j.job_title, j.job_country, e.salary
    from employee e join job j
        using(job_country, job_code, job_grade)
    where extract(year from e.hire_date) = 1993;

-- ex 4
select e.full_name, p.proj_name
    from employee e join employee_project ep using(emp_no)
        join project p using(proj_id);

-- ex 5
select A.department, B.department as head_dept
    from department A join department B
        on A.head_dept = B.dept_no;

-- ex 6
select e1.full_name, e2.full_name, e1.job_code, e2.job_grade
    from employee E1 join employee E2 using(job_code, job_grade)
        where (e1.job_country = 'USA') and (e2.job_country = 'USA')
            and (e1.emp_no < e2.emp_no);

-- ex 7
select d.department, count(emp_no)
    from department d join employee e using(dept_no)
        group by d.department;

-- tsk 1
select e.full_name, j.job_title
    from employee e join job j using(job_code, job_grade, job_country)
        where e.salary < 50000;

-- tsk 2
select e.full_name, e.salary
    from project p join employee e on p.team_leader=e.emp_no;

-- tsk 3
select d.department
    from employee e join department d on e.emp_no=d.mngr_no
    where e.salary>70000;

-- tsk 4
select e.full_name, coalesce(d.phone_no || ' ' || e.phone_ext, d.phone_no) as phone_number_employee, e.salary
    from employee e join department d using(dept_no);

-- tsk 5
select sal.old_salary, sal.new_salary, sal.change_date
    from department dep join salary_history sal on dep.mngr_no=sal.emp_no
        where dep.department = 'Field Office: East Coast';

-- tsk 6
select sal.po_number, sal.total_value, c.currency
    from sales sal join customer cus using(cust_no)
    join country c using (country);

-- tsk 7
select sal.po_number, e.job_country
    from sales sal join employee e on sal.sales_rep=e.emp_no;

-- tsk 8
select e.full_name, e.salary
    from employee_project eproj join project proj using(proj_id)
    join employee e using(emp_no)
        where proj.proj_name = 'Video Database'
        order by e.salary;

-- tsk 9
select count(distinct e.emp_no)
    from job j join employee e using(job_code)
        where j.job_title = 'Sales Representative';

-- tsk 10
select dep.department
    from department dep join employee emp using(dept_no)
        group by dep.department
        having count(emp.emp_no) > 3;


















