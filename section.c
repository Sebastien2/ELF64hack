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


extern int maxLength;
extern int maxArgs;
extern Header header;




char * getNameSection(char * nom, FILE * file, Elf64_Shdr * sectionHeaders, int i)
{
	int test=0;
	//Lecture de la section des noms de section
	int index=header.indexNamesSections;
	Elf64_Shdr section=sectionHeaders[index];
	unsigned long offset=creerLongNombre(section.sh_offset.tab, 8, header.endianness);
	unsigned long offset2=creerLongNombre(sectionHeaders[i].sh_name.tab, 4, header.endianness);

	fseek(file, offset+offset2, SEEK_SET);

	fgets(nom, maxLength, file);

	if(test)
	{
		printf("index de section voulu: %d\n", i);
		printf("index de la section des noms: %d\n", index);
		printf("offset: 0x%08lx\n", offset);
		printf("offset2: 0x%04lx\n", offset2);
		printf("Nom de la section: %s\n", nom);
		printf("\n");
		for(int i=0; i<maxLength; i++)
		{
			printf("%d ", nom[i]);
		}
	}

	return nom;
}






void getOneSectionHeader(FILE * file, Elf64_Shdr * sectionHeaders, int k)
{
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_XWord sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_XWord sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_XWord sh_addralign;
	Elf64_XWord sh_entsize;


	for(int i=0; i<4; i++)
	{
		sh_name.tab[i]=fgetc(file);
	}

	for(int i=0; i<4; i++)
	{
		sh_type.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_flags.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_addr.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_offset.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_size.tab[i]=fgetc(file);
	}

	for(int i=0; i<4; i++)
	{
		sh_link.tab[i]=fgetc(file);
	}

	for(int i=0; i<4; i++)
	{
		sh_info.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_addralign.tab[i]=fgetc(file);
	}

	for(int i=0; i<8; i++)
	{
		sh_entsize.tab[i]=fgetc(file);
	}



	//Puis on construit l'objet
	Elf64_Shdr sec;
	sec.sh_name=sh_name;
	sec.sh_type=sh_type;
	sec.sh_flags=sh_flags;
	sec.sh_addr=sh_addr;
	sec.sh_offset=sh_offset;
	sec.sh_size=sh_size;
	sec.sh_link=sh_link;
	sec.sh_info=sh_info;
	sec.sh_addralign=sh_addralign;
	sec.sh_entsize=sh_entsize;

	sectionHeaders[k]=sec;
}




void readSections(FILE * file, int nbSections, Elf64_Shdr * sectionHeaders)
{
	//On le remplit avec la liste des sections
	long start=header.startSectionHeaderAddress;

	fseek(file, start, SEEK_SET);

	for(int k=0; k<nbSections; k++)
	{
		getOneSectionHeader(file, sectionHeaders, k);
	}

	/*
	for(int i=0; i<4; i++)
	{
		printf("%d ", sh_name.tab[i]);
	}
	printf("\n");
	*/

}






int trouverIndexSectionNom(FILE * file, char * sectionName, Elf64_Shdr * sectionHeaders, int nbSections)
{
	//printf("Nom de section en argment: %s\n", sectionName);
	int result=-1;
	char nom[maxLength];
	nom[0]=0;
	for(int i=0; i<nbSections; i++)
	{
		nom[0]=0;
		getNameSection(nom, file, sectionHeaders, i);

		if(equalStrings(nom, sectionName)==1 && nom[0]!=0)  //TODO: préciser le test par ressemblance suffisante
		{
			//printf(" egalite %d ", i);
			result=i;
		}
	}

	return result;
}





int equalStrings(char * ref, char * str)
{
	//printf("%s\n", ref);
	//printf("%s\n", str);
	int res=1;
	int i=0;
	char car=ref[i];
	while(car!=0 && car !=10 && res==1)
	{
		if(car!=str[i])
		{
			//printf("alpha %d\n", i);
			res=0;
		}
		if(str[i]==0)
		{
			//printf("beta %d\n", i);
			res=0;
		}
		i+=1;
		car=ref[i];
	}

	if(car!=str[i])
	{
		//printf("gamma %d\n", i);
		res=0;
	}

	return res;
}
