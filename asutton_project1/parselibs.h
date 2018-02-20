#ifndef _PARSE_LIBS_H
#define _PARSE_LIBS_H



#define PATHVAR "PATH"
#define	LINE_LEN	512
#define MAX_ARGS	64
#define MAX_ARG_LEN	16
#define	MAX_PATHS	64
#define MAX_PATH_LEN	512
#define WHITESPACE	" .,\t"
#define displayPrompt "SuttonTerm: > " 
#define debug 0


struct command_t
{
  char *name;
  int argcounter;
  char * argv[MAX_ARGS];
};


int parsePath(char *[] );
int parseCommand(char *cLine, struct command_t *) ;

char * lookupPath(char **,char **);



#endif
