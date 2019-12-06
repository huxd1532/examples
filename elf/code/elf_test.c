#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>
#include "elf_handle.h"

#define SECTION_NAME ".mysec"
#define SECTION_CONTENT "abcdefghijklmnopqrstuvwxyz"



typedef struct{
    Elf64_Ehdr e_hdr;
}ELF_CTRL_T;

ELF_CTRL_T g_elf_ctrl;


//static char *get_elf_string_table_section(const int fd, const Elf64_Ehdr *e_hdr)
static char *get_shstr_section(const int fd, const Elf64_Ehdr *e_hdr)
{
    Elf64_Shdr s_hdr;
    char *str_table;
    if ((fd < 0) || (NULL == e_hdr) || (NULL == str_table))
        return NULL;

    lseek(fd, e_hdr->e_shoff + sizeof(Elf64_Shdr) * e_hdr->e_shstrndx, SEEK_SET);
    if(read(fd, &s_hdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)){
        printf("Read ELF section string table error");
        return NULL;
    }

    if((str_table = (char *) malloc(s_hdr.sh_size)) == NULL){
        printf("Malloc space for section string table failed");
        return NULL;
    }
    lseek(fd, s_hdr.sh_offset, SEEK_SET);
    if(read(fd, str_table, s_hdr.sh_size) != s_hdr.sh_size){
        printf("Read string table failed");
        free(str_table);
        return NULL;
    }

    return str_table;
}


static int program_dump(const char *filename)
{
    Elf64_Ehdr e_hdr;
    Elf64_Phdr p_hdr;
    int ph_offset;
    char ph_type[50];
    int  fd;
    fd = open(filename, O_RDONLY);
    if(fd < 0){
        printf("open %s failed\n", filename);
	    return -1;
    }

    if (get_elf_header(fd, &e_hdr))
    {
        close(fd);
        return -1;
    }

    ph_offset = e_hdr.e_phoff;
    printf("---------------program dump start-----------------\n");
    for (int i  = 0; i < e_hdr.e_phnum; i++) {
        lseek(fd, ph_offset, SEEK_SET);
        if(read(fd, &p_hdr, sizeof(Elf64_Phdr)) != sizeof(Elf64_Phdr)){
            printf("Read program header failed\n");
            return -1;
        }
        switch (p_hdr.p_type)
        {
            case PT_LOAD:
                /*
                 * We know that text segment starts at offset 0. And only one other possible loadable segment exists which is the data segment.
                 */
                if (p_hdr.p_offset == 0)
                {
                    strcpy(ph_type, "Text segment");
                }
                else
                {
                    strcpy(ph_type, "Data segment");
                }
                break;
            case PT_INTERP:
                strcpy(ph_type, "Interpreter");
                break;
            case PT_NOTE:
                strcpy(ph_type, "Note segment");
                break;
            case PT_DYNAMIC:
                strcpy(ph_type, "Dynamic segment");
                break;
            case PT_PHDR:
                strcpy(ph_type, "Phdr segment");
                break;
           default:
                strcpy(ph_type, "invaild segment");
                break;
        }
        printf("index=%2d\tph_offset=%2d\toffset=%2d\tsize=%3d\ttype=%s\n", i, ph_offset, p_hdr.p_offset, p_hdr.p_filesz, ph_type);
        ph_offset +=sizeof(Elf64_Phdr);
        
    }
    close(fd);
    printf("---------------program dump end-----------------\n");
}


static int section_dump(const char *filename)
{
    Elf64_Ehdr e_hdr;
    Elf64_Shdr s_hdr;
    char *str_table = NULL;
    int offset;
    int fd;

    //fd = open(filename, O_RDONLY);
    fd = open(filename, O_RDWR);
    if(fd < 0){
        printf("open %s failed\n", filename);
	    return -1;
    }

    if (get_elf_header(fd, &e_hdr))
    {
        return -1;
    }
    str_table = get_shstr_section(fd, (const Elf64_Ehdr*)&e_hdr);

    lseek(fd, e_hdr.e_shoff, SEEK_SET);
    offset = e_hdr.e_shoff;
    printf("---------------section dump start-----------------\n"); 
    for(int i = 0; i < e_hdr.e_shnum; i++){
        if(read(fd, &s_hdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)){
            printf("Read section header failed");
            return -1;
        }
        printf("index=%2d\tchar_off=%2d\tfile_off=%2d\tsec_off=%2d\tsec_size=%2d\talign=%2d\tname=%s\n", i, s_hdr.sh_name, offset, s_hdr.sh_offset, s_hdr.sh_size, s_hdr.sh_addralign, str_table + s_hdr.sh_name);
        offset += sizeof(Elf64_Shdr);  
    }
    printf("---------------section dump end-----------------\n");
    return 0;
}

