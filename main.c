#include <stdio.h>
#include <stdint.h>
#include <string.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);
int main (void){
    //opens the file
FILE *file = fopen("A2_tests.txt", "r");
if (file == NULL){
    printf("Error: Could not open file\n");
    return 1;
}

char line[256];
char func[32]; 
char expected_output[128];
char input1[128];
int counter = 0;
int pass = 0;
while (fgets(line, sizeof(line), file) != NULL){
    if (line[0] == '\n'){
        continue;
    }
    if (line[0] == '#'){
        continue;
    }
    line[strcspn (line , "\n")] = '\0';
    //Parse String with 3 matched items 
    if(sscanf(line, "%s %s %s", func, input1, expected_output) ==3){
        char result[200];
        counter++;
        //checks if any func matches
        if (strcmp(func, "oct_to_bin") == 0 ) oct_to_bin(input1, result);
        else if (strcmp(func, "oct_to_hex") == 0) oct_to_hex(input1, result);
        else if (strcmp(func, "hex_to_bin") == 0) hex_to_bin(input1, result);
        else if (strcmp(func, "to_sign_magnitude") == 0){
            int32_t n = atoi(input1);
            to_sign_magnitude(n,result);
        }
        else if (strcmp(func, "to_ones_complement") == 0){
            int32_t n = atoi(input1);
            to_ones_complement(n,result);
        }
        else if (strcmp(func, "to_twos_complement") == 0){
            int32_t n = atoi(input1);
            to_twos_complement(n,result);
        }
        //outputs results
        if (strcmp(result, expected_output) == 0){
            printf("Test %d: %s(%s) -> Expected: %s, Got: %s [PASS]\n", counter, func, input1, expected_output, result);
            pass++;
        } else printf("Test %d: %s(%s) -> Expected: %s, Got: %s [FAIL]\n", counter, func, input1, expected_output, result);


    }
    }
    printf("Summary: %d/%d test passed", pass, counter);
}