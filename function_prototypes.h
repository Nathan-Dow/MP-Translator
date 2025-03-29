
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 150

typedef char string20[21];
typedef char string30[31];
typedef char string150[151];

typedef struct entryTag{
	string20 pairs[10][2];
	int pairCount;
} entry;


void swapEntries(entry *entry1, entry *entry2);
void SortDatabase(int DbEntries, entry *wordDatabase);
void DisplayAllEntries(int *entryCount, entry *wordDatabase, int mode);
void DisplaySpecificEntries(entry *wordDatabase, int *displayArray, int displayArrayElements);
int SearchTranslation(char *word, char *translation, entry *wordDatabase, int *entryCount, int *displayArray, int *displayArrayElements);
void RemoveNewline(char *string);
void InputEntryData(char *word, char *translation, entry *wordDatabase, int *entryCount, int pairNumber);
void ManageDataMenu(int *entryCount, entry *wordDatabase);
void TranslateMenu(int *entryCount, entry* wordDatabase);
void MainMenu(int *entryCount, entry *wordDatabase);
