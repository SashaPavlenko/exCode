create or alter procedure PROC_LAB_8_TASK_7 (
    GNAME type of column GOODS.NOMENCLATURE,
    GCNTMIN integer)
returns (
    ANAME type of column AGENT.NAME_AG)
as
declare variable IDG type of column GOODS.ID_GOODS;
begin
  idg = (select g.id_goods from goods g where g.nomenclature=:gname);

  for select (select a.name_ag from agent a where a.id_ag=op.id_ag) as name_agent
    from operation op join agent ag using(id_ag) join goods g using(id_goods)
    where op.id_goods=:idg
    group by op.id_ag
    having count(op.id_ag) > :gcntmin
    into :ANAME do
        suspend;
end