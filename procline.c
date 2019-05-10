
#include "proj5.h"


/* shell input line */
int procline(void)
{

    char *arg[MAXARG + 1];  // pointer array for runcommand
   
    /*
     * Here is where I fixed BUG 1, the narg value should be initialized to 0, not just declared.
     * Declaring without initializing will lead to undefined behavior
     */
    int narg = 0  ;              // number of arguments 
    int toktype;            // type of token in command
    int type;               // type =  FOREGROUND or BACKGROUND
    
    const char* home_dir="HOME"; //home directory 
    char * dir_pre = "/";
    while ( 1 ) // loop forever
    {
      
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))

        {

        case ARG:
            if(narg<MAXARG)
                narg++;
	    /*
	     *this is where I implemented code for BUG 3
	     *typing exit into shell comand line exits the shell
	     */
	    if (strcmp(arg[0],"exit")==0){
	      exit(0);
	    }
	  
	    break;

        case EOL:
        case SEMICOLON:
        case AMPERSAND:
            if(toktype == AMPERSAND)
                type = BACKGROUND;
            else
                type = FOREGROUND;

	   
            if(narg != 0)
            {
                arg[narg] = 0;

		/*
		 *fix for BUG 2
		 *this is where I implemented the cd command using chdir() function
		 */
		if (strcmp(arg[0],"cd")==0){
		  if (arg[1] == NULL){ //go to home directory
		    chdir(getenv(home_dir));
		  }
		  else if (chdir(strcat(arg[1],dir_pre))!=0){ //append "\" to path_name
		    //error message, chdir failed
		    printf("Error: Not a directory \n");
		     return;
		  }
		}

		else{
		runcommand(arg,type);
		}            
	    }

            if( toktype == EOL )
                return;
	    /*
	     *another fix for BUG 1 is to reset narg to 0
	     */
	    narg = 0;
            break;
	
        }
    }
}
