<?php

// from course:
// https://www.linkedin.com/learning/php-with-mysql-essential-training-1-the-basics

// Assign file paths to PHP constants
// __FILE__ returns the current path to this file
// dirname() returns the path to the parent directory

// dlfnote: place this in a 'private' folder with a 'public' folder at the same level.
define("PRIVATE_PATH", dirname(__FILE__));
define("PROJECT_PATH", dirname(PRIVATE_PATH));
const PUBLIC_PATH = PROJECT_PATH . '/public';
const SHARED_PATH = PRIVATE_PATH . '/shared';

echo "__FILE__: " . __FILE__ . PHP_EOL;
echo "PRIVATE_PATH: " . PRIVATE_PATH . PHP_EOL;
echo "PROJECT_PATH: " . PROJECT_PATH . PHP_EOL;
echo "PUBLIC_PATH: " . PUBLIC_PATH . PHP_EOL;
echo "SHARED_PATH: " . SHARED_PATH . PHP_EOL;
