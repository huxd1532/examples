#ifndef __ELF_HANDLE_H__
#define __ELF_HANDLE_H__

//#define EI_NIDENT 16
#define EI_DATA   5	   /* D ata encoding */

#define EI_CLASS	      4	/* File class */

#define ELFCLASSNONE	  0	/* Invalid class */
#define ELFCLASS32	      1	/* 32-bit objects */
#define ELFCLASS64	      2	/* 64-bit objects */

#define TEMPFILE "temp"
static Elf64_Off world_align_calc(Elf64_Off offset);
typedef struct{
    char *name;
    int len;
    char *buff;
    //Elf64_Shdr s_hdr;
}section_t;



typedef enum{
    INVAILD_MODE,
    LSB_MODE,   /*Little endian mode*/
    BSB_MODE   /*Big endian mode*/
}SYSTEM_MODE_T;

int pop_last_section(const char *filename, section_t *section);
int add_section(const char *filename, section_t *new_section);
SYSTEM_MODE_T get_system_mode(void);
 int elf_check(const char *filename);
  int get_elf_header(const int fd, Elf64_Ehdr *e_hdr);

#endif
