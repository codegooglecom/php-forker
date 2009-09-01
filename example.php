<?
//         path to php_forker           path to your script       some param
$r=exec ( "/usr/local/bin/php-forker /home/projects/fork/sleep.php 123" );
var_dump($r );

?>