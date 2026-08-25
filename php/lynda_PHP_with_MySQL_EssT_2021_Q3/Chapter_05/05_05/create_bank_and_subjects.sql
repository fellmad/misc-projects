/*
 mysql --verbose -u root -p
 source <this file>
 */
show databases;
drop database if exists globe_bank;
create database globe_bank;
show databases;
use globe_bank;

CREATE TABLE subjects (
    id INT(11) NOT NULL AUTO_INCREMENT,
    menu_name VARCHAR(255),
    position INT(3),
    visible TINYINT(1), /* could use BOOL or BOOLEAN */
    PRIMARY KEY (id)
);

show tables;
describe subjects;
