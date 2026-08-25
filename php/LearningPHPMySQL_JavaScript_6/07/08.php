<?php // copyfile2.php

$rc = copy('testfile.txt', 'testfile2.txt');
if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die;
}

echo ("File successfully copied to 'testfile2.txt'");
