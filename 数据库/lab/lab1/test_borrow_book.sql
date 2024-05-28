-- (1)
call borrow_book ('R001', 'B008');
-- (2)
call borrow_book('R001', 'B001');
select * from reserve;
select * from borrow;
select * from reserve where
reserve.reader_ID = 'R001' and reserve.book_ID = 'B001';
select bid, borrow_Times, bstatus from book where
book.bid = 'B001';
-- (3)
call borrow_book('R001', 'B001');
-- (4)
call borrow_book('R005', 'B008');
