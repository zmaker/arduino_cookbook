<?php
$myfile = fopen("dati.txt", "a") or die("non posso creare il file");

date_default_timezone_set('Europe/Rome'); 

$txt = "[" . date("Y-m-d H:i:s") . "] ";

foreach($_GET as $key => $value){
   $txt .= "(" . $key . "=" . $value . ") ";
}
$txt .= "\r\n";

fwrite($myfile, $txt);
fclose($myfile);
?>