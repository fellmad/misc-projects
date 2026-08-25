<?php
$firstname = $_REQUEST['firstname'];
$lastname = $_REQUEST['lastname'];
if (
    strtolower($firstname) == strtolower('Kevin') and
    strtolower($lastname) == strtolower('Yank')
) {
    echo 'Welcome, oh glorious leader!';
} else {
    echo 'Welcome to our web site, ' .
        htmlspecialchars($firstname, ENT_QUOTES, 'UTF-8') . ' ' .
        htmlspecialchars($lastname, ENT_QUOTES, 'UTF-8') . '!';
}
