
#include "function_prototypes.h"


//TBR => to be resolved

void RemoveNewline(char *string){
	string[strcspn(string, "\n")] = '\0';
}

void InitializeDatabase(entry *wordDatabase){
	int i;
	
	for (i = 0; i < DATABASE_SIZE; i++){
		wordDatabase[i].pairCount = 0;
	}
}

void DisplaySpecificEntries(entry *wordDatabase, int *displayArray, int displayArrayElements){
	int i, j;
	//TBR: This does not display inta-entry nor inter-entry
	for (i = 0; i < displayArrayElements; i++){
		printf("---[Item %d]\n", i+1);
		for (j = 0; j < wordDatabase[displayArray[i]].pairCount; j++){
			printf("Translation: %s\n", wordDatabase[displayArray[i]].pairs[j][0]);
			printf("Word: %s\n", wordDatabase[displayArray[i]].pairs[j][1]);
		}
		printf("---\n");
	}
};

void AddEntry(int *entryCount, entry *wordDatabase){
	//To remove line below in the future
	printf("The value of entry count is %d\n", *entryCount);
	string20 translation,
			 word;
	char response[RESPONSE_SIZE];
	int sentinel = 1;
	//TBR: Maybe this could be a struct
	int displayArray[DATABASE_SIZE];
	int displayArrayElements = 0;

	
	do {
		displayArrayElements = 0;
		getchar();
		printf("Indicate desired translation: ");
		fgets(translation, sizeof(translation), stdin);
		RemoveNewline(translation);
		
		printf("Indicate desired word: ");
		fgets(word, sizeof(word), stdin);
		RemoveNewline(word);
	
		if (SearchTranslation(word, translation, wordDatabase, entryCount, displayArray, &displayArrayElements)){
			printf("Word found\n");
			DisplaySpecificEntries(wordDatabase, displayArray, displayArrayElements);
			
			printf("Is this a new entry? ");
			scanf("%s", response);
			
			if (strcmp(response, "yes") == 0){
				InputEntryData(word, translation, wordDatabase, entryCount, -1);
				printf("New entry successfully created\n");
				printf("Do you want to input another language translation pair?\n");
				scanf("%s", response);
				
				if (strcmp(response, "no") == 0){
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				}
						
			} else if (strcmp(response, "no") == 0){
				sentinel = 0;
				ManageDataMenu(entryCount, wordDatabase);
			}
			
		} else {
			printf("Word is not found\n");
			printf("Is this a new entry? ");
			scanf("%s", response);
			
			if (strcmp(response, "yes") == 0){
				InputEntryData(word, translation, wordDatabase, entryCount, -1);
				printf("Do you want to input another language translation pair?\n");
				scanf("%s", response);
				
				if (strcmp(response, "no") == 0){
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				}
						
			} else if (strcmp(response, "no") == 0){
				sentinel = 0;
				ManageDataMenu(entryCount, wordDatabase);
			}
		}
	} while (sentinel == 1);
}

void InputEntryData(char *word, char *translation, entry *wordDatabase, int *entryCount, int mode){
	// TBR: what if all entries are taken?
	int i;

	if (mode == -1){
		for (i = 0; i < *entryCount; i++){
			if (wordDatabase[i].pairCount == 0){
				*entryCount += 1;
				strcpy(wordDatabase[i].pairs[0][0], translation);
				strcpy(wordDatabase[i].pairs[0][1], word);
				wordDatabase[i].pairCount+=1;
				i = *entryCount;
			}
		}
	} else {
		strcpy(wordDatabase[mode].pairs[wordDatabase[mode].pairCount][0], translation);
		strcpy(wordDatabase[mode].pairs[wordDatabase[mode].pairCount][1], word);
		wordDatabase[mode].pairCount+=1;
	}
	
};

