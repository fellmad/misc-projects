<?php

const DB_HOST = 'localhost';
const DB_USERID = 'root';
const DB_PASSWORD = 'dwighty';
const DB_NAME = 'ijdb';

$link = mysqli_connect(DB_HOST, DB_USERID, DB_PASSWORD);
if (!$link)
{
	$output = 'Unable to connect to the database server: ' . mysqli_connect_error();
	include 'output.html.php';
	exit();
}
//var_dump($link);

// var_dump($link->get_charset()); 
if (!mysqli_set_charset($link, 'utf8'))
{
	$output = 'Unable to set database connection encoding: ' . mysqli_error($link);
	include 'output.html.php';
	exit();
}
// var_dump($link->get_charset());

if (!mysqli_select_db($link, DB_NAME))
{
	$output = 'Unable to locate the joke database: ' . mysqli_error($link);
	include 'output.html.php';
	exit();
}
//var_dump($link);

$sql = 'CREATE TABLE joke (
			id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
			joketext TEXT,
			jokedate DATE NOT NULL
		) DEFAULT CHARACTER SET utf8';
if (!mysqli_query($link, $sql)) {
    $output = 'Error creating joke table: ' . mysqli_error($link);
    include 'output.html.php';
    exit();
}

$output = 'Joke table successfully created.';
include 'output.html.php';
