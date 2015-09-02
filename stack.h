#define WORDSIZE 61

typedef struct stackList{  /** domi tis stoivas */
  char data[WORDSIZE];
  struct stackList *next;
} StackList;

/**dilwseis prwtotypwn gia dimiourgia stoivas*/
StackList *push(StackList *stack, char *data);  
StackList *pop(StackList *stack, char *data);   

