<?php

const DB_HOST = 'localhost';
const DB_USERID = 'root';
const DB_PASSWORD = 'dwighty';
const DB_NAME = 'ijdb';

if (isset($_GET['addjoke'])) {
    include 'form.html.php';
    exit();
}

$link = mysqli_connect(DB_HOST, DB_USERID, DB_PASSWORD);
if (!$link) {
    $error = 'Unable to connect to the database server: ' . mysqli_connect_error();
    include 'error.html.php';
    exit();
}

if (!mysqli_set_charset($link, 'utf8')) {
    $error = 'Unable to set database connection encoding: ' . mysqli_error($link);
    include 'error.html.php';
    exit();
}

if (!mysqli_select_db($link, DB_NAME)) {
    $error = 'Unable to locate the joke database: ' . mysqli_error($link);
    include 'error.html.php';
    exit();
}

if (isset($_POST['joketext'])) {
    $joketext = mysqli_real_escape_string($link, $_POST['joketext']);
    $sql = 'INSERT INTO joke SET
			joketext="' . $joketext . '",
			jokedate=CURDATE()';
    if (!mysqli_query($link, $sql)) {
        $error = 'Error adding submitted joke: ' . mysqli_error($link);
        include 'error.html.php';
        exit();
    }

    header('Location: .');
    exit();
}

$result = mysqli_query($link, 'SELECT joketext FROM joke');
if (!$result) {
    $error = 'Error fetching jokes: ' . mysqli_error($link);
    include 'error.html.php';
    exit();
}

while ($row = mysqli_fetch_array($result)) {
    $jokes[] = $row['joketext'];
}

include 'jokes.html.php';
