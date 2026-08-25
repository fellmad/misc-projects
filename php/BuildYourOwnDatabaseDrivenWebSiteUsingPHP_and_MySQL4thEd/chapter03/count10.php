<!DOCTYPE html>

<head>
    <title>Counting to Ten</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
</head>

<body>
    <p>
        <?php
        $count = 1;
        while ($count <= 10) {
            echo "$count ";
            ++$count;
        }
        ?>
    </p>
</body>

</html>