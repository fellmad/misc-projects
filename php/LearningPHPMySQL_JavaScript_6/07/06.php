<?php
$fh = fopen("testfile.txt", 'r');
if (!$fh) {
    die("File does not exist or you lack permission to open it");
}

$text = fread($fh, 3);
fclose($fh);
echo $text;
