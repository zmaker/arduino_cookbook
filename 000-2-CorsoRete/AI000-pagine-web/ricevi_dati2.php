<?php

$n = $_POST["nome"];
$t = $_POST["temp"];
$h = $_POST["hum"];

?>
<!DOCTYPE html>
<html>
    <head>
        <title>Ricevo dati in POST</title>
    </head>

    <body>
        <h1>I dati sono:</h1>
        <p>nome: <?php echo($n); ?></p><br/>
        <p>temp: <?php echo($t); ?></p><br/>
        <p>hum: <?php echo($h); ?></p><br/>
    </body>
</html>
