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

static Elf64_Off world_align_calc(Elf64_Off offset);
static int file_copy(const char *src_file, int src_pos, const char *des_file, int des_pos, int size);

SYSTEM_MODE_T get_system_mode(void)
{
    union w
    {
        int a;
        char b;
    }c;
    c.a = 1;
    return (c.b == 1)?LSB_MODE:BSB_MODE;
}

 int elf_check(const char *filename)
{
    int fd;
    char e_ident[EI_NIDENT];

    fd = open(filename, O_RDONLY);
    if(fd < 0){
        printf("open %s failed\n", filename);
	    return -1;
    }

    if (fd < 0)
        return -1;
    lseek(fd, 0, SEEK_SET);
    if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT){
        printf("Read elf indent info failed!\n");
        close(fd);
        return -1;
    }

    if (e_ident[EI_CLASS] != ELFCLASS64)
    {
        printf("Do not handle types other than el64!\n");
        close(fd);
        return -1;
    }
    if (e_ident[EI_DATA] != get_system_mode())
    {
        printf("Elf CPU mode and system mode do not match!\n");
        close(fd);
        return -1;
    }
    return 0;
}

 int get_elf_header(const int fd, Elf64_Ehdr *e_hdr)
{
    if ((fd < 0) || (NULL == e_hdr))
        return -1;

    lseek(fd, 0, SEEK_SET);
    if(read(fd, e_hdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)){
        printf("Read ELF header error");
        return -1;
    }
    return 0;
}


static int file_copy(const char *src_file, int src_pos, const char *des_file, int des_pos, int size)
{
    int fd1, fd2;
    char *buff;
    fd1 = open(src_file, O_RDONLY);
    if(fd1 < 0){
        printf("open %s failed\n", src_file);
	    goto _error;
    }

    fd2 = open(des_file, O_RDWR);
    if(fd2 < 0){
        printf("open %s failed\n", des_file);
	    goto _error;
    }

    if((buff = malloc(size)) == NULL){
        goto _error;
    }

    lseek(fd1, src_pos, SEEK_SET);
    if((read(fd1, buff, size)) != size)
    {
        printf("Read from source file %s failed\n", src_file);
        goto _error;
    }
    
    lseek(fd2, des_pos, SEEK_SET);
    if((write(fd2, buff, size)) != size)
    {
        printf("Write to destination file %s failed\n", src_file);
        goto _error;
    }
    close(fd1);
    close(fd2);
    free(buff);
    _error:
        return -1;

    return 0;
    
    
}


