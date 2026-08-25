<?php
function compare_numbers( $a, $b ) {
    if ( $a >= $b ) {
        return $a;
    }
    
    return $b;
}

var_dump( compare_numbers( 10, 5 ) );
var_dump( compare_numbers( 10, 20 ) );
var_dump( compare_numbers( 10, 10 ) );