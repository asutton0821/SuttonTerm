#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "parselibs.h"

int parsePath(char * dirs[]){
  char * token = NULL;
  char * line = getenv(PATHVAR);
  char * buffer = NULL;
  char * hbuffer = NULL;
  const char * sep_chars = ":";
  int n_parsed = 0;
  if(line == NULL){
    printf( "PATH environment variable not in environment\n" );
    return 1; 
  }
  memset( dirs, 0, MAX_ARGS * sizeof(char * )); //sets dirs to 0, with the size of MAX_ARGS * char * 
  buffer = strdup ( line );
 //  printf("buffer is %s", buffer);
  if(  !(hbuffer =  buffer)){
    printf("We seem to be out of memory! \n");
    return 2; 
  }
   for( token = strsep( &buffer, sep_chars ) ; token != NULL ; token = strsep( &buffer, sep_chars ) )
    {
        if( n_parsed > MAX_ARGS ) //make sure that path directories don't exceed MAX_ARGS
        {
            printf( "WOAH THERE! You have way too many paths! Try clearing some! \n" );
            return( 3 );
        }
        dirs[n_parsed] = token;
        n_parsed++;
        if(debug){
           printf("%s\n",token); //prints the path names
        }
    }
  return 0;
}



int parseCommand(char *cmdLine, struct command_t *command)  //takes the command, parses it down, and then allows it to be run. 
{
  int  argcounter = 0;
  char **cmdLinePtr =  &cmdLine;
    char * buffer; 
    while((buffer = strsep(&cmdLine, WHITESPACE)) != NULL){
        printf("%s\n",buffer);
	 if(strlen(buffer) > 0){
        command->argv[argcounter++] = buffer;
      }
    }

	if(debug){
		printf("Command->argv[%d--]: %s\n ", argcounter, command->argv[argcounter - 1]);
	}
    command->argv[argcounter--] = NULL;
    command->argcounter = argcounter;


if(debug){
  printf("Command inputted: %s, # Arguments: %d\n",*command->argv, command->argcounter+1);
}
    return  4;		
}


char *lookupPath(char **argv,char **dir)
{
    char *result = NULL;
    char pName[MAX_PATH_LEN];
    int i;

   if( *argv[0] == '/' ) //if absolute path
   {
     result = (char *) malloc(strlen(argv[0])+1); //malloc result to the size of a string
     strcpy(result, argv[0]); //copy argv into result (so if /bin/ls is the com$
     //free(result);
     return result; //return result
   }
    for( i = 0 ; i < MAX_PATHS ; i++ ) //as long as i is less than MAX_PATHS, i$
    {
      if(dir[i] == NULL){ //if the array of directories is somehow null, break $
        break;
      }
      strcpy(pName, dir[i]); //copy dir[i] into parseCommand
      strcat(pName, "/"); //concatenate / into pname.
      strcat(pName, argv[0]); //concatenate argv[0] into pName

	  if(debug){
		  printf("Path: %s\n", pName );
	  }
      /*
      What this does is take the paths inside of the PATH environment, append a$
      For instance, into the shell if the user types "ls" then the path list is$
      I have to add those. After that, I can then append ls onto it to make a c$
      access is called to see if the path exists. And if so, then the path is r$

      */
     if(access(pName, X_OK | F_OK) != -1) //check execute permissions and that $
        {
            result = (char *) malloc(strlen(pName)+1); //malloc a string
            strcpy(result, pName); //copy the pName to the result
            //free(result);
	    return result;              //return result
        }
    }
    printf( "%s command not found\n", argv[0] ); //print using a standard error$
    return NULL;
}




