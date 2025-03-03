#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function_prototypes.h"


//TBR => to be resolved

void initializeDatabase(entry *wordDatabase){
	int i;
	
	for (i = 0; i < DATABASE_SIZE; i++){
		wordDatabase[i].pairCount = 0;
	}
}

void AddEntry(int *entryCount, entry *wordDatabase){
	printf("The value of entry count is %d\n", *entryCount);
	string20 translation,
			 word;
	char response[YES_NO];
	int sentinel = 1;
	

	
	do {
		getchar();
		printf("Indicate desired translation: ");
		fgets(translation, sizeof(translation), stdin);
		
		printf("Indicate desired word: ");
		fgets(word, sizeof(translation), stdin);
	
		if (searchTranslation(word, translation, wordDatabase, entryCount)){
			printf("Word found");
		} else {
			printf("Word is not found\n");
			printf("Is this a new entry? ");
			scanf("%s", response);
			
			if (strcmp(response, "yes") == 0){
				inputEntryData(word, translation, wordDatabase, entryCount);
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
	
	
	//findInDatabase => searchTranslation(translation) && searchWord(word)

	/*
	if (findInDatabase(translation, word){
		for (all entries which were found){
			displayEntry();
		}
		printf("Is this a new entry?")
		fgets(response, sizeof(response), stdin);

		if (response == "YES"){
			
		} else if (response == "NO"){
		 	ManageDataMenu();
		}
	}
	*/

    /*
    Asks language and translation pair
    
    */
}

void inputEntryData(char *word, char *translation, entry *wordDatabase, int *entryCount){
	// TBR: what if all entries are taken?
	int i;
	for (i = 0; i < *entryCount; i++){
		if (wordDatabase[i].pairCount == 0){
			*entryCount += 1;
			strcpy(wordDatabase[i].pairs[0][0], translation);
			strcpy(wordDatabase[i].pairs[0][1], word);
			wordDatabase[i].pairCount+=1;
			
			printf("Translation of entry %d: %s\n", i, wordDatabase[i].pairs[0][0]);
			printf("Word of entry %d: %s\n", i, wordDatabase[i].pairs[0][1]);
			
			i = *entryCount;
		}
	}
};

void AddTranslations(){

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

int searchTranslation(char *word, char *translation, entry *wordDatabase, int *entryCount){
	int i, j, found = 0;
	
	for (i = 0; i < *entryCount; i++){
		for (j = 0; j < wordDatabase[i].pairCount; j++){
			if (strcmp(wordDatabase[i].pairs[j][0], translation) == 0 && strcmp(wordDatabase[i].pairs[j][1], word) == 0){
				found = 1; 
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
    		// AddTranslations();
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
	entry wordDatabase[DATABASE_SIZE];	
		
	initializeDatabase(wordDatabase);
	
	strcpy(wordDatabase[0].pairs[0][0], "english");
	strcpy(wordDatabase[0].pairs[0][1], "love");
	strcpy(wordDatabase[0].pairs[1][0], "tagalog");
	strcpy(wordDatabase[0].pairs[1][1], "mahal");
	wordDatabase[0].pairCount = 2;
    MainMenu(&entryCount, wordDatabase);
    
    

    return 0;
}
