<?php

$rc = rename('testfile2.txt', 'testfile2.new');
if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die;
}

echo "File successfully renamed to 'testfile2.new'";
