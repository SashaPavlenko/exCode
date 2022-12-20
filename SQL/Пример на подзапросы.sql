-- tsk 1
select e.FULL_NAME, e.JOB_COUNTRY, e.SALARY,
    (select max(emp.SALARY)
            from EMPLOYEE emp
            where emp.JOB_COUNTRY=e.JOB_COUNTRY) as max_salary,
    (select min(emp1.SALARY)
            from EMPLOYEE emp1
            where emp1.JOB_COUNTRY=e.JOB_COUNTRY) as min_salary
    from EMPLOYEE e
    where e.JOB_COUNTRY='USA' or e.JOB_COUNTRY='Canada';

-- tsk 2
select dep.DEPARTMENT, dep.BUDGET
    from DEPARTMENT dep
    where dep.BUDGET > (select BUDGET from DEPARTMENT where DEPT_NO=130)
    order by dep.BUDGET asc;

-- tsk 3
select emp.FULL_NAME, emp.SALARY, av.avSalCounrty
    from EMPLOYEE emp join (select (j.MAX_SALARY+j.MIN_SALARY)/2 as avSalCounrty, j.JOB_CODE, j.JOB_COUNTRY, j.JOB_GRADE
            from job j
            where j.JOB_COUNTRY='USA'
        ) as av
    on emp.JOB_CODE=av.JOB_CODE and emp.JOB_GRADE=av.JOB_GRADE and emp.JOB_COUNTRY=av.JOB_COUNTRY
    where emp.SALARY > av.avSalCounrty;

select emp.FULL_NAME, emp.SALARY
    from EMPLOYEE emp
    where emp.JOB_COUNTRY='USA' and emp.SALARY>(
        select (av.MAX_SALARY+av.MIN_SALARY)/2
        from job av
        where emp.JOB_CODE=av.JOB_CODE and emp.JOB_GRADE=av.JOB_GRADE and emp.JOB_COUNTRY=av.JOB_COUNTRY
        );

-- tsk 4
-- select p.PROJ_NAME, r.mng_name, r.FISCAL_YEAR, r.name_dep
select p.PROJ_NAME, r.name_dep, r.mng_name
    from PROJECT p left join (
        select emp.FULL_NAME as mng_name, pdb.PROJ_ID, pdb.FISCAL_YEAR, dep.DEPARTMENT as name_dep
            from PROJ_DEPT_BUDGET pdb join department dep using(dept_no)
            left join EMPLOYEE emp on dep.MNGR_NO=emp.EMP_NO
            where pdb.FISCAL_YEAR=1994
    ) as R (mng_name, proj_id, fiscal_year, name_dep)
    on p.PROJ_ID=r.PROJ_ID

-- tsk 5
select (
    select g.NOMENCLATURE
        from GOODS g
        where g.ID_GOODS=gw.ID_GOODS
           ),
    (
        select wh.TOWN
            from WAREHOUSE wh
            where wh.ID_WH=gw.ID_WH
        )
    from GOODS_WH gw

-- tsk 6
select
    (
        select a.NAME_AG
            from AGENT a
            where a.ID_AG=o.ID_AG
        )
    from OPERATION o
    where o.ID_GOODS=(
        select g.ID_GOODS
            from GOODS g
            where g.NOMENCLATURE='Папки'
        );

-- tsk 7
select
    (
    select a.NAME_AG
        from AGENT a
        where a.ID_AG=o.ID_AG
        ), count(distinct o.ID_GOODS)
    from OPERATION o
    where o.ID_WH=(
        select wh.ID_WH from WAREHOUSE wh where wh.NAME='Склад 1')
    group by o.ID_AG
    having count(distinct o.ID_GOODS)>1;

-- tsk 8
select o.OP_DATE,
       (select a.NAME_AG
            from AGENT a
            where o.ID_AG=a.ID_AG)
    from OPERATION o
    where o.ID_GOODS=(select g.ID_GOODS from GOODS g where g.NOMENCLATURE='Папки') and
          o.PRICE<(
          select avg(o1.PRICE)
            from OPERATION o1
            where o1.ID_GOODS=o.ID_GOODS
            )

