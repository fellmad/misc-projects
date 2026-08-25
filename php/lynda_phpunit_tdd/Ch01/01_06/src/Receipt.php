<?php

// composer require --dev phpunit/phpunit ^9

namespace TDD;

class Receipt {
    public function total(array $items = []) {
        return array_sum($items);
    }
}
