#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

Elf32_Sym *symtab = NULL; 
char *strtab = NULL;
int sym_count = 0;

void read_symtab_and_strtab(int fd, Elf32_Ehdr *ehdr, Elf32_Shdr *section_headers, char *shstrtab) {
    
    // 遍历所有的节头，找到符号表和字符串表
    for (int i = 0; i < ehdr->e_shnum; i++) {
        Elf32_Shdr *shdr = &section_headers[i];//cur to current structure

        
        if (shdr->sh_type == SHT_SYMTAB) {
            symtab = malloc(shdr->sh_size);
            lseek(fd, shdr->sh_offset, SEEK_SET);
            if (read(fd, symtab, shdr->sh_size) != shdr->sh_size) {
                perror("Failed to read symtab");
                return;
            }
            printf("Read symtab from section %d: %s\n", i, &shstrtab[shdr->sh_name]);

            // //check the symtab
            // int sym_count = shdr->sh_size / sizeof(Elf32_Sym);
            // printf("Number of symbols: %d\n", sym_count);
            // for (int j = 0; j < sym_count; j++) {
            //     printf("  Symbol %d: name offset = %u\n", j, symtab[j].st_name);
            // }
        }

        if (shdr->sh_type == SHT_STRTAB) {
            //if(!strcmp(shdr->sh_name,".strtab")) break;//just the offset
            //if(!strcmp(&shstrtab[shdr->sh_name],".strtab")) break;
            strtab = malloc(shdr->sh_size);
            lseek(fd, shdr->sh_offset, SEEK_SET);
            if (read(fd, strtab, shdr->sh_size) != shdr->sh_size) {
                perror("Failed to read strtab");
                free(strtab);
                return;
            }
            printf("Read strtab from section %d: %s\n", i, &shstrtab[shdr->sh_name]);
            
            // //check the strtab
            // printf("String table content:\n");
            // int offset = 0;
            // while (offset < shdr->sh_size) {
            // printf("  Offset %d: %s\n", offset, &strtab[offset]);
            // offset += strlen(&strtab[offset]) + 1;  // 跳过当前字符串
            // }

            break;//ignore the shstrtab


        }
    }

}
// e /home/wizard/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-riscv32-nemu.elf 
void parse_elf_file(const char *file_path) {
    printf("Trying to open file: '%s'\n", file_path);
    int fd = open(file_path, O_RDONLY);
    //int fd = open("/home/wizard/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-riscv32-nemu.elf", O_RDONLY);

    if (fd < 0) {
        perror("Failed to open file");
        return ;
    }
    //check ELF header
    Elf32_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)) {
        perror("Failed to read ELF header");
        close(fd);
        return ;
    }

    // Check for ELF Magic
    if (ehdr.e_ident[0] != 0x7f || ehdr.e_ident[1] != 'E' ||
        ehdr.e_ident[2] != 'L' || ehdr.e_ident[3] != 'F') {
        fprintf(stderr, "This is not an ELF file.\n");
        close(fd);
        return ;
    }

    // Print some details about the ELF file
    printf("ELF Header:\n");
    printf("  Type: %u\n", ehdr.e_type);
    printf("  Machine: %u\n", ehdr.e_machine);
    printf("  Version: 0x%x\n", ehdr.e_version);
    printf("  Entry point address: 0x%x\n", ehdr.e_entry);
    printf("  Start of program headers: %u (bytes into file)\n", ehdr.e_phoff);
    printf("  Start of section headers: %u (bytes into file)\n", ehdr.e_shoff);
    printf("  Flags: 0x%x\n", ehdr.e_flags);
    printf("  Size of this header: %u (bytes)\n", ehdr.e_ehsize);
    printf("  Size of program headers: %u (bytes)\n", ehdr.e_phentsize);
    printf("  Number of program headers: %u\n", ehdr.e_phnum);
    printf("  Size of section headers: %u (bytes)\n", ehdr.e_shentsize);
    printf("  Number of section headers: %u\n", ehdr.e_shnum);
    printf("  Section header string table index: %u\n", ehdr.e_shstrndx);

    // Read Section Headers
    lseek(fd, ehdr.e_shoff, SEEK_SET);// off_t leek(int fd,off_t offset, int whence);
    /*
    SEEK_SET set the pointer to an offset relative to the head of file.
    SEEK_CUR set the pointer to an offset relative to the current pointer.
    SEEK_END     
    */
    Elf32_Shdr *section_headers = malloc(ehdr.e_shnum * sizeof(Elf32_Shdr));
    if (read(fd, section_headers, ehdr.e_shnum * sizeof(Elf32_Shdr)) != ehdr.e_shnum * sizeof(Elf32_Shdr)) {
        perror("Failed to read section headers");
        free(section_headers);
        close(fd);
        return;
    }

    // Get the section header string table index (shstrndx)
    Elf32_Shdr shstrtab_header = section_headers[ehdr.e_shstrndx];
    printf("Section header string table starts at offset 0x%x\n", shstrtab_header.sh_offset);

    // Read the section header string table
    char *shstrtab = malloc(shstrtab_header.sh_size);
    lseek(fd, shstrtab_header.sh_offset, SEEK_SET);
    if (read(fd, shstrtab, shstrtab_header.sh_size) != shstrtab_header.sh_size) {
        perror("Failed to read section header string table");
        free(shstrtab);
        free(section_headers);
        close(fd);
        return;
    }

    // Now let's print the section names
    printf("Section names from the section header string table:\n");
    for (int i = 0; i < ehdr.e_shnum; ++i) {
        printf("  Section %d: %s\n", i, &shstrtab[section_headers[i].sh_name]);
    }

    read_symtab_and_strtab(fd, &ehdr, section_headers, shstrtab);
    
    //print the name of symtab
    if (symtab && strtab) {
    printf("\nSymbols in the symtab:\n");
    Elf32_Shdr *symtab_shdr = NULL;
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (section_headers[i].sh_type == SHT_SYMTAB) {
            symtab_shdr = &section_headers[i];
            break;
        }
    }

    if (symtab_shdr != NULL) {
        sym_count = symtab_shdr->sh_size / sizeof(Elf32_Sym);
        printf("sym_count is %d\n", sym_count);
        for (int i = 0; i < sym_count; i++) {
            if (symtab[i].st_name != 0) {//filter out items with empty names
                printf("  Symbol %d: %s ", i, &strtab[symtab[i].st_name]);
                printf("value %x\n",symtab[i].st_value);
            }
        }
    }
    }
    // Cleanup
    free(shstrtab);
    //free(section_headers);

    close(fd);
}

char *find_function_by_pc(uint32_t pc) {
    
    if (!symtab || !strtab) {
        fprintf(stderr, "Symtab or Strtab not initialized.\n");
        return NULL;
    }
    //printf("begin!\n");
    //printf("sym_count = %d\n",sym_count);
    Elf32_Sym *sym = symtab;
    for (int i = 0; i < sym_count; i++) {
        //printf("the %d trying\n",i);
        // func?
        if (ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC) {
            // uint32_t start = sym[i].st_value;
            // uint32_t end = start + sym[i].st_size;
            if (pc == sym[i].st_value) {
                return &strtab[sym[i].st_name];
            }
        }
    }

    return NULL;
}

void test_find_function_by_pc(uint32_t pc) {
    char *func_name = find_function_by_pc(pc);
    if (func_name) {
        printf("PC 0x%x is function: %s\n", pc, func_name);
    } else {
        printf("PC 0x%x does not belong to any function.\n", pc);
    }
}