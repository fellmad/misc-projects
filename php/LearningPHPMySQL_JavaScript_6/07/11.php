<?php // update.php

$filename = 'testfile.txt';
$fh = fopen($filename, 'r+');
if (!$fh) {
    $errors = error_get_last();
    print_r($errors);
    die("Failed to open $filename");
}

$text = fgets($fh);
fseek($fh, 0, SEEK_END);
$rc = fwrite($fh, "\n$text");
if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die("Could not write to $filename");
}

fclose($fh);

echo "$filename successfully updated";
