<?php
// removed 'else' clause here.
// better: return or exit?
if (!isset($_REQUEST['firstname'])) {
    include 'form.html.php';
    exit;
    // return; 
}

$firstname = $_REQUEST['firstname'];
$lastname = $_REQUEST['lastname'];
if (
    strtolower($firstname) == strtolower('Kevin') and
    strtolower($lastname) == strtolower('Yank')
) {
    $output = 'Welcome, oh glorious leader!';
} else {
    $output = 'Welcome to our web site, ' .
        htmlspecialchars($firstname, ENT_QUOTES, 'UTF-8') . ' ' .
        htmlspecialchars($lastname, ENT_QUOTES, 'UTF-8') . '!';
}
include 'welcome.html.php';
