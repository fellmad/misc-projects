
<?php
// https://dev.to/mahdyaralipor/5-php-features-youre-probably-not-using-but-should-133e

$fiber = new Fiber(function (): string {
    echo "[Fiber] starting" . PHP_EOL;

    $received = Fiber::suspend('first pause'); // pause + send value out
    echo "[Fiber] resumed, got: $received" . PHP_EOL;

    $received = Fiber::suspend('second pause');
    echo "[Fiber] resumed again, got: $received" . PHP_EOL;

    return 'done';
});

echo "[Main] starting fiber" . PHP_EOL;
$yielded = $fiber->start();                 // runs until first suspend
echo "[Main] fiber paused, sent: $yielded" . PHP_EOL;

$yielded = $fiber->resume('message one');   // resume, get next suspend value
echo "[Main] fiber paused again, sent: $yielded" . PHP_EOL;

$fiber->resume('message two');              // resume to completion
echo "[Main] fiber returned: " . $fiber->getReturn() . PHP_EOL;
