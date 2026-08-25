<?php

function url_for($script_path) {
  // add the leading '/' if not present
  if($script_path[0] != '/') {
    $script_path = "/" . $script_path;
  }
  return WWW_ROOT . $script_path;
}

function u($string="") {
  return urlencode($string);
}

// dlfnote
// use this on the path (the part before the '?')
// blanks encoded as %20
// not commonly used, as path is controlled by our code
function raw_u($string="") {
  return rawurlencode($string);
}

// dlfnote
// use on query string (after the '?')
// spaces encoded as '+'
// used a LOT
function h($string="") {
  return htmlspecialchars($string);
}
