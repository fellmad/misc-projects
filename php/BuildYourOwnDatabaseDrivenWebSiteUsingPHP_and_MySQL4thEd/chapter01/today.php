<!DOCTYPE html>

<head>
    <title>Today&rsquo;s Date</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
</head>

<body>
    <p>Today&rsquo;s date (according to this web server) is
        <br>
        <?php
        echo date('l, F dS, Y.');
        ?>

        <br>
        <?php
        echo date('Y M D d');
        ?>

        <br>
        <?php
        echo date('Y m d');
        ?>

    </p>
</body>

</html>