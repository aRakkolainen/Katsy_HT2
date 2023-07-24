#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int checkWord(char *searchWord, char *tempLine) {
    // How to split the line in C with strtok: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    // Searching for substring with strstr: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/search-within-a-string and linux manual
    // Comparing two strings: https://www.programiz.com/c-programming/library-function/string.h/strcmp 
    char *token; 
    token = strtok(tempLine, " ");
        while (token != NULL ){
            if ((strcmp(token, searchWord) == 0) || (strstr(token, searchWord) != NULL)) {
                return(1); // 1=true
            }
            token = strtok(NULL, " ");
    }
    return(0); // 0 = false
} 
void readFileAndSearchWord(char *fileName, char *searchWord) {
    FILE *file; 
    char *line=NULL;
    size_t len;
    int r=0; 
    int result;
    char *tempLine=NULL;

    if ((file = fopen(fileName, "r")) == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            } else {
                do {
                    r = getline(&line, &len, file);
                    /*Using realloc is based on this https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
                    and allocation memory for char * is based on this: https://stackoverflow.com/questions/2971709/allocating-memory-to-char-c-language*/
                    if ((tempLine = realloc(tempLine, (strlen(line)+1))) == NULL) {
                        fprintf(stderr, "malloc failed");
                        exit(1);
                    }
                    if (r != -1) {
                        strcpy(tempLine, line);
                        result = checkWord(searchWord, tempLine);
                        if (result == 1) {
                            printf("%s", line);
                        } 
                        }
                } while (r > 1);
                free(line); 
                free(tempLine);  
            fclose(file);
    }
}

int main(int argc, char * argv[]) {
    char *line=NULL;
    size_t len; 
    int r=0; 
    FILE *tempFile; 
    if (strcmp(argv[1], "") == 0) {
            printf("Empty word doesn't match any lines.\n"); 
            exit(1);
        }
    if (argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    } 
    else if (argc == 2) {

        printf("Searching the word from stdin\n"); 
        if ((tempFile = fopen("temp.txt", "w")) == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            }
        else {
            do {
            r = getline(&line, &len, stdin); 
            if (r == -1) {
                break; 
            } 
            fprintf(tempFile, "%s", line); 
            
        } while (r > 1);
        free(line);
        fclose(tempFile);
        readFileAndSearchWord("temp.txt", argv[1]);
        unlink("temp.txt");
        }
        

    
    } else if (argc > 2) {
        printf("Searching the word from file..\n");
        for (int i=2; i < argc; i++) {
            readFileAndSearchWord(argv[i], argv[1]);    
        }
        }
    return(0);
}
