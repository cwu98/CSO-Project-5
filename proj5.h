#ifndef PROJECT5_H
#define PROJECT5_H


#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

#define EOL       1   /*end of line*/
#define ARG       2   /* normal arguments */
#define AMPERSAND 3
#define SEMICOLON 4
#define PONDKEY   5   /*for pondkey*/
#define PIPE      6   /*for pipe*/

#define MAXARG 512   /* max. no. command args*/
#define MAXBUF 512   /* max. length input line */

#define FOREGROUND  0
#define BACKGROUND  1

#define PROMPT  "sh201>  "
#define SHELL_NAME  "sh201"

int procline(void);

int userinput( ) ;

int gettok(char **outptr) ;

int runcommand(char **cline, int where) ;

int sh_cd(char **args) ;

int sh_exit() ; 

void sigint_handler(int num);

void sigchld_handler(int num);

#endif // PROJECT4_H


