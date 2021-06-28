<?php
$myfile = fopen("dati.txt", "w") or die("Unable to open file!");
$txt = "sensor:" . $_GET["sens"];
fwrite($myfile, $txt);
fclose($myfile);
?>