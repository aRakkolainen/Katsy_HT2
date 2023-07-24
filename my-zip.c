#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// countChar function is based on this website: https://javatutoring.com/c-program-to-count-occurrences-of-character-in-string/
int countChar(char, char *);
void readFile(char *);
void writeToStdout(char *, int); 


int countChar(char character, char *str) {
    int count = 0; 
    for (int i=0; str[i]; i++ ) {
        if (str[i] == character) {
            count++; 
        } 
    }
    return count; 

}
//This function reads the file to be compressed and then calls function where the content is compressed
void readFile(char *inputFileName) {
    FILE * file; 
    char *line=NULL;
    size_t len;
    int r;
            if ((file = fopen(inputFileName, "r")) == NULL) {
                fprintf(stderr, "my-zip: cannot open file\n");
                exit(1);
            } else {
                do {
                    r= getline(&line, &len, file); 
                    if (r != -1) {
                        writeToStdout(line, r);
                    }
                    }while(r > 1);
                    free(line);
                    fclose(file);
                }

}

// Here is written the output to the stdout when first the function has called other function countChar 
// for counting the number of each character in line. 
void writeToStdout(char *line, int r) { 
    int counter=0; 
    int total=0;
    char character = line[total];
    while (total < r) {
        total += counter; 
        character = line[total];
        if (character == '\0') {
            break; 
        }
        counter = countChar(character, line);
        //Writing the integer in binary form and writing char simultaneously: https://stackoverflow.com/questions/10810593/two-consecutive-fwrites-operation  
        //Info about using fwrite(): https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
        fwrite(&counter, sizeof(int), 1, stdout); 
        fwrite(&character, sizeof(char), 1, stdout);            
        }

}

int main(int argc, char * argv[]) { 
    char inputFileName[30];
    
    if (argc == 1) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    } else if (argc >= 2) {
        for (int i=1; i < argc; i++) {
            strcpy(inputFileName, argv[i]);
            readFile(inputFileName);
            } 
        } 
    return(0);  
}
