

//---------------------Structures

typedef struct
{

	char magicalNumber; //1 char
	char ELFId[3];  //3 char
	char bitFormat;  //1 char
	char endianness;  //1 char
	char elfVersion;  //1 char
	char OsId1;  //1 char
	char OsId2;  //1 char
	int fileType;  //2 char
	int targetInstructionSet;  //2 char
	long startExecutionAddress;  //4 char pour 32-bit, 8 char pour 64-bit
	long startProgramHeaderAddress;  //4 char pour 32-bit, 8 char pour 64-bit
	long startSectionHeaderAddress;  //4 char pour 32-bit, 8 char pour 64-bit
	int sizeHeader;  //2 char
	int sizeEntryProgramHeader;  //2 char
	int nbEntriesProgramHeader;  //2 char
	int sizeEntrySectionHeader;  //2 char
	int nbEntriesSectionHeader;  //2 char
	int indexNamesSections;  //2 char
}Header;



//Types de base utilisés dans le format Elf64
typedef struct
{
	char tab[8];
}Elf64_Addr;

typedef struct
{
	char tab[8];
}Elf64_Off;

typedef struct
{
	char tab[2];
}Elf64_Half;

typedef struct
{
	char tab[4];
}Elf64_Word;

typedef struct
{
	char tab[4];
}Elf64_SWord;

typedef struct
{
	char tab[8];
}Elf64_XWord;

typedef struct
{
	char tab[8];
}Elf64_sXWord;



//Format d'un section header dans Elf64
typedef struct
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
}Elf64_Shdr;


//Pour la dynamic table
typedef struct
{
	Elf64_sXWord d_tag;
	Elf64_Addr d_ptn;
}Elf64_Dyn;


//Pour la symbol table
typedef struct
{
	Elf64_Word st_name;
	char st_info;
	char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_XWord st_size;
}Elf64_Sym;




//Pour les 2 types de relocation
typedef struct
{
	Elf64_Addr r_offset;
	Elf64_XWord r_info;
}Elf64_Rel;


typedef struct
{
	Elf64_Addr r_offset;
	Elf64_XWord r_info;
	Elf64_sXWord r_addend;
}Elf64_Rela;




//---------------Variables globales



Header header;





//----------------Signatures de fonctions





void afficherLigne(char * intitule, char * var, int size);

void afficherRawSectionHeader(Elf64_Shdr * sectionHeaders, int i);

void afficherSectionHeader(FILE * file, Elf64_Shdr * sectionHeaders, int i);

void afficherHeader(Header header);

Header fillHeader(char first, char l1, char l2, char l3, char bitFormat, char endianness, char elfVersion, char osId, char osId2, int fType, int targetInstr, long execInitAddress, long programInitAddress, long sectionInitAddress, int sizeHead, int sizeProgEntry, int nbEntriesProg, int sizeSecEntry, int nbEntriesSec, int indexNamesSec);
