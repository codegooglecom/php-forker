<?
$a="[null]";
if ( isset($argv[1]) )
	$a = $argv[1];

$date = date('d-m h:i:s');

$f = fopen( '/tmp/fork_log.txt', 'a+');	
fwrite( $f,"$date argc=$argc cmd=$argv[0]  arg1=$a\n");
fclose($f);

sleep(10);