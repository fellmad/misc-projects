<?php

$j       = 23;
$temp    = "Hello";
$address = "1 Old Street";
$age     = 61;

$arr = compact(explode(' ', 'j temp address age'));

var_dump($arr);