int pop_last_section(const char *filename, section_t *section)
{
    Elf64_Ehdr e_hdr, *p_ehdr;
    Elf64_Shdr s_hdr, *p_shdr, *p_shstr_hdr;
    Elf64_Xword shstr_table_size;
    char *shstr_table, *mem;
    int fd, fd1, i;
    Elf64_Off offset, last_offset, section_shd_offset, section_offset;
    struct stat st;

    fd = open(filename, O_RDONLY);
    if(fd < 0){
        printf("open %s failed\n", filename);
	    goto _error;
    }

    if(!access(TEMPFILE, F_OK)){
        printf("remove file!\n");
        remove(TEMPFILE);
    }

    if (fstat(fd, &st) < 0)
    {
        printf("Get %s file stat failed", filename);
        goto _error;
    }
    fd1 = creat(TEMPFILE, st.st_mode);
    if(fd1 < 0){
		printf("Create %s failed\n", TEMPFILE);
		 goto _error; 
    }
    close(fd1);
    if((NULL == section->name) || !strlen(section->name))
    {
        goto _error;
        
    }

    if (get_elf_header(fd, &e_hdr))
    {
        goto _error;
    }

    //1、根据section name 去找有没有这个section,有就继续，否则返回。
    lseek(fd, e_hdr.e_shoff + sizeof(Elf64_Shdr) * e_hdr.e_shstrndx, SEEK_SET);
    if(read(fd, &s_hdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)){
        printf("Read ELF section string table failed");
        goto _error;
    }
    shstr_table_size = s_hdr.sh_size;
    if((shstr_table = (char *) malloc(shstr_table_size)) == NULL){
        printf("Malloc memory for section string table failed");
        goto _error;
    }    

    lseek(fd, s_hdr.sh_offset, SEEK_SET);
    if(read(fd, shstr_table, shstr_table_size) != shstr_table_size){
        printf("Read string table failed");
        goto _error;
    }
    last_offset = s_hdr.sh_offset; 

    //目标section必须是最后一个section
    offset = e_hdr.e_shoff + sizeof(Elf64_Shdr)*(e_hdr.e_shnum - 1);
    lseek(fd, offset, SEEK_SET);
    if(read(fd, &s_hdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)){
        printf("Find section .text procedure failed");
        goto _error;
    }

    if(!strcmp(shstr_table + s_hdr.sh_name, section->name) == 0){
        printf("Section name %s not match with %s\n", shstr_table + s_hdr.sh_name, section->name);
        goto _error;
    }
    //section name 也必须是shstrab里面的最后一个字符串
    if(shstr_table_size != (s_hdr.sh_name + strlen(shstr_table + s_hdr.sh_name) + 1)){
        printf("Section name is not stored at the end of the shstrab");
        goto _error;
    }
    last_offset += s_hdr.sh_name;
    shstr_table_size = s_hdr.sh_name;

    //2、取出section内容
    if((section->buff = (char *)malloc(s_hdr.sh_size)) == NULL)
    {
        printf("Malloc memory for section failed\n");
        goto _error;
    }
    lseek(fd, s_hdr.sh_offset, SEEK_SET);
    if(read(fd, section->buff, s_hdr.sh_size) != s_hdr.sh_size){
        printf("Read secrion failed!\n");
        goto _error;
    }
    section->len = s_hdr.sh_size;
    close(fd);
    //3、拷贝section name之前的内容到临时文件
    file_copy(filename, 0, TEMPFILE, 0, last_offset);

    //4、拷贝section header table到目标文件
    last_offset = world_align_calc(last_offset);
    file_copy(filename, e_hdr.e_shoff, TEMPFILE, last_offset, e_hdr.e_shentsize*(e_hdr.e_shnum - 1));

    //5、调整相关表头内容
    fd = open(TEMPFILE, O_RDWR);
    if(fd < 0){
        printf("reopen %s failed\n", TEMPFILE);
        goto _error;
    }

    if (fstat(fd, &st) < 0)
    {
        printf("fstat failed");
        goto _error;
    }
    mem = mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED)
    {
        printf("mmap failed!\n");
        goto _error;
    }
    p_ehdr = (Elf64_Ehdr *)mem;
    p_ehdr->e_shnum -= 1;
    p_ehdr->e_shoff = last_offset;

    p_shdr = (Elf64_Shdr *)&mem[p_ehdr->e_shoff];

    p_shstr_hdr = &p_shdr[p_ehdr->e_shstrndx];
    p_shstr_hdr->sh_size = shstr_table_size;

    munmap(mem, st.st_size);
    close(fd);
    if(rename(TEMPFILE, filename)){
	printf("Rename file failed\n");
	goto _error;
    }
    _error:
        if(section->buff){
            free(section->buff);
            section->buff = NULL;
        }
        return  -1;
}


static Elf64_Off world_align_calc(Elf64_Off offset)
{
    int align=sizeof(int);
    return (offset%align)?((offset/align + 1)*align):(offset);
}

