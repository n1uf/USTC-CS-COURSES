drop procedure if exists borrow_book;

Delimiter //
create procedure borrow_book(
	in reader_id char(8), in book_id char(8))
begin
	declare reserve_times int; -- 这本书被预约的次数
	declare current_reserve int; -- 这个人已经预约了这本书
	declare existing_borrow int; -- 这个人在同一天借了同一本书
	declare current_borrow int; -- 这个人已经借了多少本书
    
    
    select count(*) into reserve_times from reserve
    where reserve.book_ID = book_id;
    
    select count(*) into current_reserve from reserve 
    where reserve.book_ID = book_id and reserve.reader_ID = reader_id;
    
    if reserve_times != 0 and current_reserve = 0 then
		select "C:该图书存在预约记录，借阅者没有预约，不许借阅";
	else
		select count(*) into existing_borrow from borrow 
        where borrow.reader_ID = reader_id 
        and borrow.book_ID = book_id
        and borrow.borrow_date = '2024/5/9';
		if existing_borrow > 0 then
			select "B:不允许同一个读者在同一天借阅同一本书";
		else
			select count(*) into current_borrow from borrow
            where borrow.reader_ID = reader_id
            and borrow.return_date is null;
            if current_borrow >= 3 then
				select "A:一个读者最多借阅三本书，如有三本书未归还则不许再借阅";
			else
				-- 借阅成功
                select "借阅成功！";
                -- E：更新图书表
                update book set bstatus = 1, borrow_times = borrow_times + 1
                where bid = book_id;
                -- 插入borrow表
                insert into borrow(book_ID, reader_ID, borrow_date)
                values(book_id, reader_id, '2024/5/9');
                -- D：删除预约信息（如果有预约的话）
                delete from reserve 
                where reserve.book_ID = book_id 
                and reserve.reader_ID = reader_id;
			end if;
		end if;
	end if;
end //
Delimiter ;