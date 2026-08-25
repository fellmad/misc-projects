-- mariadb -u root -p
-- source <this file>

drop database globe_bank;

create database globe_bank;

use globe_bank;

DROP TABLE IF EXISTS `pages`;

-- child table of subjects table
CREATE TABLE pages (
    id INT(11) NOT NULL AUTO_INCREMENT,
    subject_id INT(11),
    menu_name VARCHAR(255),
    position INT(3),
    visible TINYINT(1),
    content TEXT,
    PRIMARY KEY (id)
);

-- foreign key to subjects table here on child table:
ALTER TABLE pages ADD INDEX fk_subject_id (subject_id);

INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (1, 'Globe Bank', 1, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (1, 'History', 2, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (1, 'Leadership', 3, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (1, 'Contact Us', 4, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (2, 'Banking', 1, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (2, 'Credit Cards', 2, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (2, 'Mortgages', 3, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (3, 'Checking', 1, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (3, 'Loans', 2, 1);
INSERT INTO pages (subject_id, menu_name, position, visible)
VALUES (3, 'Merchant Services', 3, 1);

DROP TABLE IF EXISTS `subjects`;

CREATE TABLE `subjects` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `menu_name` varchar(255) DEFAULT NULL,
    `position` int(3) DEFAULT NULL,
    `visible` tinyint(1) DEFAULT NULL,
    PRIMARY KEY (`id`)
);

INSERT INTO `subjects`

VALUES
    (1, 'About Globe Bank', 1, 1),
    (2, 'Consumer', 2, 1),
    (3, 'Small Business', 3, 0);