<?php

$dt = new DateTime();
$dt_formatted = $dt->format('Y-m-d H:i:s');

$to = 'fellmad@gmail.com';
$subject = 'test message sending at: ' . $dt_formatted;
$message = 'Hello, World!';
$headers = "From: example@example.com\r\n"; // Or sendmail_username@hostname by default
mail($to, $subject, $message, $headers);
