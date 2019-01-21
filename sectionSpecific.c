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




void bssLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i)
{
  printf("Empty section until it is loaded in memory, nothing to show.\n");
}


void dataLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i)
{
  printf("Section containing the values of initialized variables. It cannot be read directly, it provides values for other sections'variables.\n");
}


void interpLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{
  printf("Section containing the address of the interpreter.\n");
	long offset=creerLongNombre(sectionHeaders[i].sh_offset.tab, 8, header.endianness);
	long length=creerLongNombre(sectionHeaders[i].sh_size.tab, 8, header.endianness);
	//printf("%lx %lx\n", offset, length);
	fseek(file, offset, SEEK_SET);
  char car;
  for(long i=0; i<length; i++)
  {
    car=fgetc(file);
    printf("%c", car);
  }
}

void rodataLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{
	printf("Section containing constant variables, can be accessed from other sections only to read them (only value present).\n");
}


void textLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{
	printf("Section containing the code instructions, use disassemble to read it.\n");
	//TODO
}


void commentLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{
	printf("Section containing global information of the ELF file.\n");

	long offset=creerLongNombre(sectionHeaders[i].sh_offset.tab, 8, header.endianness);
	long length=creerLongNombre(sectionHeaders[i].sh_size.tab, 8, header.endianness);
	//printf("%lx %lx\n", offset, length);
	fseek(file, offset, SEEK_SET);
  char car;
  for(long i=0; i<length; i++)
  {
    car=fgetc(file);
    printf("%c", car);
  }
}


void dynamicLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{
	int test=1;
	long offset=creerLongNombre(sectionHeaders[i].sh_offset.tab, 8, header.endianness);
	//printf("%lx %lx\n", offset, length);
	fseek(file, offset, SEEK_SET);
	//on lit la table entière
	printf("Table de structure\n");
	long size=creerLongNombre(sectionHeaders[i].sh_size.tab, 8, header.endianness);
	long entsize=creerLongNombre(sectionHeaders[i].sh_entsize.tab, 8, header.endianness);
	long nbEntries=size/entsize;
	if(test)
	{
		printf("Taille de la section: 0x%08lx\n", size);
		printf("Taille d'une entree': 0x%08lx\n", entsize);
		printf("Nombre d'entrees: %ld\n", nbEntries);
	}
	Elf64_Dyn entries[nbEntries];
	char d_tag[8];
	char d_ptn[8];
	for(int i=0; i<nbEntries; i++)
	{
		//on lit iune entrée
		for(int j=0; j<8; j++)
		{
			d_tag[j]=fgetc(file);
			entries[i].d_tag.tab[j]=d_tag[j];
		}
		for(int j=0; j<8; j++)
		{
			d_ptn[j]=fgetc(file);
			entries[i].d_ptn.tab[j]=d_ptn[j];
		}
	}

	//Puis on l'affiche TODO: this is raw data
	for(int i=0; i<nbEntries; i++)
	{
		printf("Entree %d: ", i);
		printf("tag: ");
		for (int j=0; j<8; j++)
		{
			printf("%d ", entries[i].d_tag.tab[j]);
		}
		printf("   ptn: ");
		for (int j=0; j<8; j++)
		{
			printf("%d ", entries[i].d_ptn.tab[j]);
		}
		printf("\n");
	}

}


void dynstrLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header)
{

}








void readRawPart(FILE * file, long offset, long length)
{
  fseek(file, offset, SEEK_SET);
  char car;
  for(long i=0; i<length; i++)
  {
    car=fgetc(file);
    printf("0x%x ", car);
  }
}



void readRawPartString(FILE * file,long offset, long length)
{
	fseek(file, offset, SEEK_SET);
  char car;
  for(long i=0; i<length; i++)
  {
    car=fgetc(file);
    printf("%c ", car);
  }
}




void readRawSection(int index, FILE * file, Elf64_Shdr * sectionHeaders, Header header)
{
	printf("Lecture hexadécimal (1 char à la fois) de la section numero %d:\n", index);
	long offset=creerLongNombre(sectionHeaders[index].sh_offset.tab, 8, header.endianness);
	long length=creerLongNombre(sectionHeaders[index].sh_size.tab, 8, header.endianness);
	//printf("0x%08lx 0x%08lx\n", offset, length);
	readRawPart(file, offset, length);

	printf("\n");
	printf("Lecture (1 char à la fois) de la section numero %d:\n", index);
	readRawPartString(file, offset, length);
}










