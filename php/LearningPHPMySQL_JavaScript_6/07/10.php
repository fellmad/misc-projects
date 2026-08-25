<?php // deletefile.php

$rc = unlink('testfile2.new');

if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die;
}

echo "File 'testfile2.new' successfully deleted";
