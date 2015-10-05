**php-forker** "php-forker" is a program written in C.
I is used to start console PHP scripts in the background from a PHP script serving a web request.

**Problem description.**
The usage of the PCNTL (Process Control support) extension applicable for the task, is not recommended in WEB scripts, and a plain "system()" call from a PHP script creates a zombie shell process:
system('/usr/local/bin/php script.php &');

As a solution, php\_forker demonizes a php-cli process that runs a console php script:
system('/usr/local/bin/php-forker /path/to/script.php arg1');


## Usage: ##
```
system('/usr/local/bin/php-forker /path/to/script.php one_arg '); 
```

Where:
  * /usr/local/bin/php-forker - full path to binary php-forker
  * /path/to/script.php - full path to your php script
  * one\_arg  is the optional parameter for PHP script argument.

Using for hight-calculate or long-time process or conversing with AJAX:
  * WEB pages start baground process and in the parametr point tmp-filename.
  * Baground process make calculate and save in the tmp-filename calc-progress.
  * WEB pages by AJAX show culculate progress from tmp-filename.

## INSTALL ##
1: check the binary php
```
whereis php
>/usr/bin/php
```
2: define PATH constant to binary php in the main.c
```
#define PATH "/usr/bin/php"   // default
```
3: install php-forker to **/usr/local/bin** or change destination in the Makefile
```
make
make install
```

## Example ##
```
/// file example.php  call  process.php

$rand=rand( 1000,9999);
$res=exec ( "/usr/local/bin/php-forker /home/projects/fork/process.php /www/php-forker/$rand" );
if ($res !='Ok' )
     die ('php-forker error');

// some code for point  filename="/www/php-forker/$rand" to AJAX page

```
```
/// file process.php  forked from example.php
if ( isset($argv[1]) )
	$filename = $argv[1];
else {
    syslog(LOG_ERR,"the input parameter is absent");	
    exit;
}

for (  $i=0; $i < $n; $i++ ){
    $f = fopen(  $filename, 'w');	
    fwrite( $f,"ceil(100* $i/$n )");    // save  the percent of calculate process
    fclose($f);

// some hard calculate

}
$f = fopen(  $filename, 'w');   
fwrite( $f,"Ok");    // finalize of the calculate process
fclose($f);
```

use AJAX for read from  filename "/www/php-forker/$rand" we see caculate progress



