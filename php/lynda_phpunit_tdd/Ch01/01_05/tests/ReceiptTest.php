<?php

// run command:
// lynda_phpunit_tdd\Ch01\01_05>  vendor\bin\phpunit tests

namespace TDD\Test;

require dirname(dirname(__FILE__)) .
    DIRECTORY_SEPARATOR . 'vendor' . DIRECTORY_SEPARATOR . 'autoload.php';

use PHPUnit\Framework\TestCase;

use TDD\Receipt;

class RectiptTest extends TestCase
{
    public function testTotal()
    {
        $Receipt = new Receipt();
        $this->assertEquals(
            15,
            $Receipt->total([0, 2, 5, 8]),
            'when summing the total should equal 15'
        );
    }
}
