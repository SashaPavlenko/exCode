create or alter procedure PROC_LAB_8_TASK_8 (
    D1 type of column OPERATION.OP_DATE,
    D2 type of column OPERATION.OP_DATE)
returns (
    NAME_GOOD type of column GOODS.NOMENCLATURE,
    NAME_WAREHOUSE type of column WAREHOUSE.NAME,
    NAME_AGENT type of column AGENT.NAME_AG,
    TOTAL_VALUE_OPERATION float)
as
begin
  for select g.nomenclature as name_good, wh.name as name_wh, ag.name_ag as name_agent, (op.quantity*op.price) as total_value_operation
    from operation op join goods g using(id_goods) join agent ag using(id_ag) join warehouse wh using(id_wh)
    where op.op_date>=:D1 and op.op_date<=:D2
    into :name_good, :name_warehouse, :name_agent, :total_value_operation do
        suspend;
end