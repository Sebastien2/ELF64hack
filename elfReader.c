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



#ifndef TEST
	#define TEST 0
#endif




//Les attributs du ELF que l'on stocke
extern Header header;
int maxLength=100;
int maxArgs=5;


int creerNombre(char * caracs, int length, char endianness)
{
	int charSize=256;
	int res=0;
	if(endianness==1)
	{
		//on lit à l'envers
		for(int i=0; i<length; i++)
		{
			if(caracs[length-1-i]>=0)
			{
				res=(caracs[length-1-i])+(1<<8)*res;
			}
			else
			{
				res=((int)(caracs[length-1-i])+charSize)+(1<<8)*res;
			}
		}
	}
	else if(endianness==2)
	{
		//on lit à l"endroit
		for(int i=0; i<length; i++)
		{
			if(caracs[i]>=0)
			{
				res=(caracs[i])+(1<<8)*res;
			}
			else
			{
				res=((int)(caracs[i])+charSize)+(1<<8)*res;
			}

		}
	}
	if(TEST)
	{
		printf("Nombre renvoit 0x%08x\n", res);
	}

	return res;
}

long creerLongNombre(char * caracs, int length, char endianness)
{
	int charSize=256;
	long res=0;
	if(endianness==1)
	{
		//on lit à l'envers
		for(int i=0; i<length; i++)
		{
			if(caracs[length-1-i]>=0)
			{
				res=(caracs[length-1-i])+(1<<8)*res;
			}
			else
			{
				res=((int)(caracs[length-1-i])+charSize)+(1<<8)*res;
			}
		}

	}
	else if(endianness==2)
	{
		//on lit à l"endroit
		for(int i=0; i<length; i++)
		{
			if(caracs[i]>=0)
			{
				res=(caracs[i])+(1<<8)*res;
			}
			else
			{
				res=((int)(caracs[i])+charSize)+(1<<8)*res;
			}
		}
	}
	if(TEST)
	{
		printf("LongNombre renvoit 0x%08lx\n", res);
	}

	return res;
}


void commandUnknown()
{
	printf("Command unknown. Type help for info\n");
}








void main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("Nombre d'argument incorrect car valant %d\n", argc);
		return;
	}
	char * fileName=argv[1];

	//on ouvre le fichier, lecture en binaire
	FILE *file;
	file=fopen(fileName, "rb+");

	header=readHeader(file);
	//afficherHeader(header);

	//Lecture de la table des sections : TODO utiliser malloc pour optimiser l'usage d'un gros espace?
	Elf64_Shdr sectionHeaders[header.nbEntriesSectionHeader];


	readSections(file, header.nbEntriesSectionHeader, sectionHeaders);


	char exit[]="exit";
	char help[]="help";
	char list[]="list";
	char sections[]="sections";
	char programs[]="programs";
	char raw[]="raw";
	char sectionHeaders_word[]="sectionHeaders";
	char section[]="section";
	char section_option[]="-section";
	char sectionNames[]="sectionNames";
	char headerDetails[]="headerDetails";

	char * sectionName;

	char * argsLine[maxArgs]; //Maximum number of arguments
	char mot0[maxLength];
	char mot1[maxLength];
	char mot2[maxLength];
	char mot3[maxLength];
	char mot4[maxLength];
	argsLine[0]=mot0;
	argsLine[1]=mot1;
	argsLine[2]=mot2;
	argsLine[3]=mot3;
	argsLine[4]=mot4;
	int nbArgs;

	char line[maxLength];



	int index;



	//Boucle de commande
	while(strcmp(argsLine[0], exit)!=0)
	{
		header=readHeader(file);
		readSections(file, header.nbEntriesSectionHeader, sectionHeaders);


		printf("\033[1;35m(CheshireCat) \033[0m");
		fgets(line, maxLength, stdin);
		nbArgs=countNumberWords(line);

		listWords(line, nbArgs, argsLine);
		if(TEST)
		{
			printf("Nombre d'arguments fournis: %d\n", nbArgs);
			printf("Liste des arguments fournis:\n");
			for(int i=0; i<maxArgs; i++)
			{
				printf("arg%d: %s\n", i, argsLine[i]);
			}
		}

		//on determine la commande recherchee
		if(nbArgs>maxArgs)
		{
			tooManyArguments();
		}
		else if(strcmp(argsLine[0], help)==0)
		{
			globalHelpCommand();
		}
		else if(nbArgs==1)
		{
			if(strcmp(argsLine[0], headerDetails)==0)
			{
				afficherHeader(header);
			}
		}
		else if(nbArgs==2)
		{
			if(strcmp(argsLine[0], list)==0)
			{
				if(strcmp(sections, argsLine[1])==0)
				{
					if(TEST)
					{
						printf("Demande d'affichage de la liste des sections\n");
					}

					for(int i=0; i<header.nbEntriesSectionHeader; i++)
					{
						afficherSectionHeader(file, sectionHeaders, i);
					}
				}
				else if(strcmp(programs, argsLine[1])==0)
				{
					if(TEST)
					{
						printf("Demande d'affichage de la liste des programs\n");
					}

				}
				else if(strcmp(sectionNames, argsLine[1])==0)
				{

					printf("Liste des noms de section: \n");
					for(int i=0; i<header.nbEntriesSectionHeader; i++)
					{
						getNameSection(sectionName, file, sectionHeaders, i);
						printf("%d: %s\n", i, sectionName);
					}
				}
				else
				{
					commandUnknown();
				}
			}
			else if(strcmp(raw, argsLine[0])==0)
			{
				if(strcmp(sectionHeaders_word, argsLine[1])==0)
				{
					if(TEST)
					{
						printf("raw sectionHeaders\n");
					}
					for(int i=0; i<header.nbEntriesSectionHeader; i++)
					{
						afficherRawSectionHeader(sectionHeaders, i);
					}
				}
				else
				{
					commandUnknown();
				}
			}
		}
		else if(nbArgs==3)
		{
			if(strcmp(section, argsLine[0])==0)
			{
				if(TEST)
				{
					printf("3 args, section\n");
				}
				lectureDetailSectionEntree(header, sectionHeaders, file, argsLine, nbArgs);
			}
			else if (strcmp(raw, argsLine[0])==0)
			 {
				 if(strcmp(section_option, argsLine[1])==0)
 				{
 					sectionName=argsLine[2];
					//Trouver le numero de la section, puis afficher les raw data
					index=trouverIndexSectionNom(file, sectionName, sectionHeaders, header.nbEntriesSectionHeader);
					if(TEST)
					{
						printf("Index: %d\n", index);
					}
					if(index<0)
					{
						printf("Ce nom de section n'existe pas dans ce fichier\n");
					}
					else
					{

						readRawSection(index, file, sectionHeaders, header);

					}

 				}
			}
		}




		printf("\n");
	}



	/*
	for(int i=0; i<header.nbEntriesSectionHeader; i++)
	{
		afficherSectionHeader(file, sectionHeaders, i);
	}
	*/

	//getNameSection(file, sectionHeaders, 2);


	fclose(file);

}
