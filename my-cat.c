//my-cat.c Source code for command my-cat
// Sources for this code: 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc >= 2) {
        for (int i=1; i < argc; i++) {
            FILE *file; 
            char line[50];
            if ((file = fopen(argv[i], "r")) == NULL) {
                perror("my-cat: cannot open file");
                printf("\n");
                exit(1);
            } else {
                while (fgets(line, 50, file) != NULL) {
                    printf("%s", line);
                }
                printf("\n");
                fclose(file);
            }
        }
    } 
    return(0);
}