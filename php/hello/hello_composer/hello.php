<?php

// in this folder:
//      composer u
// to retrieve composer dependencies for this app to run
// https://getcomposer.org/doc/01-basic-usage.md

require __DIR__ . '/vendor/autoload.php';

$log = new Monolog\Logger('name');
$log->pushHandler(new Monolog\Handler\StreamHandler('app.log', Monolog\Level::Warning));
$log->warning('Foo');
echo "see the new file 'app.log'" . PHP_EOL;
