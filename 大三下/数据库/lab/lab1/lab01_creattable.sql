drop table if exists borrow;
drop table if exists reserve;
drop table if exists book;
drop table if exists reader;

create table book(
	bid char(8) primary key,
    bname varchar(100) not null,
    author varchar(50),
    price float,
    borrow_Times int default(0),
    reserve_Times int default(0),
    bstatus int default(0)
);

create table reader(
	rid char(8) primary key,
    rname varchar(20),
    age int,
    address varchar(100)
);

create table borrow(
	book_ID char(8),
    reader_ID char(8),
    borrow_Date date,
    return_Date date,
    primary key(book_ID, reader_ID, borrow_Date),
    constraint borrow_book
    foreign key(book_ID) references book(bid),
    constraint borrow_reader
    foreign key(reader_ID) references reader(rid)
);

create table reserve(
	book_ID char(8),
    reader_ID char(8),
    reserve_Date date default(curdate()),
    take_Date date,
    primary key(book_ID, reader_ID, reserve_Date)
);
