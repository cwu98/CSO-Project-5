
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


    while ( 1 ) // loop forever
    {
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))

        {

        case ARG:
            if(narg<MAXARG)
                narg++;
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
                runcommand(arg,type);
            }

            if( toktype == EOL )
                return;
            narg = MAXARG;
            break;
        }
    }
}
