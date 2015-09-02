/**Author: Marelas Giwrgos
 * Date:   5/1/2011
 * Description: Paragogi protasewn apo context free grammatiki */

/**Otan pragmatopoieite compile prepei na kanete kai sundesi me ti 
mathimatiki bibliothiki. -lm sto telos tis entolis gia compile */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stack.h"
#include"output.h"

/** dilwseis twn prwtotypwn */

NonTerm *readFile(FILE *fp,NonTerm *grammar, int *size);  
TokenList *createList(TokenList *root,char *word,FILE *fp); 

StackList *generation(FILE *f_out,NonTerm *grammar,int size,StackList *stack); 

int find(NonTerm *grammar,int size,char word[]); 


/** main*/
int main (int argc,char* argv[]){

  NonTerm *grammar;	       /** dynamikos pinakas gia tin apothikeysi tis grammatikis */
  int sizeOfGrammar=0;	       /** plithos twn mi termatikwn stoixeiwn==megethos toy pinaka grammar */
  FILE *fp,*f_out=NULL;        /** deiktes sto arxeio anagnwsis k sto arxeio eksodou antistoixa */
  StackList *stack=NULL;       /** deikths ths stoivas */
  
  if(argc!= 2 )                /** elegxos toy arithmou twn orismatwn */
  {
    printf("lathos arithmos orismatwn\n");
    exit(1);
  }
  
  if( strchr(argv[1],'.') == NULL )  /** elegxos tis morfis arxeiou x.y */
  {
     printf("lathos. den einai sti morfi x.y\n");
     exit(1);
  }
  
  fp=fopen(argv[1],"r");                          /** anoigoume to arxeio ths grammatikhs */
  if(fp==NULL)
  {
    printf("den yparxei to arxeio pou kathorisate\n");
    exit(1);
  }

  f_out= openFile(argv[1], f_out);                /** f_out: to arxeio output */

  grammar=NULL;
  grammar=readFile(fp,grammar,&sizeOfGrammar);    /** diavamsa kai apothikeusi grammatikis */ 

  stack=push(stack,"<start>");			/** prosthetoume to arxiko symvolo <start> sto stack gia na xekinisei h pargwgh */
  stack=generation(f_out,grammar,sizeOfGrammar,stack);  /** paragogh protasewn */
  printf("\n");
  
  /** apodesmeusi ths dynamikhs mnimis pou xrisomopoihse to programma */
  freeMemory(grammar,sizeOfGrammar);
  free(grammar);                                  

  /* close all files */
  fclose(fp);
  if (f_out != NULL) {
    fflush(f_out);
    fclose(f_out);
  }
  
  return(0);
  
}

/** readFile : anagnwsi tis grammatikis apo to arxeio.
Mesa stin readfile kaleitai i createList gia tin apothikeusi tis grammatikis */
NonTerm *readFile(FILE *fp,NonTerm *grammar, int *size)
{
  char word[WORDSIZE];
  int j;
  
  fscanf(fp,"%s",word);
  while(!feof(fp)){
  
    if(strcmp(word,"{")==0){   /** anagnwrisi kanonwn, wste na mh diavazei ta sxolia poy mporei na yparxoyn */
      fscanf(fp,"%s",word);    /** mh termatiko */
      
      /** dynamiki desmeusi mnimis gia ton pinaka apothikeusis tis grammatikis */
      grammar=(NonTerm*) realloc (grammar,(*size + 1)*sizeof(NonTerm));  
      if (grammar==NULL) 
      {
	printf("No memory\n");
	exit(1);
      }
      strcpy(grammar[*size].nonterm,word);
      j=0;
      fscanf(fp,"%s",word);
      while(strcmp(word,"}")!=0){   	
	  grammar[*size].generics[j]=createList(grammar[*size].generics[j],word,fp); /** diavasma kai apothikeysi ths paragogis toy mh termatikoy */
	  fscanf(fp,"%s",word);
	  j++;
      }
      
      grammar[*size].gnumber=j;
      *size = *size + 1;
    }
    fscanf(fp,"%s",word);
    
  }

  return grammar;
}

/** createList : apothikeuei tis paragoges sth lista twn paragwgwn. Kathe neos komvos mpainei sthn arxh ths listas
    epeidi xrisimopoiw th stoiva */
TokenList *createList(TokenList *root,char *word,FILE *fp)
{
  TokenList *new;
  root=NULL;
  
  while(strcmp(word,";")!=0){
    new=(TokenList*)malloc(sizeof(TokenList));    /**dynamiki desmeusi mnimis gia tin lista */
    strcpy(new->token,word);
    new->next=root;
    root=new;
    fscanf(fp,"%s",word);
    }
    return(root);
}

/** generation : dhmioyrgia protasewn apo thn grammatiki poy exei diavastei.
    gia kathe stoixeio poy vgazoume apo sto stack, elegxoyme an einai termatiko.
    Ean einai, tote to grafoume sto arxeio exodou, alliws einai mh termatiko opote 
    vriskoyme to to termatiko ston pinaka twn termatikwn, epilegoume me tyxaio
    tropo mia paragogi, vazoume ola ta symvola thw paragogis sth stoiva kai kanoyme 
    xana to idio apo thn arxh.
*/
StackList *generation(FILE *f_out,NonTerm *grammar,int size,StackList *stack)
 {
   int location;              /**h thesi toy pinaka non terminal (grammar) sthn opoia vrisketai to non terminal */   
   int position;              /**h thesi toy pinaka tvn paragwgwn poy epilegetai me tyxaio tropo */   
   TokenList *current;
   char word[WORDSIZE];
   int linelength=0;          /** linelength: mikos tis seiras poy grafoyme sto arxeio exodou */
   
   srand((int) time(NULL));   /**arxikopoihsh tou seed me vasi ton trexonta xrono */
   stack=pop(stack,word);                     
   while(strcmp(word,"")!= 0) /** oso h stoiva den einai adeia */
   {
      location=find(grammar,size,word);		/** evresi ths thesis toy non terminal */
      if(location<0)     			/** an location<0 tote to word: termatiko, opote to grafoume sto arxeio */
      {
	linelength=linelength+strlen(word)+1;  
	
	if(linelength<=60)
	{
	  if(f_out==NULL)   /** periptwsi ektypwsis stin othoni */
	  {
	    printf("%s ",word);
	  }
	  else              /** ektypwsi sto arxeio .out */
	  {
	    fprintf(f_out,"%s ",word);
	  }
	} 
	else
	{					/** allagh grammhs */
	  linelength=strlen(word)+1;
	  if(f_out==NULL) printf("\n%s ",word);
	  else fprintf(f_out,"\n%s ",word);
	}
      }
      else               /** word: non terminal */
      {
	/** me tin xrisi tis rand epitygxanetai i tyxaia epilogi paragwgwn */
	position= rand()%grammar[location].gnumber;       
	
	/** vazoume ola ta symvola thw paragwghs sth stoiva */
	current=grammar[location].generics[position];
	while(current!= NULL)
	{
	  stack=push(stack,current->token); 
	  current=current->next;	  
	}
      } 
      stack=pop(stack,word);
   }
   
   return stack;
 }

/** find: an to word einai mh termatiko, epistrefei th thesi ston pinaka twn mh termatikwn, alliws -1 */
int find(NonTerm *grammar,int size,char word[])
{
  int i;
  for(i=0;i<size;i++)
  {
    if(strcmp(word,grammar[i].nonterm)==0) return(i);
    
  }
  return(-1);
}




