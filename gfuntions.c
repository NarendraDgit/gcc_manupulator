#include "hfile.h"
/* This function gives you assembly file */
void hypens(char* dests, char* srcc)
{
	struct stat sb;
	char comm[BUF_SIZE], buff[BUF_SIZE];

	status = checkbuildstatus(srcc, dests);
	sprintf(comm, "gcc -S -o %s %s", dests, srcc);
	ret = mysystem(comm);
	if(ret == -1)
	{
		perror("mysystem");
	}

	if(stat(dests, &sb) != 0)
	{
		perror("hypens");
	}
	sprintf(buff, "%.22s:%s is created.\n", ctime(&(sb.st_ctime)), dests);
	buildlog(buff);

}

/* This function gives you object file */
void hypenc(char* desto, char* srcs)
{
	struct stat sb;
	char comm[BUF_SIZE], buff[BUF_SIZE];

	status = checkbuildstatus(srcs, desto);
	hypens("internal.s", srcs);
	sprintf(comm, "as -o %s internal.s", desto);
	ret = mysystem(comm);
	if(ret == -1)
	{
		perror("mysystem");
	}

	if(stat(desto, &sb) != 0)
		perror("hypenc");
	sprintf(buff, "%.22s:%s is created\n", ctime(&(sb.st_ctime)), desto);
	buildlog(buff);

	memset(&buff, 0, BUF_SIZE);
	un = unlink("internal.s");
	sprintf(buff, "%.22s:internal.s is deleted\n", ctime(&(sb.st_ctime))); 
	buildlog(buff);
}

/* This function gives you exe file */
void nooption(char* deste, char* srco)
{
	struct stat sb;
	char comm[BUF_SIZE], buff[BUF_SIZE];

        status = checkbuildstatus(srco, deste);
        hypenc("internal1.o", srco);

	sprintf(comm, "ld -o %s -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 internal1.o -e main", deste);
	ret = mysystem(comm) == -1;
	if(ret == -1)
	{
		perror("mysystem");
	}
	
	if(stat(deste, &sb) != 0)
	{
		perror("stat");
	}

	sprintf(buff, "%.22s:%s is created.\n", ctime(&(sb.st_ctime)), deste);
	buildlog(buff);

	memset(buff, 0, BUF_SIZE);
	sprintf(buff, "%.22s:internal1.o is deleted\n", ctime(&(sb.st_ctime)));
	un = unlink("internal1.o");
	buildlog(buff);
}

int mysystem(char* command)
{
	pid_t childPid;
	int status;

	switch(childPid = fork())
	{

		case -1: /* Error */
			printf("Error in mysystem()\n");
			return (-1);

		case 0:
			execlp("/bin/sh", "sh", "-c", command, (char*)NULL);
			_exit(127);

		default: /* Parent */
			if(waitpid(childPid, &status, 0) == -1)
				return (-1);
			else
			{
				printf("Please wait...\n");
				sleep(2);
				return(status);
			}
	}
}

/* This function check the status of files, it present or not */
int checkbuildstatus(char* src1, char* dest1)
{
	char buff[50]; 
	char outstr[BUF_SIZE];
	struct stat sb, sb1;
	int fd;
	time_t timem, timec;
	
	if(access(dest1, F_OK) != 0)
	{
		return(0);
	}
	
	stat(src1, &sb);
	stat(dest1, &sb1);
	timem = sb.st_mtime;
	timec = sb1.st_ctime;

	if(timec > timem)
	{
		stat(dest1, &sb1);
		printf("%s this file is alredy present and updated\n", dest1);
		sprintf(buff, "%.22s is upto data", ctime(&timec));

		sprintf(outstr, "%.22s:%s is upto date.\n", ctime(&timec), dest1);
		buildlog(outstr);
	}
	else
	{
		un = unlink(dest1);
		sprintf(outstr, "%.22s:%s is deleted.\n", ctime(&(sb.st_ctime)), dest1);
		strcat(outstr, buff);
		buildlog(outstr);
	}
	return (0);
}

/* This function create logs in Build.log file */
void buildlog(char* buff)
{
	size_t slen = 0;
	int fd;

	slen = strlen(buff);
	fd = open("Build.log", O_RDWR | O_CREAT | O_APPEND, 0644);
	if(fd == -1)
	{
		fprintf(stderr, "open:Build.log:%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	wb = write(fd, buff, slen);
	close(fd);

}

void usageerror(void)
{
	printf("mygcc:\033[1;31m fatal error: \033[0m no input files\n");
	printf("compilation terminated.\n");

}

void printhelp(void)
{
	puts("Usage: mygcc[options] file...");
	puts("Options");
	printf("-S\tCompile only; do not assemble or link.\n");
	printf("-o<file>\tPlace the output into <file>.");
	printf("-h Display this information\n");
}

