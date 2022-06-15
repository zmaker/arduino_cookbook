<?php

$n = $_GET["nome"];
$t = $_GET["temp"];
$h = $_GET["hum"];

?>
<!DOCTYPE html>
<html> 
    <head>
        <title>Ricevo dati in GET</title>
    </head>
    
    <body>
        <h1>I dati sono:</h1>
        <p>nome: <?php echo($n); ?></p><br/>
        <p>temp: <?php echo($t); ?></p><br/>
        <p>hum: <?php echo($h); ?></p><br/>
    </body>
</html>