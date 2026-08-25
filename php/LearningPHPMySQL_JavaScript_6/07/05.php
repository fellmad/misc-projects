<?php
$fh = fopen("testfile.txt", 'r');

if (!$fh) {
    die("File does not exist or you lack permission to open it");
}

$line = fgets($fh);
fclose($fh);
echo $line;
