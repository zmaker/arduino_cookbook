<?php
$myfile = fopen("dati.txt", "w") or die("non riesco a creare il file");
date_default_timezone_set('Europe/Rome');

$txt = "[".date("Y-m-d H:i:s")."] - ";

foreach($_POST as $key => $value) {
    $txt .= "(" . $key . "=" . $value . ") ";    
} 

$txt .= "\r\n";

fwrite($myfile, $txt);
fclose($myfile);

//echo ($txt);
?>