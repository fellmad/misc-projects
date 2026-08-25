<?php

require_once('../../../private/initialize.php');

$test = $_GET['test'] ?? '';

// dlf: prefered switch statement.
switch ($test) {
    case '404':
        error_404();
        break;
    case '500':
        error_500();
        break;
    case 'redirect':
        redirect_to(url_for('/staff/subjects/index.php'));
        break;
    default:
        echo 'no error';
}
