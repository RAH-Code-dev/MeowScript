#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpretMeowScript(const char* program) {
    int asciiValue = 0;
    const char* meow = "meow";
    const char* hiss = "hiss";
    const char* purr = "purr";

    while (*program != '\0') {
        if (strstr(program, meow) == program) {
            asciiValue++;
            program += 4;
        } else if (strstr(program, hiss) == program) {
            asciiValue--;
            program += 4;
        } else if (strstr(program, purr) == program) {
            putchar(asciiValue);
            program += 4;
        } else {
            program++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.meow>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *meowScriptProgram = (char *)malloc(size + 1);
    if (meowScriptProgram == NULL) {
        perror("Error allocating memory for the program");
        fclose(file);
        return 1;
    }

    fread(meowScriptProgram, 1, size, file);
    fclose(file);

    meowScriptProgram[size] = '\0';

    interpretMeowScript(meowScriptProgram);
    printf("\n");

    free(meowScriptProgram);

    return 0;
}
