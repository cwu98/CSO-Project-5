
#include "proj5.h"

/*
 *fix for BUG 4
 *signal handler for SIGINT
 */
void sigint_handler(int num){
  signal(SIGINT,sigint_handler); 
  printf(" \n");
  
}

/*
 *fix for BUG 5
 *signal handler for SIGCHLD
 */
void sigchld_handler(int num){
  int child_status;
  pid_t pid;
  while(pid=(waitpid(-1,&child_status,0))>0){
}
  //  printf("reaped\n"); 
}

int main()
{
  

  //catch SIGINT signal
  signal(SIGINT,sigint_handler);
  
  //catch SIGCHLD signal, reap zombie processes
   signal(SIGCHLD,sigchld_handler);
 
 //run the shell until EOF (keyboard Ctrl+D) is detected
  while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}
