
all: 
	gcc -o php-forker main.c
install :
	cp php-forker /usr/local/bin