static int elf_file_dump(const char *filename)
{
    Elf64_Ehdr *e_hdr;
    Elf64_Phdr *p_hdr;
    Elf64_Shdr *s_hdr;
    char *mem;
    int fd;
    struct stat st;
    char *StringTable;

    if ((fd = open(filename, O_RDONLY)) < 0)
    {
        return -1;
    }
 
    if (fstat(fd, &st) < 0)
    {
        close(fd);
        return -1;
    }
 
    /* Map the executable into memory */
     mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED)
    {
        perror("mmap");
        exit(-1);
    }
    e_hdr = (Elf64_Ehdr *)mem;

    p_hdr = (Elf64_Phdr *)&mem[e_hdr->e_phoff];
    s_hdr = (Elf64_Shdr *)&mem[e_hdr->e_shoff]; 
 
    StringTable = &mem[s_hdr[e_hdr->e_shstrndx].sh_offset];
}

void usage(void)
{
	char *message="comand [-operation] file\noperation:\n\t-a: add a new section\n\t-p:pop a section\n\t-d:dump files\n";
	printf("%s", message);
}

int main(int argc, char **argv)
{
	section_t section;
	int len;
	 if(argc < 3)
	 {
		usage();
        	return -1;
	 }
	if (elf_check(argv[2]))
	{
		printf("Elf mode don't match with system\n");
		return -1;
	}
	 if(!strcmp("-a", argv[1]))
	 {
	 	printf("Add a new section\n");
	memset(&section, 0, sizeof(section_t));
	len = strlen(SECTION_NAME); 
	section.name = malloc(len + 1);
	if (NULL == section.name)
	{
		printf("malloc for setion name failed!\n");
		return -1;
		
	}
	strncpy(section.name, SECTION_NAME, len);

	len = strlen(SECTION_CONTENT);
	section.len = len + 1;
	section.buff = malloc(len + 1);
	strncpy(section.buff, SECTION_CONTENT, len);

	if(add_section(argv[2], &section))
		printf("Add section failed\n");

		
	 }else if(!strcmp("-p", argv[1])){
	 	printf("Pop a  section\n");
		memset(&section, 0, sizeof(section_t));
		len = strlen(SECTION_NAME); 
    		section.name = malloc(len + 1);
		if (NULL == section.name)
		{
			printf("malloc for setion name failed!\n");
			return -1;
   		}
		strncpy(section.name, SECTION_NAME, len);
	 	if(pop_last_section(argv[2], &section)){
			printf("Pop error\n");
		}else{
			printf("len=%d\n", section.len);
			printf("content=%s\n", section.buff);
		}
			
	 }else if(!strcmp("-d", argv[1])){
	 	printf("Dump file\n");
		program_dump(argv[2]);
		section_dump(argv[2]);
	 }
	 else{
	 	printf("Error:bad params\n");
		usage();
	 }

}


#if 0

int main(int argc, char **argv)
{
    int len, ret=0;
    section_t new_section; 
    if(argc<2)
    {
        printf("Input parameters is to few!\n");
        return -1;
    }

    if (elf_check(argv[1]))
    {
        printf("Elf mode don't match with system\n");
        return -1;
    }
    memset(&new_section, 0, sizeof(section_t));
    len = strlen(SECTION_NAME); 
    new_section.name = malloc(len + 1);
    if (NULL == new_section.name)
    {
        printf("malloc for setion name failed!\n");
	    ret = -1;
	    goto _out;
    }
    strncpy(new_section.name, SECTION_NAME, len);
    #if 0
    len = strlen(SECTION_CONTENT);
    new_section.len = len + 1;
    new_section.buff = malloc(len + 1);
    strncpy(new_section.buff, SECTION_CONTENT, len);

   add_section(argv[1], &new_section);
    #endif

    program_dump(argv[1]);
    elf_file_dump(argv[1]);
    section_dump(argv[1]);

    
    pop_last_section(argv[1], &new_section);

    _out:
    	if (new_section.name)
            free(new_section.name);
        if (new_section.buff)
            free(new_section.buff);
	   return ret;

}
#endif
