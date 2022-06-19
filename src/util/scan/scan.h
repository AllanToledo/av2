//
// Created by allan on 19/06/2022.
//

#ifndef AV2_SCAN_H
#define AV2_SCAN_H
void printWithSuggestion(char *text, char *suggestion, char *string);

int smithWaterman(char *s1, char *s2);

void scanWithSuggestion(char *text, char *string, int numOptions, int stringSize, char options[numOptions][stringSize]);
#endif //AV2_SCAN_H
