#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>

#define BUF_SIZE      200

void hypens(char* dests, char* srcc);
void hypenc(char* desto, char* srcs);
void nooption(char* deste, char* srco);
int mysystem(char* command);
void buildlog(char* buff);
void usageerror(void);
void printhelp(void);
int checkbuildstatus(char* src1, char* dest1);

int un, status,ret;
int srct[BUF_SIZE];
size_t wb;
//char* destt = NULL;
