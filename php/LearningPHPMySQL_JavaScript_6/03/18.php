<?php
static $int = 0;         // Allowed 
static $int = 1 + 2;       // Disallowed (will produce a Parse error)  ?

echo $int;

// static $int = sqrt(144); // Disallowed
