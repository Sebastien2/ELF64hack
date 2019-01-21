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


void tooManyArguments()
{
  printf("La commande est inconnue (trop d'arguments): use help for more information\n");
}



void globalHelpCommand()
{
  //TODO
  printf("demande d'aide globale\n");
}
