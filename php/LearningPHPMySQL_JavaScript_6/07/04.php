<?php // testfile.php

$fh = fopen("testfile.txt", 'w');
if (!$fh) {
    $errors = error_get_last();
    print_r($errors);
    die("Failed to create file");
}

$text = <<<_END
Line 1
Line 2
Line 3
_END;

$rc = fwrite($fh, $text);
if (!$rc) {
    $errors = error_get_last();
    print_r($errors);
    die("Could not write to file");
}

fclose($fh);
echo "File 'testfile.txt' written successfully";
