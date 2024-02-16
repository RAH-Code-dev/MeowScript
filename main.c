#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * The function interprets a MeowScript program by incrementing, decrementing, or outputting ASCII
 * values based on specific keywords.
 * 
 * @param program The `program` parameter is a pointer to a character array (string) that represents
 * the MeowScript program to be interpreted.
 */
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

int interactive() {
    char buffer[256];
    char *inputHistory = NULL;
    size_t totalSize = 0;

    printf("MeowScript's Interactive Mode :3 (Ctrl+D to exit):\n> ");

    while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t bufferSize = strlen(buffer);

        inputHistory = realloc(inputHistory, totalSize + bufferSize + 1);
        if(inputHistory == NULL) {
            perror("Error reallocating memory for input history");
            return 1;
        }

        strcpy(inputHistory + totalSize, buffer);
        totalSize += bufferSize;

        interpretMeowScript(inputHistory);
        printf("\n> ");
    }

    return 0;
}

/**
 * This C program reads a file containing a MeowScript program, interprets the program, and prints the
 * output.
 * 
 * @param argc The `argc` parameter is an integer that represents the number of command-line arguments
 * passed to the program. It stands for "argument count".
 * @param argv The `argv` parameter is an array of strings that represents the command-line arguments
 * passed to the program. In this case, `argv` is expected to have two elements:
 * 
 * @return The main function is returning an integer value. In this case, it is returning 0, indicating
 * successful execution of the program.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return interactive();
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
