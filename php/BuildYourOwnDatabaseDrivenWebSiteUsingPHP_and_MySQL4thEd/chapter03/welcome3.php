<!DOCTYPE html>

<head>
    <title>Query String Link Example</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
</head>

<body>
    <p>
        <?php
        $firstname = $_GET['firstname'];
        $lastname = $_GET['lastname'];
        echo 'Welcome to our web site, ' .
            htmlspecialchars($firstname, ENT_QUOTES, 'UTF-8') . ' ' .
            htmlspecialchars($lastname, ENT_QUOTES, 'UTF-8') . '!';
        ?>
    </p>
</body>

</html>