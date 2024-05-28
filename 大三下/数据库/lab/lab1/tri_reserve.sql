drop trigger if exists trig_ins_reserve;
drop trigger if exists trig_del_reserve;

Delimiter //
create trigger trig_ins_reserve after insert on Reserve
for each row
begin
	update Book set bstatus = 2, reserve_Times = reserve_Times + 1
	where bid = new.book_ID;
end;

create trigger trig_del_reserve after delete on Reserve 
for each row 
begin
declare book_status int;
declare num_reserve int;
	-- 获取当前预约书籍的状态和剩余预约数
	select bstatus, reserve_Times into book_status, num_reserve
	from Book where Book.bid = old.book_ID;
	-- 减少预约次数
	update Book set Book.reserve_Times = num_reserve - 1
	where Book.bid = old.book_ID;
	-- 最后一位预约者取消预约
	if num_reserve = 1 and book_status = 2 then
	update Book set Book.bstatus = 0
	where Book.bid = OLD.book_ID;
    end if;
end //
Delimiter ;

