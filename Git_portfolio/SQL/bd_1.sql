with 
-- вычисляем время первого сообщения пользователя
T1 as (select entity_id as id_1, min(created_at) as min_time_mes
from test.chat_messages
where type = 'incoming_chat_message'
group by entity_id
),
-- вычисляем время первого ответа пользователю с учетом его первого сообщения
T2 as (select entity_id as id_2, min(CM.created_at) as min_time_ans
from test.chat_messages as CM inner join T1 on T1.id_1 = CM.entity_id 
where type = 'outgoing_chat_message' and CM.created_at > T1.min_time_mes
group by entity_id),
-- соединяем с идентификатором менеджера
T3 as (
select id_2, min_time_ans as min_time_ans, created_by as manager_id
from T2 inner join test.chat_messages as test_1 on test_1.created_at = T2.min_time_ans and test_1.entity_id = T2.id_2
),
-- меняем формат времени и соединяем первую и третью таблицу
T4 as (select  manager_id, id_1, TO_TIMESTAMP(min_time_ans) AT TIME ZONE 'UTC' as min_time_ans, TO_TIMESTAMP(min_time_mes) AT TIME ZONE 'UTC' as min_time_mes
from T1 inner join T3 on T1.id_1 = T3.id_2),
-- расчитываем время ответа на сообщения с учетом ночного времени суток
T5 as (
select manager_id, id_1, min_time_mes, min_time_ans,
case 
	when min_time_mes::time <= '09:30:00'::time and min_time_ans <= min_time_mes - min_time_mes::time + interval '9 hours 30 minutes' 
	then '00:00:00'::interval
	when min_time_mes::time < '09:30:00'::time and min_time_ans > min_time_mes - min_time_mes::time + interval '9 hours 30 minutes'
	then 
		case 
			when min_time_ans < min_time_mes - min_time_mes::time + interval '1 day'
			then min_time_ans - min_time_mes - ('09:30:00'::time - min_time_mes::time)
			when min_time_ans > min_time_mes - min_time_mes::time + interval '1 day 9 hours 30 minutes'
		 	then min_time_ans - min_time_mes - interval '9 hours 30 minutes' - ('09:30:00'::time - min_time_mes::time)
			when min_time_ans > min_time_mes - min_time_mes::time + interval '1 day'
			then min_time_mes - min_time_mes::time + interval '1 day' - min_time_mes - ('09:30:00'::time - min_time_mes::time)
		end
	when min_time_mes::time >= '09:30:00'::time
	then 
		case 
			when min_time_ans < min_time_mes - min_time_mes::time + interval '1 day' 
			then min_time_ans - min_time_mes
			when min_time_ans > min_time_mes - min_time_mes::time + interval '1 day 9 hours 30 minutes' 
		 	then min_time_ans - min_time_mes - interval '9 hours 30 minutes'
			when min_time_ans > min_time_mes - min_time_mes::time + interval '1 day'
			then min_time_mes - min_time_mes::time + interval '1 day' - min_time_mes
		end
end as time_answer
from T4
),
-- считаем среднее время ответа для каждой группы менеджеров
T6 as (
select TM.name_mop, avg(time_answer) AS average_time
from T5 inner join test.managers as TM on T5.manager_id = TM.mop_id
group by mop_id
)
-- выводим результат
select *
from T6
order by 2