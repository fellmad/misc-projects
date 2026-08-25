<?php
$tmnt = array(
    'Leo' => array( 
        'bandana' => 'blue', 
        'weapon' => 'swords', 
        'role' => 'leader' 
    ),
    'Raph' => array( 
        'bandana' => 'red', 
        'weapon' => 'sighs', 
        'role' => 'hot shot' 
    ),
    'Mikey' => array( 
        'bandana' => 'orange', 
        'weapon' => 'nunchucks', 
        'role' => 'fun one' 
    ),
    'Don' => array( 
        'bandana' => 'purple', 
        'weapon' => 'staff', 
        'role' => 'nerd' 
    ),
);

foreach( $tmnt as $turtle => $atts ) {
    echo "<h4>$turtle:</h4> ";
    echo '<ul>';
    foreach( $atts as $label => $attr ) {
       echo "<li>$label: $attr</li>";
    }
    echo '</ul>';
}