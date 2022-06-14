<?php
$tm = date('s');
$tm = $tm % 3;
if ($tm != 0) {
  echo("led=on");   
} else {
  echo("led=off");
}
?>