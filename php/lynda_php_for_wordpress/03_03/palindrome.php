<?php
function is_palindrome( $string ) {
    $string = str_replace( ' ', '', strtolower( $string ) );
    return $string == strrev( $string );
}

var_dump( is_palindrome( "Race Car" ) );
var_dump( is_palindrome( "mom" ) );
var_dump( is_palindrome( "Hello World!" ) );