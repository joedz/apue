#include "apue.h"

int		globvar = 6;		/* external variable in initialized data */
char	buf[] = "a write to stdout\n";

int
main(void)
{
	int		var;		/* automatic variable on the stack */
	pid_t	pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n");	/* we don't flush stdout */

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {		/* child */
		globvar++;				/* modify variables */
		var++;
	}

	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
	  var);
	exit(0);
}

/*
./fork1

a write to stdout
before fork
pid = 83310, glob = 7, var = 89
pid = 83309, glob = 6, var = 88

root@10027f15d9e9:~/apue/proc# ./fork1 > file.tmp
root@10027f15d9e9:~/apue/proc# cat file.tmp 
a write to stdout
before fork
pid = 83913, glob = 7, var = 89
before fork
pid = 83912, glob = 6, var = 88

*/

