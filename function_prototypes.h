
#define STRING_LEN20 21
#define DATABASE_SIZE 150
#define YES_NO 4

typedef char string20[STRING_LEN20];

typedef struct entryTag{
	string20 pairs[10][2];
	int pairCount;
} entry;

int searchTranslation(char *word, char *translation, entry *wordDatabase, int *entryCount);
void inputEntryData(char *word, char *translation, entry *wordDatabase, int *entryCount);
void ManageDataMenu(int *entryCount, entry *wordDatabase);
void MainMenu(int *entryCount, entry *wordDatabase);
