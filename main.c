

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <stdarg.h>
#include <errno.h>
#define PATH "/usr/bin/php"
#define PHP  "php"

 int demonize(){

        int  fd;

    switch (fork()) {
    case -1:
         fprintf( stderr, "demonize fork failed");
        return -1;

    case 0:
        break;

    default:
        //Free();
        exit(0);
    }

    int pid = getpid();

    if (setsid() == -1) {
         fprintf( stderr, "setsid() failed");
        return -1;
    }

    umask(0);

    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        fprintf( stderr, "open(\"/dev/null\") failed");
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        fprintf( stderr,"dup2(STDIN) failed");
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        fprintf( stderr,"dup2(STDOUT) failed");
        return -1;
    }

    if (dup2(fd, STDERR_FILENO) == -1) {
        fprintf( stderr, "dup2(STDERR) failed");
        return -1;
    }

    if (fd > STDERR_FILENO) {
        if (close(fd) == -1) {
            fprintf( stderr,  "close() failed");
            return -1;
        }
    }

    return pid;
}


int main (int argc, const char * argv[]) {
	if (argc <2){
		printf("usage: %s </full/path/phpscript.php> [param_for_php] \n", argv[0]);
		return 0;
	}

   size_t pid = fork();
   if(pid < 0){
		printf("fork abort\n");
		return 0;
     }
    
    if (pid == 0) {
			printf("Ok\n");
			return 0;
    } 
	
	size_t res =  demonize();
	if (res < 0 ){
		printf("demonize Abort! \n");
		return 0;
	}
	if(argc==2)	
		res =execl( PATH, PHP, argv[1]);
	if(argc==3)	
		res =execl( PATH, PHP, argv[1], argv[2]);
		
	if (res < 0) {
		syslog(LOG_ERR, "[forker] abort: exec php script[%s] error %s\n", argv[1],  strerror( errno));
		return 0;
	}
	
	    return 0;
}
