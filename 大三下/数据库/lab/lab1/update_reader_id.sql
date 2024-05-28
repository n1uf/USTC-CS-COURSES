drop procedure if exists update_reader_id;

Delimiter //
create procedure update_reader_id(
	in old_id char(8), in new_id char(8))
begin
	-- 异常
	declare new_id_exist bool;
    declare old_id_exist bool;
    select exists (select * from reader where rid = new_id) into new_id_exist;
    select exists (select * from reader where rid = old_id) into old_id_exist;
    if(new_id_exist) then select "new id exists";
    elseif(not old_id_exist) then select "old id doesn't exist";
    
    else
		start transaction;
		-- 解除外键约束
		set foreign_key_checks = false;
        update reader set rid = new_id where reader.rid = old_id;
        update borrow set reader_id = new_id where borrow.reader_id = old_id;
		-- 恢复外键约束
		set foreign_key_checks = true;
        
		create temporary table temp_reserve
        select * from reserve where reader_ID = old_id;
        
		insert into reserve (book_ID, reader_ID, reserve_Date, take_Date)
		select book_ID, new_id, reserve_Date, take_Date from temp_reserve;
        
        drop temporary table temp_reserve;
		commit;
	end if; 
end //
Delimiter ;