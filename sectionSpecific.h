#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCTURE
	#define STRUCTURE "Structure.h"
	#include STRUCTURE
#endif


//A chaque section on associe la fonction permettant de le lire

void bssLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i);

void dataLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i);

void interpLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header);

void rodataLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header);

void textLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header);

void commentLecture(FILE * file, Elf64_Shdr * sectionHeaders, int i, Header header);





void readRawPart(FILE * file, long offset, long length);

void readRawSection(int index, FILE * file, Elf64_Shdr * sectionHeaders, Header header);

void readRawPartString(FILE * file,long offset, long length);

void lectureDetailSectionEntree(Header header, Elf64_Shdr * sectionHeaders, FILE * file, char ** argsLine, int nbArgs);

void lectureDetailSection(Header header, Elf64_Shdr * sectionHeaders, FILE * file, char ** argsLine, int nbArgs);
