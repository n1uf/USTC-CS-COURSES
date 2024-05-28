-- 查询读者Rose借过的书（包括已还和未还）的
-- 图书号、书号和借期；
select bid, bname, borrow_Date 
from book, borrow, reader 
where reader.rname = 'Rose'
and borrow.reader_ID = reader.rid
and borrow.book_ID = book.bid;

-- 查询从没有结果图书也没有预约过图书的
-- 读者号和读者姓名；
select rid, rname
from reader
where reader.rid
not in(
	select reader_ID
    from borrow
    union
    select reader_ID
    from reserve
);

-- 查询被借阅次数最多的作者（注意一个作者可能写了多本书）；
-- ans A 使用借阅表borrow中的借书记录
select author
from book, borrow
where book.bid = borrow.book_ID
group by author
order by
count(author) desc
limit 1;

-- ans B 使用图书表book中的borrow_times
select author
from book
group by author
order by
sum(borrow_Times) desc
limit 1;

-- 查询目前借阅未还的书名中包含“MySQL“的图书号和书名；
select bid, bname
from book
where bstatus = 1
and
bname like "%MySQL%";

-- 查询借阅图书数目（多次借同一本书需要重复计入）
-- 超过3本的读者姓名；
select rname
from reader, borrow
where borrow.reader_ID = reader.rid
group by borrow.reader_ID
having count(borrow.book_ID) > 3;

-- 查询没有借阅过任何一本J.K.Rowling所著图书的
-- 读者号和姓名；
select rid, rname
from reader
where reader.rid not in(
	select reader_ID
    from book, borrow
    where book.author = 'J.K. Rowling'
    and borrow.book_ID = book.bid
);

-- 查询2024年借阅图书数目排名前3名的
-- 读者号、姓名以及借阅图书数；
select rid, rname, count(*) as count
from reader, borrow
where reader.rid = borrow.reader_ID
and borrow.borrow_Date >= '2024-01-01'
and borrow.borrow_Date <= '2024-12-31'
group by rid
order by count desc
limit 3;

-- 创建一个读者借书信息的视图，包含
-- 读者号、姓名、所借阅图书号、图书名和借期；
-- 使用该视图查询2024年所有读者的读书号和所借阅的不同图书数；
create or replace view borrow_info as(
	select
		reader.rid as reader_id,
        reader.rname as reader_name,
        borrow.book_ID as book_id,
        book.bname as book_name,
        borrow.borrow_Date as borrow_date
	from
		reader,
        borrow,
        book
	where
		reader.rid = borrow.reader_ID
        and borrow.book_ID = book.bid
);

select reader_id, count(distinct book_id)
from borrow_info
where borrow_date >= '2024-01-01'
and borrow_date <= '2024-12-31'
group by reader_id;