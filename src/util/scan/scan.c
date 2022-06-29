#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "conio.h"
#include "scan.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

void scanWithSuggestion(char *text, char *string, int numOptions, int stringSize, char options[numOptions][stringSize]) {
    printWithSuggestion(text, "\0", "\0");
    char ch;
    char emptyString[] = "\0";
    char *suggestion = options[0];
    int betterSuggestionScore = 0;
    int i = 0;
    string[0] = '\0';
    while (i < stringSize - 1) {
        ch = getch();
        if (ch == '\t') {
            strcpy(string, suggestion);
        }
        if (ch == '\r') {
            suggestion[0] = '\0';
            printWithSuggestion(text, suggestion, string);
            break;
        }
        if (ch == '\b' && i > 0) {
            i--;
            string[i] = '\0';
        }
        if (isalpha(ch)) {
            string[i] = ch;
            i++;
            string[i] = '\0';
        }
        betterSuggestionScore = 0;
        if (strlen(string) < 2)
            suggestion = emptyString;
        else
            for (int j = 0; j < (numOptions); j++) {
                char *suggestionTemp = options[j];
                int suggestionScore = smithWaterman(string, suggestionTemp);
                if (suggestionScore > betterSuggestionScore) {
                    suggestion = options[j];
                    betterSuggestionScore = suggestionScore;
                }
            }
        printWithSuggestion(text, suggestion, string);
    }
    printWithSuggestion(text, "\0", string);
    printf("\n");
}

void printWithSuggestion(char *text, char *suggestion, char *string) {
    int align = strlen(text);
    printf("\33[1B");
    printf("\33[2K\r");
    printf("\33[%dC\33[32m%s\33[0m", align, suggestion);
    //printf("%s\33[0m", suggestion);
    printf("\33[1A");
    printf("\33[2K\r");
    printf("%s", text);
    printf("%s", string);
}

int smithWaterman(char *s1, char *s2) {
    int m = strlen(s1);
    int n = strlen(s2);
    int **matrix = (int **) malloc(sizeof(int *) * (m + 1));
    for (int i = 0; i < m + 1; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * (n + 1));
    }
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            } else {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }
    int max = matrix[m][n];
    for (int i = 0; i < m + 1; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return max;
}

void scanString(char *string, int stringSize) {
    fflush(stdin);
    fgets(string, 100, stdin);
    string[strlen(string) - 1] = '\0';
}


void scanSelection(char *result, int countOptions, int stringLength, char options[countOptions][stringLength]){
    int option = 0;
    while(1){
        for(int i = 0; i < countOptions; i++){
            printf("\33[2K\r");
            if(i == option) printf("\33[30m\33[47m");
            printf("%s", options[i]);
            if(i == option) printf("\33[0m");
            printf("\33[1B");
        }
        printf("\33[%dA", countOptions);
        //printf("\33[8m");
        char ch = getch();
        if(ch == -32){
            ch = getch();
            if(ch == 72) option--;
            if(ch == 80) option++;
            if(option < 0) option = countOptions - 1;
            if(option == countOptions) option = 0;
            continue;
        }
        if(ch == '\r'){
            strcpy(result, options[option]);
            for(int i = 0; i < countOptions; i++){
                printf("\33[2K\r");
                printf("\33[1B");
            }
            printf("\33[%dA", countOptions);
            //printf("\33[0m");
            return;
        }
    }
}
