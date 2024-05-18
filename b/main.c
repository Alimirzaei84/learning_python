// Write your code here :)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 90000
#define MAX_WORD_LENGTH 100

intin(){
    int i = 0;
    char **dic;
    dic = (char**)calloc(MAX_WORDS , sizeof(char*));
    for(int o = 0 ;o<MAX_WORDS ;o++){
        dic[o] = (char*)calloc(MAX_WORD_LENGTH ,sizeof(char));
    }
    FILE *file;
    file = fopen("dic.txt", "r+");
    if(file == NULL) {
        printf("error\n");
        return -1;
    }
   while ((fscanf(file,"%s", dic[i]) != EOF) && i <= MAX_WORDS){
	dic[i][strcspn(dic[i], "\n")] = '\0';
      i++;
   }
    fclose(file);
    char input[1000];
    fgets(input,sizeof(input), stdin);
	input[strcspn(input, "\n")] = '\0';
    char *token = strtok(input, " ");
    int found_misspelled_word = 0;
    while (token != NULL) {
        int is_misspelled = 1;
        for (int j = 0; j < i; j++) {
            if (!strcmp(token, dic[j])) {
                is_misspelled = 0;
                break;
            }
        }
        if (is_misspelled) {
            if (!found_misspelled_word) {
                printf("misspelled word(s):\n");
                found_misspelled_word = 1;
            }
            puts(token);
        }
        token = strtok(NULL, " ");
    }
    if (!found_misspelled_word) printf("there is no misspelled word!\n");
    return 0;
}
