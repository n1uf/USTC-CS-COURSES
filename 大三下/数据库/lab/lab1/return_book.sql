drop procedure if exists return_book;

Delimiter //
create procedure return_book(
	in reader_id char(8), in book_id char(8))
begin
	declare reserved bool;
    if not exists(
	select 1 from borrow
	where borrow.reader_ID = reader_id
	and borrow.book_ID = book_id
	and borrow.return_Date is null) then
		select "没有借阅，还书失败";
    else
		select "还书成功";
		update borrow set
        return_date = '2024/5/10'
        where borrow.reader_ID = reader_id
		and borrow.book_ID = book_id
		and borrow.return_Date is null;
        select count(*) into reserved from reserve
        where reserve.book_ID = book_id;
        if reserved then
			update book set bstatus = 2 where book.bid = book_id;
		else
			update book set bstatus = 0 where book.bid = book_id;
		end if;
	end if;
end //
Delimiter ;