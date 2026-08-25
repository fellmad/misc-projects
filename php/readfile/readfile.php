<?php

// @ symbol in PHP:
// https://www.geeksforgeeks.org/what-is-the-use-of-the-symbol-in-php/

$filename = __FILE__; // read this file
$filename = 'junk';

$handle = @fopen($filename, "r");
if (!$handle) {
    $err = error_get_last();
    $err = print_r($err, true);
    error_log($err);
    die();
}

$linenumber = 1;
while ($line = fgets($handle)) {
    echo $linenumber . ' ' . $line;
    $linenumber++;
}

if (!feof($handle)) {
    die("Error: unexpected fgets() fail\n");
}

fclose($handle);
