-- test update_reader_id
select * from reader where 1;
call update_reader_id('R006', 'R999');
select * from reader where 1;

select * from borrow where 1;

select * from reserve where 1;