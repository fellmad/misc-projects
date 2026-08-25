<?php
$a = "1000";
$b = "+1000";
$c = 1000;

if ($a == $b)  echo "1";
if ($a === $b) echo "2";

if ($a == $c) echo "string equals number...";

if ($b == $c) echo "string equals number...";