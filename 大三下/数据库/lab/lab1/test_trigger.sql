insert into Reserve (book_ID, reader_ID, reserve_Date)
values ('B012', 'R001', curdate());
select * from Reserve;
select * from Book where bid = 'B012';
delete from Reserve where book_ID = 'B012' and reader_ID = 'R001';
select * from Reserve;
select * from Book where bid = 'B012';