void AddTranslations(int *entryCount, entry *wordDatabase){
	//To remove line below in the future
	string20 queryTranslation,
			 queryWord,
			 translation,
			 word;
	char response[RESPONSE_SIZE];
	
	int confirmation;
	int sentinel = 1;
	//TBR: Maybe this could be a struct
	int displayArray[DATABASE_SIZE];
	int displayArrayElements = 0;
	int translationID;
	
	displayArrayElements = 0;
	getchar();
	printf("Indicate desired translation: ");
	fgets(queryTranslation, sizeof(queryTranslation), stdin);
	RemoveNewline(queryTranslation);
	
	printf("Indicate desired word: ");
	fgets(queryWord, sizeof(queryWord), stdin);
	RemoveNewline(queryWord);

	if (SearchTranslation(queryWord, queryTranslation, wordDatabase, entryCount, displayArray, &displayArrayElements)){
		
		if (displayArrayElements > 1){
			DisplaySpecificEntries(wordDatabase, displayArray, displayArrayElements);
			printf("Language - Translation pairs have been found\n");

			printf("Please indicate which entry will be added translations\n");
			scanf("%d", &translationID);

			if (wordDatabase[displayArray[translationID-1]].pairCount == 10){
				printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
				ManageDataMenu(entryCount, wordDatabase);
			} else {
				while (sentinel == 1){
					getchar();
					printf("Indicate language to be added: ");
					fgets(translation, sizeof(translation), stdin);
					RemoveNewline(translation);
					
					printf("Indicate word translation to be added: ");
					fgets(word, sizeof(word), stdin);
					RemoveNewline(word);
					
					InputEntryData(word, translation, wordDatabase, entryCount, displayArray[translationID-1]);
	
					printf("Successfully added to entry\n");
	
					if (wordDatabase[displayArray[0]].pairCount == 10){
						printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
						sentinel = 0;
					}
					printf("Would you like to add more translations to the same entry?\n");
					scanf("%s", response);
	
					if (strcmp(response, "no") == 0){
						sentinel = 0;
						ManageDataMenu(entryCount, wordDatabase);
					}
				}
			}
			
		} else if (displayArrayElements == 1){
			DisplaySpecificEntries(wordDatabase, displayArray, displayArrayElements);
			printf("A Language - Translation pair has been found\n");

			if (wordDatabase[displayArray[0]].pairCount == 10){
				printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
				ManageDataMenu(entryCount, wordDatabase);
			} else {
				while (sentinel == 1){
					getchar();
					printf("Indicate language to be added: ");
					fgets(translation, sizeof(translation), stdin);
					RemoveNewline(translation);
					
					printf("Indicate word translation to be added: ");
					fgets(word, sizeof(word), stdin);
					RemoveNewline(word);
					
					InputEntryData(word, translation, wordDatabase, entryCount, displayArray[0]);
	
					printf("Successfully added to entry\n");
	
					if (wordDatabase[displayArray[0]].pairCount == 10){
						printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
						sentinel = 0;
					}
					printf("Would you like to add more translations to the same entry?\n");
					scanf("%s", response);
	
	
					if (strcmp(response, "no") == 0){
						sentinel = 0;
						ManageDataMenu(entryCount, wordDatabase);
					}
				}
			}
			
		}
		
	} else {
		printf("Word is not found\n");
		printf("Please return to the Manage Data menu and use the Add Entry option\n");
	
		while (confirmation != 1){
			printf("Input 1 if understood\n");
			scanf("%d", &confirmation);
			
			if (confirmation == 1){
				ManageDataMenu(entryCount, wordDatabase);
			} else {
				printf("Unrecognized command, please re-input\n");
			}
		}
		
	}
}

void DeleteEntry(){

}

void DeleteTranslation(){
    
}

void DisplayAllEntries(){
    
}

void SearchWord(char word, struct entryTag wordDatabase){
	//
}

int SearchTranslation(char *word, char *translation, entry *wordDatabase, int *entryCount, int *displayArray, int *displayArrayElements){
	int i, j, found = 0;
	int displayIndex = 0;
	
	for (i = 0; i < *entryCount; i++){
		for (j = 0; j < wordDatabase[i].pairCount; j++){
				
			if (strcmp(wordDatabase[i].pairs[j][0], translation) == 0 && strcmp(wordDatabase[i].pairs[j][1], word) == 0){
				found = 1; 
				displayArray[displayIndex] = i;
				*displayArrayElements += 1;
				displayIndex += 1;
				// print entry...
			}
				
			
		}
	}
	
	return found;
}

