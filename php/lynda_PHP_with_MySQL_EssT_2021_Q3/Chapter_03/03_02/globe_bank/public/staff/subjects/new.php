<?php

require_once('../../../private/initialize.php');

$test = $_GET['test'] ?? '';

switch ($test) {
    case '404':
        error_404();
        break;
    case '500':
        error_500();
        break;
    default:
        echo 'no error.';
}

// if ($test == '404') {
//     error_404();
// } elseif ($test == '500') {
//     error_500();
// } else {
//     echo 'No error';
// }
