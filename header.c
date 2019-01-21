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





Header readHeader(FILE * file)
{
	fseek(file, 0, SEEK_SET);
	if(TEST==1)
	{
		printf("-----------------Description du header en mode TEST-------------\n\n");

	}




	//Type de fichier
	int first=fgetc(file);
	if(TEST==1)
	{
		printf("Nombre magique (1 char): 0x%02x\n", first);

	}
	char l1=fgetc(file);
	char l2=fgetc(file);
	char l3=fgetc(file);
	if(TEST==1)
	{
		printf("Type de fichier (3 char): %c%c%c\n", l1, l2, l3);

	}

	//32 ou 64 bit format
	char bitFormat=fgetc(file);
	if(TEST==1)
	{
		if(bitFormat==1)
		{
			printf("Bit format du fichier (1 char): 32 bits\n");
		}
		else if(bitFormat==2)
		{
			printf("Bit format du fichier (1 char): 64 bits\n");
		}
		else
		{
			printf("Bit format du fichier (1 char): ERREUR, valeur erronée\n");
		}
	}



	//endianness
	char endianness=fgetc(file);
	if(TEST==1)
	{
		if(endianness==1)
		{
			printf("Endianness (1 char): little endian\n");
		}
		else if(endianness==2)
		{
			printf("Endianness (1 char): big endian\n");
		}
		else
		{
			printf("Endianness (1 char): ERREUR, valeur erronée valant 0x%02x\n", endianness);
		}
	}


	//version of ELF
	char elfVersion=fgetc(file);
	if(TEST==1)
	{
		if(elfVersion==1)
		{
			printf("Version de ELF utilisée (1 char): 1\n");
		}
		else
		{
			printf("Version de ELF utilisée (1 char): ERREUR, numero non reconnu valvant 0x%02x\n", elfVersion);
		}
	}



	//OS identification
	char osId=fgetc(file);
	if(TEST==1)
	{
		printf("Numero identifiant l'OS (1 char): 0x%02x\n", osId);

	}

	//OS detailed identification
	char osId2=fgetc(file);
	if(TEST==1)
	{
		printf("Numero identifiant en detail l'OS (1 char): 0x%02x\n", osId2);

	}

	//7 char non utilises
	char unused1=fgetc(file);
	char unused2=fgetc(file);
	char unused3=fgetc(file);
	char unused4=fgetc(file);
	char unused5=fgetc(file);
	char unused6=fgetc(file);
	char unused7=fgetc(file);
	if(TEST==1)
	{
		printf("Non utilisés dans la spécification ELF (7 char): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", unused1, unused2, unused3, unused4, unused5, unused6, unused7);

	}

	//Type de ficher objet
	char fileType[2];
	fileType[0]=fgetc(file);
	fileType[1]=fgetc(file);
	int fType=creerNombre(fileType, 2, endianness);
	if(TEST==1)
	{
		switch(fType)
		{
			case 0:
				printf("Type de fichier objet (2 char): ET_NONE , 0\n");
				break;
			case 1:
				printf("Type de fichier objet (2 char): ET_REL , 1\n");
				break;
			case 2:
				printf("Type de fichier objet (2 char): ET_EXEC , 2\n");
				break;
			case 3:
				printf("Type de fichier objet (2 char): ET_DYN , 3\n");
				break;
			case 4:
				printf("Type de fichier objet (2 char): ET_CORE , 4\n");
				break;
			case 0xfe00:
				printf("Type de fichier objet (2 char): ET_LOOS , 0xfe00\n");
				break;
			case 0xfeff:
				printf("Type de fichier objet (2 char): ET_HIOS , 0xfeff\n");
				break;
			case 0xff00:
				printf("Type de fichier objet (2 char): ET_LOPROC , 0xff00\n");
				break;
			case 0xffff:
				printf("Type de fichier objet (2 char): ET_HIPROC , 0xffff\n");
				break;
			default:
				printf("Type de fichier objet (2 char): ERREUR, inconnu car valeur obtenue=0x%02x\n", fType);
				break;
		}
	}


	//target instruction set
	char targetInstruction[2];
	targetInstruction[0]=fgetc(file);
	targetInstruction[1]=fgetc(file);
	int targetInst=creerNombre(targetInstruction, 2, endianness);
	if(TEST==1)
	{
		printf("Target instruction set (2 char): 0x%02x\n", targetInst);

	}


	//Fixed by original version of ELF
	char fixedNumber[4];
	for(int i=0; i<4; i++)
	{
		fixedNumber[i]=fgetc(file);
	}
	int fixedN=creerNombre(fixedNumber, 4, endianness);
	if(TEST==1)
	{
		printf("Fixed number in original ELF specification (4 char): 0x%02x", fixedN);
		if(fixedN!=1)
		{
			printf("ERREUR: le nombre doit valoir 1");
		}
		printf("\n");

	}

	//memory address where the file starts executing
	char execAddress[4*bitFormat];
	for(int i=0; i<4*bitFormat; i++)
	{
		execAddress[i]=fgetc(file);
	}
	long execInitAddress= creerLongNombre(execAddress, 4*bitFormat, endianness);
	if(TEST==1)
	{
		printf("Adresse (en offset) de début de l'éxécution du fichier (4 char pour 32-bit, 8 char pour 64-bit): 0x%08lx\n", execInitAddress);

	}


	//memory address for start of the program header file
	char programAddress[4*bitFormat];
	for(int i=0; i<4*bitFormat; i++)
	{
		programAddress[i]=fgetc(file);
	}
	long programInitAddress= creerLongNombre(programAddress, 4*bitFormat, endianness);
	if(TEST==1)
	{
		printf("Adresse (en offset) de début du program header table (4 char pour 32-bit, 8 char pour 64-bit): 0x%08lx\n", programInitAddress);

	}

	//memory address for start of the section header file
	char sectionAddress[4*bitFormat];
	for(int i=0; i<4*bitFormat; i++)
	{
		sectionAddress[i]=fgetc(file);
	}
	long sectionInitAddress= creerLongNombre(sectionAddress, 4*bitFormat, endianness);
	if(TEST==1)
	{
		printf("Adresse (en offset) de début du section header table (4 char pour 32-bit, 8 char pour 64-bit): 0x%08lx\n", sectionInitAddress);

	}

	//Variously interpreted, depending on the machine
	char variousInterpretation[4];
	for(int i=0; i<4; i++)
	{
		variousInterpretation[i]=fgetc(file);
	}
	long variousInterp=creerLongNombre(variousInterpretation, 4, endianness);
	if(TEST==1)
	{
		printf("Valeur interprétée de manière variable suivant la machine (4 char): 0x%04lx\n", variousInterp);

	}

	//Size of this header
	char sizeHeader[2];
	for(int i=0; i<2; i++)
	{
		sizeHeader[i]=fgetc(file);
	}
	int sizeHead=creerNombre(sizeHeader, 2, endianness);
	if(TEST==1)
	{
		printf("Taille de ce header (2 char): 0x%02x\n", sizeHead);

	}

	//Size of a program header table entry
	char sizeProgramEntry[2];
	for(int i=0; i<2; i++)
	{
		sizeProgramEntry[i]=fgetc(file);
	}
	int sizeProgEntry=creerNombre(sizeProgramEntry, 2, endianness);
	if(TEST==1)
	{
		printf("Taille d'une entrée de la program header table (2 char): 0x%02x\n", sizeProgEntry);

	}

	//Number of entries in the program header table
	char nbEntriesProgram[2];
	for(int i=0; i<2; i++)
	{
		nbEntriesProgram[i]=fgetc(file);
	}
	int nbEntriesProg=creerNombre(nbEntriesProgram, 2, endianness);
	if(TEST==1)
	{
		printf("Nombre d'entrée dans la program header table (2 char): 0x%02x\n", nbEntriesProg);

	}

	//Size of a section header table entry
	char sizeSectionEntry[2];
	for(int i=0; i<2; i++)
	{
		sizeSectionEntry[i]=fgetc(file);
	}
	int sizeSecEntry=creerNombre(sizeSectionEntry, 2, endianness);
	if(TEST==1)
	{
		printf("Taille d'une entrée de la section header table (2 char): 0x%02x\n", sizeSecEntry);

	}

	//Number of entries in the program header table
	char nbEntriesSection[2];
	for(int i=0; i<2; i++)
	{
		nbEntriesSection[i]=fgetc(file);
	}
	int nbEntriesSec=creerNombre(nbEntriesSection, 2, endianness);
	if(TEST==1)
	{
		printf("Nombre d'entrée dans la section header table (2 char): 0x%02x\n", nbEntriesSec);

	}

	//Index of the section header table entry that contains the names of the sections
	char indexNamesSection[2];
	for(int i=0; i<2; i++)
	{
		indexNamesSection[i]=fgetc(file);
	}
	int indexNamesSec=creerNombre(indexNamesSection, 2, endianness);
	if(TEST==1)
	{
		printf("Index de la section dans la section header table donnant les noms des sections: %d\n", indexNamesSec);

	}


	if(TEST==1)
	{
		printf("--------------------------------------------\n\n");
	}

	Header header=fillHeader( first, l1, l2, l3, bitFormat, endianness, elfVersion, osId, osId2, fType, targetInst, execInitAddress, programInitAddress, sectionInitAddress, sizeHead, sizeProgEntry, nbEntriesProg, sizeSecEntry, nbEntriesSec, indexNamesSec);







	return header;


}
