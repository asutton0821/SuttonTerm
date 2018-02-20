/*

Colson Sutton 
Copyright 2018

Following the skeleton from the book, this program will create a miniature shell that will allow the user to input executable commands. 
If found in PATH, then the program will execute and run the command for the user, otherwise the user will be prompted with a message stating
that it cannot be found. Building upon homework #6, we are able to access the directory using the access() function and make sure that the directory 
exists in one of the path. As per the requirements, using fork(), wait(), and execv(), we are able to become the child process (seperate ourself from the parent), 
run the program, wait for it to finish, and then go back to the parent. 

To parse the command, we use a function called readCommand. this allows us to parse the STDIN (standard input, or input from the keyboard) using fgets (straying away from the apparent
more dangerous gets, as learned the hard way). Once the command is read, a null terminator is added to the end of the string, otherwise causing havoc by gathering other memory garbage. 


Referring to the header file, if debug is set to 1 (or true, in this case), all of the debug statements in my program will fire. 


*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "suttonterm.h"
#include "parselibs.h"


void printScreenPrompt(){
  printf("%s ", displayPrompt);
}

void readCommand(char *buffer) 
{
    fgets(buffer, LINE_LEN, stdin);
    buffer[strlen(buffer)-1] = '\0';  //must set the last of the length to null value
}

int main() 
{
    char commandLine[LINE_LEN];
    char *pathv[MAX_PATHS];
    int i;
    int chPID;		
    int stat;		
    
    struct command_t command;


    
    parsePath(pathv);
    while(1==1) //never ending loop
    {
      
      printScreenPrompt(); //display prompt 

      readCommand(commandLine); //reads the command prompt from stdin 

      if( (strcmp(commandLine, "exit") == 0) ||
          (strcmp(commandLine, "quit") == 0)) //if user types quit or exit, then quit
      {
           break;	
      }

      parseCommand(commandLine, &command); //parse the command (see parseCommand documentation)

      command.name  = lookupPath(command.argv, pathv); //set the command.name to the lookupPath name that works 
       
      if(debug){
        
        printf("Name: %s, ", command.name);
        printf("Arguments: ");
        for(int j=0; j<=command.argcounter;j++){
		
          printf("%s ", command.argv[j]);
}
       printf("\n");
      }
        if((chPID = fork()) == 0) //fork, running as child. 
        {
            execvp(command.name, command.argv); //execute the command with the associated arguments 
        }
        pid_t thisChPID = wait(&stat); //wait for the process to finish before allowing the parent process to run. 
        if(debug){
          printf("State change took %d to complete! \n", stat);
        }
	free(command.name);
  
  }
  free(pathv[0]);
}
