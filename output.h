#define WORDSIZE 61
#define SIZE     10

typedef struct tokenList {  /** lista me paragwges tis grammatikis */
  char token[WORDSIZE];	    /** lexi tis paragogis (termatikh h mh termatikh) */
  struct tokenList *next;
} TokenList;

typedef struct {            /** orismos tis domis toy pinaka ths grammatikis */
  char nonterm[WORDSIZE];	/** mi termatiko stoixeio */
  TokenList *generics[SIZE];	/** pinakas paragwgwn toy mi termatikoy */
  int gnumber;			/** plithos paragwgwn toy mi termatikoy */
} NonTerm;

/** dilwseis prwtotypwn */
FILE *openFile(char *name,FILE *f_out);  

void freeMemory(NonTerm *grammar,int size); 

TokenList *freelist(TokenList *root);       
