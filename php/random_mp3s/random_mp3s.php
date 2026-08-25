<?php

// https://code.tutsplus.com/tutorials/get-command-line-arguments-with-php-argv-or-getopt--cms-39201

$shortopts  = "";
$shortopts .= "n:";     // nukmber of mp3's to collect
$shortopts .= "s:";     // startfolder
$shortopts .= "d::";    // destination folder. optional.

function usage()
{
    $scriptName = basename(__FILE__);
    echo <<<EOD
    usage:
        php $scriptName -n -s -d  // number; startfolder; destination folder.
        if given, destfolder must exist. if not given, only a count is returned.
    EOD;
}

function GetFilenamesByExtention(string $extension, string $startFolder)
{
    $extension = strtolower($extension);
    $matching_list = [];
    $dir = new RecursiveDirectoryIterator(
        $startFolder,
        FilesystemIterator::SKIP_DOTS
    );
    $files = new RecursiveIteratorIterator($dir);
    foreach ($files as $file) {
        $ext = $file->getExtension();
        $ext = strtolower($ext);
        if ($extension != $ext) {
            continue;
        }
        $matching_list[] = $file->getRealPath();  // append; faster than array_push
    }
    return $matching_list;
}

$options = getopt($shortopts);

if (!isset($options['n'])) {
    usage();
    die();
}
if (!isset($options['s'])) {
    usage();
    die();
}

$number = intval($options['n']);
$startfolder = $options['s'];
$destfolder = '';

if (isset($options['d'])) {
    $destfolder = $options['d'];
    if (!file_exists($destfolder)) {
        die("destination folder " . $destfolder . " does not exist.");
    }
}

if (!file_exists($startfolder)) {
    die("start folder " . $startfolder . " does not exist.");
}

echo ("collecting $number mp3's starting in $startfolder." . PHP_EOL);
$filenames = GetFilenamesByExtention('mp3', $startfolder);
echo count($filenames) . " files found." . PHP_EOL;

$max_files = min($number, count($filenames));
$num_copied = 0;
if ($destfolder != '') {
    echo "copying " . $number . " to " . $destfolder . PHP_EOL;
    $fileNameKeys = array_rand($filenames, $max_files);
    foreach ($fileNameKeys as $key) {
        // echo $key . ' ' . $filenames[$key] . PHP_EOL;
        $source_filename = $filenames[$key];
        $short_source_filename = basename($source_filename);
        $dest_filename = $destfolder . DIRECTORY_SEPARATOR . $short_source_filename;
        $rc = copy($source_filename, $dest_filename);
        if (!$rc) {
            die("copy failed: " . $source_filename . " to " . $dest_filename);
        }
        $num_copied++;
    }
}

echo ("$num_copied" . " files copied.");
