#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/** synarthseis diaxeirishs ths stoivas. H stoiva einai mia lista sthn opoia kathe komvos mpainei sthn arxh */


/**push: topothetisi stin stoiva toy stoixeiou data */
StackList *push(StackList *stack, char *data)
{
  
  StackList *new; 
  
  new=(StackList *) malloc (sizeof(StackList)); /**dimioyrgia neou komvou sto stack*/
  if(new == NULL)
  {
    printf("Stack overflow");
    exit(1);
  }
  strcpy(new->data,data);                        /**antigrafi tou data sto stack*/
  new->next=stack;                               
  stack=new;                                     
  return(stack);
  
}

/**pop: eksagwgi apo tin stoiva. an yparxei stoixeio sti stoiva, gemizei to data 
        alliws to data einai NULL */
StackList *pop(StackList *stack, char *data)
{
  StackList *current;
  
  strcpy(data,"");                                 /**arxikopoihsh pediou data*/
  if(stack == NULL) return(NULL);
  current=stack;                                   
  strcpy(data,stack->data);
  stack=stack->next;                               /**epomenos komvos*/
  free (current);
  return(stack);
}