#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"output.h"

/** openfile : dimiourgia arxeiou output me kataliksi xI.out vasismeno sto arxeio eisodou x.y */
FILE *openFile(char *name,FILE *f_out)
{
  int i, xlength, namelength;
  char *filename;
  
  xlength=strchr(name,'.')-name;                              /**metraei to mikos tou x*/
  i=1;
  do
  {
    namelength=xlength + log10(i) + 6;                     /**mikos tou onomatos*/
    filename=(char*) malloc (namelength*sizeof(char));    /**desmeusi mnimis gia to onoma*/
    strncat(filename,name,xlength);                       /** filename : periexei to neo onoma */
    sprintf(filename,"%s%d.out",filename,i);              /**dimiourgia arxeiou me kataliksi .out */
   
    f_out=fopen(filename,"r");				/** an to arxeio yparxei, tote dokimazoume to epomeno i */
    if(f_out==NULL) 
    {
      f_out=fopen(filename,"w");			/** to arxeio den yparxei, opote exoyme vrei to onoma tou */
      break;
    }
    i++;
    free(filename);
   } while (f_out!=NULL);
  
  free(filename);  
  return f_out;
}

/** freelist : apodesmeusi twn komvwn apo ti lista */
TokenList *freelist(TokenList *root)
{
  TokenList *current;
  
  while(root!=NULL)
  {
    current=root;
    root=root->next;
    free(current);  
  }
  return root;
  
}

/** freeMemory : apodesmeusi mnimis twn paragwgwn */
void freeMemory(NonTerm *grammar,int size)
{
  int i,j;
  for(i=0;i<size;i++)
  {
    for(j=0;j<grammar[i].gnumber;j++)
    {
      grammar[i].generics[j]=freelist(grammar[i].generics[j]);          /** prwta i apodesmeusi twn komvwn */
    }
  }
}
