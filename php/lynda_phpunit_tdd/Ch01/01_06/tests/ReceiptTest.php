<?php

// composer require --dev phpunit/phpunit ^9
// vendor\bin\phpunit tests --color

namespace TDD\Test;

require dirname(dirname(__FILE__)) .
    DIRECTORY_SEPARATOR . 'vendor' .
    DIRECTORY_SEPARATOR . 'autoload.php';

use PHPUnit\Framework\TestCase;
use TDD\Receipt;

class ReceiptTest extends TestCase {
    public function setUp(): void {
        $this->Receipt = new Receipt();
    }

    public function tearDown(): void {
        unset($this->Receipt);
    }

    public function testTotal() {
        $input = [0, 2, 5, 8];
        $output = $this->Receipt->total($input);
        $this->assertEquals(
            151,
            $output,
            'When summing the total should equal 15'
        );
    }
}
