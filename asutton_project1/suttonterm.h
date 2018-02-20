#ifndef _SUTTONTERM_H
#define _SUTTONTERM_H



/*

After repeatedly getting 'function is not a prototype definition and several half hours on stack overflow, i finally figured out that a protype looks like this!
It only includes the type and not the same variable name like I originally thought! 

*/


void printScreenPrompt(void);
void readCommand(char *); 
int main(void); //if this is even needed... 

#endif
