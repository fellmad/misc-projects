use globe_bank;

describe subjects;

delete from subjects;
INSERT INTO `subjects` VALUES (1,'About Globe Bank',1,1),(2,'Consumer',2,1),(3,'Small Business',3,0);
select * from subjects;
delete from subjects;

INSERT INTO `subjects` (menu_name, position, visible) VALUES ('About Globe Bank',1,1),('Consumer',2,1),('Small Business',3,0);
select * from subjects;