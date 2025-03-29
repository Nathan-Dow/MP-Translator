
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

void RemoveNewline(char *string);
void clearInputBuffer();
void inputString(char* str, int size);
int intInput(int low, int high);
void inputYesNo(int *decision);
void toLowerCase(char *string);
void tokenizeString(char* str, string150* strArr);
void InitializeDatabase(int *entryCount, entry *wordDatabase);
void DisplaySpecificEntries(entry *wordDatabase, int *FoundEntryArray, int FoundEntryArrayElements);
void AddEntry(int *entryCount, entry *wordDatabase);
void InputEntryData(char *word, char *language, entry *wordDatabase, int *entryCount, int mode);
void AddTranslations(int *entryCount, entry *wordDatabase);
void DeleteEntry(int *entryCount, entry *wordDatabase);
void DeleteTranslation(int *entryCount, entry *wordDatabase);
void DisplayAllEntries(int *entryCount, entry *wordDatabase, int mode);
void SearchWord_With_Display(int *entryCount, entry *wordDatabase);
void SearchTranslation_With_Display(int *entryCount, entry *wordDatabase);
int SearchTranslation(char *word, char *language, entry *wordDatabase, int *entryCount, int *FoundEntryArray, int *FoundEntryArrayElements);
void Export(int *entryCount, entry *wordDatabase);
void Import(int *entryCount, entry *wordDatabase, int condition);
void translate(string150 text, string20 srcLanguage, string20 finLanguage, string150* strArr, int *entryCount, entry *wordDatabase);
void TranslateTextInput(int *entryCount, entry *wordDatabase);
void TranslateTextFile(int *entryCount, entry *wordDatabase);
void ManageDataMenu(int *entryCount, entry *wordDatabase);
void TranslateMenu(int *entryCount, entry* wordDatabase);
void SortDatabase(int entryCount, entry *wordDatabase);
void swapEntries(entry *entry1, entry *entry2);
void MainMenu(int *entryCount, entry *wordDatabase);