void lectureDetailSectionEntree(Header header, Elf64_Shdr * sectionHeaders, FILE * file, char ** argsLine, int nbArgs)
{
	//On identifie le deuxième arguemnt
	char rawOption[]="-raw";
	char contentOption[]="-content";
	char leftSpaceOption[]="-leftSpace";
	char detailsHeaderOption[]="-detailsHeader";
	//On identifie la section recherchée
	if(strcmp(rawOption, argsLine[1])==0)
	{
		int index=trouverIndexSectionNom(file, argsLine[1], sectionHeaders, header.nbEntriesSectionHeader);
		if(index>=0)
		{
			readRawSection(index,  file, sectionHeaders, header);
		}
		else
		{
			printf("Nom de section inexistant\n");
		}
	}
	else if(strcmp(contentOption, argsLine[1])==0)
	{
		lectureDetailSection(header, sectionHeaders, file, argsLine, nbArgs);
	}
	else if(strcmp(leftSpaceOption, argsLine[1])==0)
	{
		printf("c");
		//TODO
	}
	else if(strcmp(detailsHeaderOption, argsLine[1])==0)
	{
		printf("d");
		//TODO
	}
	else
	{
		commandUnknown();
	}
}











void lectureDetailSection(Header header, Elf64_Shdr * sectionHeaders, FILE * file, char ** argsLine, int nbArgs)
{
	char bss[]=".bss";
	char data[]=".data";
	char interp[]=".interp";
	char rodata[]=".rodata";
	char text[]=".text";
	char comment[]=".comment";
	char dynamic[]=".dynamic";
	char dynstr[]=".dynstr";
	char dynsym[]=".dynsym";
	char got[]=".got";
	char hash[]=".hash";
	char note[]=".note";
	char plt[]=".plt";
	char shstrtab[]=".shstrtab";
	char symtab[]=".symtab";

	//Ceux qui ne constituent que des préfiwes au nom
	char rel[]=".rel";
	char rela[]=".rela";
	//On identifie la section dont il s'agit, et on adapte des comprtements spécifiques

	int test=1;
	//TODO
	char * nomSection=argsLine[2];
	int index=trouverIndexSectionNom(file, argsLine[2], sectionHeaders, header.nbEntriesSectionHeader);
	if(strcmp(bss, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .bss\n");
		}
		bssLecture(file, sectionHeaders, index);
	}
	else if(strcmp(data, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .data\n");
		}
		dataLecture(file, sectionHeaders, index);
	}
	else if(strcmp(interp, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .interp\n");
		}
		interpLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(rodata, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .rodata\n");
		}
		rodataLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(text, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .text\n");

		}
		textLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(comment, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .comment\n");
		}
		commentLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(dynamic, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .dynamic\n");
		}
		dynamicLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(dynstr, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .dynstr\n");
		}
		dynstrLecture(file, sectionHeaders, index, header);
	}
	else if(strcmp(dynsym, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .dynsym\n");
		}
	}
	else if(strcmp(got, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .got\n");
		}
	}
	else if(strcmp(hash, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .hash\n");
		}
	}
	else if(strcmp(note, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .note\n");
		}
	}
	else if(strcmp(plt, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .plt\n");
		}
	}
	else if(strcmp(shstrtab, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .shstrtab\n");
		}
	}
	else if(strcmp(symtab, argsLine[2])==0)
	{
		if(test==1)
		{
			printf("Lecture de la section .symtab\n");
		}
	}
	else if(isPrefix(argsLine[2], rela)==1)
	{
		if(test==1)
		{
			printf("Lecture de la section ayant pour préfixe .rela, son nom complet étant %s\n", argsLine[2]);
		}
	}
	else if(isPrefix(argsLine[2], rel)==1)
	{
		if(test==1)
		{
			printf("Lecture de la section ayant pour préfixe .rel, son nom complet étant %s\n", argsLine[2]);
		}
	}
	else
	{
		if(test==1)
		{
			printf("Nom de section non reconnu\n");
		}
	}

	printf("\n");
}
