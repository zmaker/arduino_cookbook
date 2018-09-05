<?php
$to = $_GET['to'];
$subject = "prova invio email";
$message = $_GET['msg'];
$headers = "From: paolo@zeppelinmaker.it/r/n";
mail ($to, $subject, $message, $headers);
?>
