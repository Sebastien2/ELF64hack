#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ELFREADER
	#define ELFREADER "elfReader.h"
	#include ELFREADER
#endif
#ifndef HEADER
	#define HEADER "header.h"
	#include HEADER
#endif
#ifndef STRUCTURE
	#define STRUCTURE "Structure.h"
	#include STRUCTURE
#endif
#ifndef SECTION
	#define SECTIONS "section.h"
	#include SECTIONS
#endif
#ifndef HELP
	#define HELP "help.h"
	#include HELP
#endif
#ifndef PARSER
	#define PARSER "parser.h"
	#include PARSER
#endif
#ifndef SECTIONSPECIFIC
	#define SECTIONSPECIFIC "sectionSpecific.h"
	#include SECTIONSPECIFIC
#endif


int test=0;


extern int maxLength;
extern int maxArgs;



int countNumberWords(char * text)
{
  int len=0;
  int i=0;
  char car=text[0];
  //Calcule la longueur du texte, sans l'argument final
  while(car!=0 && car !=10)
  {
    len+=1;
    i+=1;
    car=text[i];
  }

  int count=0;
  for(int j=0; j<len; j++)
  {
    if(text[j]==32 && text[j+1]!=32 && text[j+1]!=10)
    {
      count+=1;
    }
  }
  if(text[0]!=32 && text[0]!=10)
  {
    count+=1;
  }

  return count;

}






void listWords(char * text, int nb,  char ** argsLine)
{
  for(int k=0; k<maxArgs; k++)
  {
    argsLine[k][0]=0;
  }
  int m=maxArgs;  //Nb max d'arguments
  if(nb<maxArgs)
  {
    m=nb;
  }

  int len=0;
  int i=0;
  char car=text[0];
  //Calcule la longueur du texte, sans l'argument final
  while(car!=0 && car !=10)
  {
    len+=1;
    i+=1;
    car=text[i];
  }

  i=0;
  int debut=1;
  int count=0;
  for(int j=0; j<len; j++)
  {
    car=text[j];
    if(count<m)
    {
      if(car!=10 && car !=32 && debut==1)
      {
        if(test)
        {
          printf("1");
        }

        //On commence un nouveau mot

        argsLine[count][i]=car;
        debut=0;
        i+=1;
      }
      else if((car==10 || car ==32) && debut==1)
      {
        if(test)
        {
          printf("2");
        }
        i=0; //on s'apprete a commencer un nouveau mot
      }
      else if((car==10 || car ==32) && debut==0)
      {
        if(test)
        {
          printf("3");
        }
        argsLine[count][i]=0;  //Fin de string
        i=0;
        debut=1; //on tombe sur un nouvel espace
        count+=1;

      }
      else if(car!=10 && car!=32 && debut==0)
      {
        if(test)
        {
          printf("4");
        }
        //On continue un mot
        argsLine[count][i]=car;
        i+=1;

      }
    }
  }

  //Dernier carac
  if(count<maxArgs)
  {
    argsLine[count][i]=0;
  }
}






int isPrefix(char * mot, char * prefix)
{
	int res=1;
	char car=prefix[0];
	int i=0;
	while(car!=0 && car!=10 && mot[i]!=0 && res==1)
	{
		if(car!=mot[i])
		{
			res=0;
		}
		i+=1;
		car=prefix[i];
	}

	return res;
}
