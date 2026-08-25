<!DOCTYPE html>

<head>
    <title>Query String Link Example</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
</head>

<body>
    <p>
        <?php
        $name = $_GET['name'];
        echo 'Welcome to our web site, ' . $name . '!';
        ?>
    </p>
</body>

</html>