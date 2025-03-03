
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN20 21
#define DATABASE_SIZE 150
#define RESPONSE_SIZE 4

typedef char string20[STRING_LEN20];

typedef struct entryTag{
	string20 pairs[10][2];
	int pairCount;
} entry;

void DisplaySpecificEntries(entry *wordDatabase, int *displayArray, int displayArrayElements);
int SearchTranslation(char *word, char *translation, entry *wordDatabase, int *entryCount, int *displayArray, int *displayArrayElements);
void RemoveNewline(char *string);
void InputEntryData(char *word, char *translation, entry *wordDatabase, int *entryCount, int pairNumber);
void ManageDataMenu(int *entryCount, entry *wordDatabase);
void MainMenu(int *entryCount, entry *wordDatabase);
