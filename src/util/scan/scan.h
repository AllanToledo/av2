//
// Created by allan on 19/06/2022.
//

#ifndef AV2_SCAN_H
#define AV2_SCAN_H
void printWithSuggestion(char *text, char *suggestion, char *string);

int smithWaterman(char *s1, char *s2);
void scanString(char *string, int stringSize);

void scanWithSuggestion(char *text, char *string, int numOptions, int stringSize, char options[numOptions][stringSize]);
void scanSelection(char *result, int countOptions, int stringLength, char options[countOptions][stringLength]);

#endif //AV2_SCAN_H
