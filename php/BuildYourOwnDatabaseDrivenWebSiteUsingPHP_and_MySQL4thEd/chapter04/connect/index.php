<?php

const DB_HOST = 'localhost';
const DB_USERID = 'root';
const DB_PASSWORD = 'dwighty';
const DB_NAME = 'ijdb';

$link = mysqli_connect(DB_HOST, DB_USERID, DB_PASSWORD);
if (!$link)
{
	$output = 'Unable to connect to the database server.';
    $err = mysqli_connect_error();
    $output .= PHP_EOL . $err;
	include 'output.html.php';
	exit();
}
//var_dump($link);

// var_dump($link->get_charset()); 
if (!mysqli_set_charset($link, 'utf8'))
{
	$output = 'Unable to set database connection encoding.';
	include 'output.html.php';
	exit();
}
// var_dump($link->get_charset());

if (!mysqli_select_db($link, DB_NAME))
{
	$output = 'Unable to locate the joke database.';
	include 'output.html.php';
	exit();
}
//var_dump($link);

$output = 'Database connection established.';
include 'output.html.php';
