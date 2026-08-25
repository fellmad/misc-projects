<?php

function isHosted()
{
    $hosted = isset($_SERVER["SERVER_NAME"]);
    return $hosted;
}

function usageConsole()
{
    echo "Usage: php hello.php <name>...from the commandline." . PHP_EOL;
}

function usageHosted()
{
    echo "todo usageHosted()";
    die();
}

if (isHosted()) {
    usageHosted();
}

//
// add this to .json config file to used command-line args:
//
//  "args": ["user name", "arg2", "other args, etc."],
//

if ($argc < 2) {
    usageConsole();
    die();
}

$name = $argv[1];
echo "Hello, $name" . PHP_EOL;
