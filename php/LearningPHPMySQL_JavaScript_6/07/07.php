<?php // copyfile.php
$rc = copy('testfile.txt', 'testfile2.txt');

if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die;
    // die("Could not copy file");
}
echo "File successfully copied to 'testfile2.txt'";
