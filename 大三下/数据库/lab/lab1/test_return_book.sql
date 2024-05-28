-- (1)
call return_book('R001', 'B008');
-- (2)
select bstatus from book where book.bid = 'B001';
select reader_ID, book_ID, return_Date from borrow 
where reader_ID = 'R001' and book_ID = 'B001';
call return_book('R001', 'B001');
select bstatus from book where book.bid = 'B001';
select reader_ID, book_ID, return_Date from borrow 
where reader_ID = 'R001' and book_ID = 'B001';
