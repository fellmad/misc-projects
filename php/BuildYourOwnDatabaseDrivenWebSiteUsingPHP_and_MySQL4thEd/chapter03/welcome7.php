<?php
$name = $_REQUEST['name'];
if ($name == 'Kevin') {
    echo 'Welcome, oh glorious leader!';
} else {
    echo 'Welcome to our web site, ' .
        htmlspecialchars($name, ENT_QUOTES, 'UTF-8') . '!';
}
