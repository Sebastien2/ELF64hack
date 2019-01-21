#include <stdio.h>

#ifndef STRUCTURE
	#define STRUCTURE "Structure.h"
	#include STRUCTURE
#endif


char * getNameSection(char * nom, FILE * file, Elf64_Shdr * sectionHeaders, int i);
void getOneSectionHeader(FILE * file, Elf64_Shdr * sectionHeaders, int k);
void readSections(FILE * file, int nbSections, Elf64_Shdr * sectionHeaders);
int trouverIndexSectionNom(FILE * file, char * sectionName, Elf64_Shdr * sectionHeaders, int nbSections);
int equalStrings(char * ref, char * str);
