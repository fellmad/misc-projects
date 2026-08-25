<?php

$filename = 'testfile.txt';

$fh = fopen($filename, 'r+');
if (!$fh) {
    $errors = error_get_last();
    print_r($errors);
    die("fopen() $filename");
}

$text = fgets($fh);

if (!flock($fh, LOCK_EX)) {
    $errors = error_get_last();
    print_r($errors);
    die("flock() fail on $filename");
}

if (fseek($fh, 0, SEEK_END)) {
    $errors = error_get_last();
    print_r($errors);
    die("fseek() fail on $filename");
}

if (!fwrite($fh, "$text")) {
    $errors = error_get_last();
    print_r($errors);
    die("fwrite() fail on $filename");
}

if (!flock($fh, LOCK_UN)) {
    $errors = error_get_last();
    print_r($errors);
    die("flock() fail on $filename");
}

if (!fclose($fh)) {
    $errors = error_get_last();
    print_r($errors);
    die("fclose() fail on $filename");
}

echo "$filename  successfully updated";
