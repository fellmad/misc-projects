<?php require_once('../../../private/initialize.php'); ?>

<?php
$id = $_GET['id'] ?? '1'; // PHP > 7.0
echo $id;
?>

<?php
// dlfnote
// hover over each link to see the modified URL string:
?>

<a href="show.php?name=<?php echo u('John Doe'); ?>">Link</a><br />
<a href="show.php?company=<?php echo u('Widgets&More'); ?>">Link</a><br />
<a href="show.php?query=<?php echo u('!#*?'); ?>">Link</a><br />