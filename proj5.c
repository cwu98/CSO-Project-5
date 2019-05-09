
#include "proj5.h"

/*
 *signal handler for SIGINT
 */
void sigint_handler(int num){
  signal(SIGINT,sigint_handler); 
  printf(" Terminated foreground process \n");
  fflush(stdout);
}


int main()
{
  //  while((pid=waitpid(-1,NULL,WNOHANG))>0){
  // }

  //catch SIGINT signal
  signal(SIGINT,sigint_handler);
    //run the shell until EOF (keyboard Ctrl+D) is detected
  while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}