int add_section(const char *filename, section_t *new_section)
{
    Elf64_Ehdr e_hdr, *p_ehdr;
    Elf64_Shdr new_sction_hdr, *p_shdr, *p_shstr_hdr;
    Elf64_Xword sh_size, new_shstr_size;
    Elf64_Off n, offset, new_e_shoff;
    Elf64_Word last_shstr_name, new_shstr_name;
    char *buff, *shstr_table, *mem;
    struct stat st;
    int fd, ret = 0;

    fd = open(filename, O_RDWR);
    if(fd < 0){
        printf("open %s failed\n", filename);
	    return -1;
    }

    if (get_elf_header(fd, &e_hdr))
    {
        ret = -1;
        goto _out;
    }

    //1、将shstable之后的内容（即sectiob header table）读取出来，存放在buff中
    sh_size = e_hdr.e_shentsize*e_hdr.e_shnum;

    if((buff = malloc(sh_size)) == NULL){
        printf("Malloc menory for section header failed!\n");
        ret = -1;
        goto _out;
    }

    lseek(fd, e_hdr.e_shoff, SEEK_SET);
    if(read(fd, buff, sh_size) != sh_size){
        printf("Read section header table failed\n");
        ret = -1;
        goto _out;
    }
    //2、在shstable 节中添加新增节的名字
    /*find last sh_name*/
    last_shstr_name = 0;
    p_shdr = (Elf64_Shdr *)buff;
    for(int i = 0; i < e_hdr.e_shnum; i++){
        if(p_shdr->sh_name > last_shstr_name){
            last_shstr_name = p_shdr->sh_name;
        }
        if(i == e_hdr.e_shstrndx)
        {
            p_shstr_hdr = p_shdr;
        }
        p_shdr++;
    }

    if((shstr_table = (char *) malloc(p_shstr_hdr->sh_size)) == NULL){
        printf("Malloc space for section shstr table failed");
        ret = -1;
        goto _out;
    }

    lseek(fd, p_shstr_hdr->sh_offset, SEEK_SET);
    if(read(fd, shstr_table, p_shstr_hdr->sh_size) != p_shstr_hdr->sh_size){
        printf("Read string table failed");
        ret = -1;
        goto _out;
    }

    new_shstr_name = last_shstr_name + strlen(shstr_table + last_shstr_name) + 1;
    offset = p_shstr_hdr->sh_offset + new_shstr_name;
    lseek(fd, offset, SEEK_SET);
    n = strlen(new_section->name) + 1;
    if(n != write(fd, new_section->name, n)){
        printf("Write new section name failed!\n");
        ret = -1;
        goto _out;
    }
    memset(&new_sction_hdr, 0, sizeof(Elf64_Shdr));
    new_sction_hdr.sh_name = new_shstr_name;
    new_shstr_size = new_shstr_name + n;

    //3、在shstable 节后添加新增节内容
    offset += (n + 1);
    offset = world_align_calc(offset);
    lseek(fd, offset, SEEK_SET);
    n = new_section->len + 1;

    if(n != write(fd, new_section->buff, n)){
        printf("Write new section content failed!\n");
        ret = -1;
        goto _out;
    }
    new_sction_hdr.sh_offset = offset;
    new_sction_hdr.sh_size = n;
    //4、将buff内容写回到新增节内容之后
    offset += n;
    offset = world_align_calc(offset);
    lseek(fd, offset, SEEK_SET);
    n = sh_size;
    if(n != write(fd, buff, n)){
        printf("Write back section table failed!\n");
        ret = -1;
        goto _out;
    }
    new_e_shoff = offset;

    //5、把新section的头部添加大section table的末尾
    offset += n;
    lseek(fd, offset, SEEK_SET);
    n = sizeof(Elf64_Shdr);
    if(n != write(fd, &new_sction_hdr, n)){
        printf("Write new section header failed!\n");
        ret = -1;
        goto _out;
    }

    close(fd);/*Save previous changes*/

    //6、调整各表头的偏移
    fd = open(filename, O_RDWR);
    if(fd < 0){
        printf("reopen %s failed\n", filename);
	    ret = -1;
        goto _out;
    }

    if (fstat(fd, &st) < 0)
    {
        printf("fstat failed");
        ret = -1;
        goto _out;
    }
    mem = mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED)
    {
        printf("mmap failed!\n");
        return -1;
    }

    p_ehdr = (Elf64_Ehdr *)mem;
    p_ehdr->e_shnum += 1;
    p_ehdr->e_shoff = new_e_shoff;

    p_shdr = (Elf64_Shdr *)&mem[p_ehdr->e_shoff];
    p_shstr_hdr = &p_shdr[p_ehdr->e_shstrndx];
    p_shstr_hdr->sh_size = new_shstr_size;

    munmap(mem, st.st_size);

    _out:
        if(buff)
            free(buff);
        if(shstr_table)
            free(shstr_table);
        close(fd);
        return ret;
}


