<?php

// run:
// vendor\bin\phpunit tests\ReceiptTest.php --color --filter=testTax
// vendor\bin\phpunit tests\ReceiptTest.php --color --filter=ReceiptTest::testTax
// with the file phpunit.xml in this folder: vendor\bin\phpunit
// vendor\bin\phpunit --testsuite=app
// vendor\bin\phpunit --testsuite=app --filter=testTax
// fix the filter element in phpunit.xml:
// https://phpunit.readthedocs.io/en/9.5/configuration.html?highlight=filter

namespace TDD\Test;

require dirname(dirname(__FILE__))
    . DIRECTORY_SEPARATOR . 'vendor'
    . DIRECTORY_SEPARATOR . 'autoload.php';

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
            15,
            $output,
            'When summing the total should equal 15'
        );
    }

    public function testTax() {
        $inputAmount = 10.00;
        $taxInput = 0.10;
        $output = $this->Receipt->tax($inputAmount, $taxInput);
        $this->assertEquals(
            1.00,
            $output,
            'The tax calculation should equal 1.00'
        );
    }
}