void Export(){

}

void Import(){
}

void TranslateTextInput(){

}

void TranslateTextFile(){

}

void ManageDataMenu(int *entryCount, entry *wordDatabase){
	system("cls");
	
	int action;
	
	printf("MANAGE DATA\n");
	printf("[1] -> Add Entry\n");
	printf("[2] -> Add Translations\n");
	printf("[3] -> Delete Entry\n");
	printf("[4] -> Delete Translation\n");
	printf("[5] -> Display All Entries\n");
	printf("[6] -> Search Word\n");
	printf("[7] -> Search Translation\n");
	printf("[8] -> Export\n");
	printf("[9] -> Import\n");
	printf("[0] -> Exit\n");
	
	scanf("%d", &action);
	
	switch (action){
    	case 1:
    		AddEntry(entryCount, wordDatabase);
    		break;
    	case 2: 
    		AddTranslations(entryCount, wordDatabase);
    		break;
    	case 3:
    		// DeleteEntry();
    		break;
    	case 4: 
    		// DeleteTranslation();
    		break;
    	case 5:
    		// DisplayAllEntries();
    		break;
    	case 6: 
    		// SearchWord();
    		break;
    	case 7:
    		// SearchTranslation();
    		break;
    	case 8: 
    		// Export();
    		break;
    	case 9:
    		// Import();
    		break;
    	default:
    		MainMenu(entryCount, wordDatabase);
    		break;
	}

}

void TranslateMenu(int *entryCount, entry* wordDatabase){
	system("cls");
	
	int action;
	
	printf("TRANSLATE MENU\n");
	printf("[1] -> Translate Text Input\n");
	printf("[2] -> Translate Text File\n");
	printf("[0] -> Exit\n");
	
	scanf("%d", &action);
	
	switch (action){
    	case 1:
    		// TranslateTextInput();
    		break;
    	case 2: 
    		// TranslateTextFile();
    		break;
    	case 3:
    		MainMenu(entryCount, wordDatabase);
    		break;
	}	
}

void MainMenu(int *entryCount, entry *wordDatabase){
	system("cls");
	int action;
    
    //to change font in the future
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t     Welcome to the Library of Babel\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("[1] -> Manage Data\n");
    printf("[2] -> Translation Panel\n");
    printf("[0] -> Exit Program\n");
    
    
    scanf("%d", &action);
    
    switch (action){
    	case 1: 
    		ManageDataMenu(entryCount, wordDatabase);
    		break;
    	case 2:
    		TranslateMenu(entryCount, wordDatabase);
    		break;
    	default:
    		printf("Thank you for using our program!");
    		break;
	}
}

int main(){
	int entryCount = 10;
	
	int temp;
	entry wordDatabase[DATABASE_SIZE];	
		
	InitializeDatabase(wordDatabase);
	
	strcpy(wordDatabase[0].pairs[0][0], "english");
	strcpy(wordDatabase[0].pairs[0][1], "love");
	strcpy(wordDatabase[0].pairs[1][0], "tagalog");
	strcpy(wordDatabase[0].pairs[1][1], "mahal");
	wordDatabase[0].pairCount = 2;
	
	strcpy(wordDatabase[1].pairs[0][0], "tagalog");
	strcpy(wordDatabase[1].pairs[0][1], "mahal");
	strcpy(wordDatabase[1].pairs[1][0], "kapampangan");
	strcpy(wordDatabase[1].pairs[1][1], "mal");
	wordDatabase[1].pairCount = 2;
	
	//TBR: Line below to be removed in the future
	printf("Word DB pair count: %d", wordDatabase[0].pairCount);
	scanf("%d", &temp);
    MainMenu(&entryCount, wordDatabase);
    
    

    return 0;
}
