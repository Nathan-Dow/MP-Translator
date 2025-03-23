
#include "function_prototypes.h"



void RemoveNewline(char *string){
	string[strcspn(string, "\n")] = '\0';
}

void InitializeDatabase(entry *wordDatabase){
	int i, j;
	for (i = 0; i < DATABASE_SIZE; i++){
		for (j = 0; j < 10; j++){
			//This sets the first index of the language and translation to a null byte, removing all contents of the string
			wordDatabase[i].pairs[j][0][0] = '\0';
			wordDatabase[i].pairs[j][1][0] = '\0';
		}
		wordDatabase[i].pairCount = 0;
	}
}

void DisplaySpecificEntries(entry *wordDatabase, int *displayArray, int displayArrayElements){
	int i, j;
	//TBR: This does not display inta-entry nor inter-entry
	for (i = 0; i < displayArrayElements; i++){
		printf("\nEntry No: [%d]\n", i+1);
		printf("------------------------------------------------\n");
		printf("%-25s | %20s\n", "Language", "Translation");
		printf("------------------------------------------------\n");

		for (j = 0; j < wordDatabase[displayArray[i]].pairCount; j++){
			printf("%-20s [%02d] | ", wordDatabase[displayArray[i]].pairs[j][0], j+1);
			printf("%20s\n", wordDatabase[displayArray[i]].pairs[j][1]);
		}
		printf("------------------------------------------------\n");
	}
};

void AddEntry(int *entryCount, entry *wordDatabase){
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
			printf("Displaying instances of language translation pair matches in current database \n");
			DisplaySpecificEntries(wordDatabase, displayArray, displayArrayElements);
			
			printf("Is this a new entry? ");
			scanf("%s", response);
			
			if (strcmp(response, "yes") == 0){
				InputEntryData(word, translation, wordDatabase, entryCount, -1);
				printf("The value of entry count is %d\n", *entryCount);
				printf("New entry successfully created\n");
				printf("Do you want to input another language translation pair?[y/n]\n");
				scanf("%s", response);
				//TBR: need to lowercase every input


				if (strcmp(response, "yes") != 0){
					sentinel = 0;
					if (strcmp(response, "n")){
						printf("Redirecting to Manage Data Menu\n");
					} else {
						printf("Incorrect input, redirecting to Manage Data Menu\n");
					}
					ManageDataMenu(entryCount, wordDatabase);
				}
						
			} else if (strcmp(response, "no") == 0){
				sentinel = 0;
				printf("Redirecting to Manage Data Menu\n");
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
	
	//mode = -1 : to add a new entry
	//mode != -1 : to add a new translation to an existing entry
	if (mode == -1){
		strcpy(wordDatabase[*entryCount].pairs[0][0], translation);
		strcpy(wordDatabase[*entryCount].pairs[0][1], word);
		wordDatabase[*entryCount].pairCount = 1;
		*entryCount += 1;
	
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
					
					// TBR: Must receive yes response only
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

void DeleteEntry(int *entryCount, entry *wordDatabase){
	int deleteID, i, j;

	DisplayAllEntries(entryCount, wordDatabase, -1);

	if (*entryCount != 0){
		printf("Which entry would you like to delete [number]? ");
		scanf("%d", &deleteID);

		if (deleteID >= 1 && deleteID <= *entryCount){
			for (i = 0; i < wordDatabase[deleteID-1].pairCount; i++){
				for (j = 0; j < 2; j++){
					strcpy(wordDatabase[deleteID-1].pairs[i][j], "");
				}
			}
			wordDatabase[deleteID-1].pairCount = 0;
			*entryCount -=1;
			printf("Successfully deleted\n");
			ManageDataMenu(entryCount, wordDatabase);
		} else {
			printf("Input has been incorrect, redirecting to Manage Data Menu\n");
			ManageDataMenu(entryCount, wordDatabase);
		}
	} else {
		ManageDataMenu(entryCount, wordDatabase);
	}
	
}

void DeleteTranslation(int *entryCount, entry *wordDatabase){
    int i, entryID, translationID, sentinel = 1;
	char response;

	DisplayAllEntries(entryCount, wordDatabase, -1);

	if (*entryCount != 0){
		printf("From which entry would you like to delete a language-translation pair?\n");

		scanf("%d", &entryID);

		if (entryID >= 1 && entryID <= *entryCount){
			do{
				printf("What language-translation pair would you want to be deleted? [Number]\n");
				printf("Input [-1] to stop deletion\n");
				scanf("%d", &translationID);

				if (translationID >= 1 && translationID <= wordDatabase[entryID-1].pairCount){

					for (i = translationID; i < wordDatabase[entryID-1].pairCount; i++){
						strcpy(wordDatabase[entryID - 1].pairs[i - 1][0], wordDatabase[entryID - 1].pairs[i][0]);
						strcpy(wordDatabase[entryID - 1].pairs[i - 1][1], wordDatabase[entryID - 1].pairs[i][1]);
					}
					strcpy(wordDatabase[entryID - 1].pairs[wordDatabase[entryID - 1].pairCount - 1][0], "");
					strcpy(wordDatabase[entryID - 1].pairs[wordDatabase[entryID - 1].pairCount - 1][1], "");

					wordDatabase[entryID - 1].pairCount -= 1;

					if (wordDatabase[entryID-1].pairCount == 0){
						*entryCount -= 1;
						printf("Successfully deleted language-translation pair\n");
						printf("Entry has been deleted completely\n");
						printf("Redirecting to Manage Data Menu\n");
						sentinel = 0;
						SortDatabase(*entryCount, wordDatabase);
						ManageDataMenu(entryCount, wordDatabase);
					} else {
						SortDatabase(*entryCount, wordDatabase);
						printf("Successfully deleted language-translation pair\n");
					}

					

				} else if (translationID == -1){
					printf("Redirecting to Manage Data Menu\n");
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else {
					//not accounting for already 0 language-translation pairs in entry
					printf("Invalid translation-pair ID given. Would you like to retry?[y/n] \n");
					scanf(" %c", &response);

					if (response != 'y'){
						printf("Redirecting to Manage Data Menu\n");
						sentinel = 0;
						ManageDataMenu(entryCount, wordDatabase);
					}
				}

			} while (sentinel);
		} else {
			printf("Input has been incorrect, redirecting to Manage Data Menu\n");
			ManageDataMenu(entryCount, wordDatabase);
		}
	} else {
		ManageDataMenu(entryCount, wordDatabase);
	}

	

}

void DisplayAllEntries(int *entryCount, entry *wordDatabase, int mode){
	//mode = 1 would return to ManageDataMenu()
	//mode = -1 would be for delete entry/delete translation
	int i = 0, j, sentinel = 1;
	
	int validInput;
	char response;

    SortDatabase(*entryCount, wordDatabase);

	if (*entryCount == 0){
		printf("Database currently has no entries\n");
		printf("Redirecting to Manage Data menu\n\n");
	} else {
		do{
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");
			//TBR: This could be a separate function
			for (j = 0; j < wordDatabase[i].pairCount; j++){
				printf("%-20s [%02d] | ", wordDatabase[i].pairs[j][0], j+1);
				printf("%20s\n", wordDatabase[i].pairs[j][1]);
					
			}
			printf("------------------------------------------------\n");
			printf("Press 'X' to end the display\n");
			if (i < *entryCount - 1)
				printf("Press 'N' to view the next entry\n");
			if (i > 0)
				printf("Press 'P' to view the previous entry\n");
	
			validInput = 0;
			
			do {
				getchar();
				printf("Enter your choice: ");
				scanf("%c", &response);
	
				if (response == 'X'){
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
				} else if (response == 'N' && i < *entryCount -1){
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0){
					i--;
					validInput = 1;
				} else {
					printf("Invalid input or out of bounds\n");
				}
			} while (!validInput);
	
		} while (sentinel);
	
	}

	if (mode > 0){
		ManageDataMenu(entryCount, wordDatabase);
	}
	
	
}

void SearchWord_With_Display(int *entryCount, entry *wordDatabase){
	SortDatabase(*entryCount, wordDatabase);
	int i = 0, j, k, sentinel = 1;
	
	string20 searchingWord;

	int validInput;
	int foundCopies = 0;

	int foundWord;
	int copiesArray[DATABASE_SIZE];

	char response;


	printf("Input the word you want to search in the database: ");
	//TBR: Must check for incorrect input
	scanf("%s", searchingWord);

	//must search for the word

	for (i = 0; i < *entryCount; i++){
		foundWord = 0;
		for (j = 0; j < wordDatabase[i].pairCount && foundWord == 0; j++){
			// printf("%s\n", wordDatabase[i].pairs[j][1]);
			// printf("Searching word: [%s]\n", searchingWord);
			if (strcmp(wordDatabase[i].pairs[j][1], searchingWord) == 0){
				copiesArray[foundCopies] = i;
				foundCopies += 1;
				foundWord = 1;
			}
		}
	}
	



	if (foundCopies > 0){
		i = 0;
		do {
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//TBR: This could be a separate function
			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase

			for (j = 0; j < wordDatabase[copiesArray[i]].pairCount; j++){
				for (k = 0; k < 2; k++){
					if (k == 0)
						printf("%-20s [%02d] | ", wordDatabase[copiesArray[i]].pairs[j][k], j+1);
					else	
						printf("%20s\n", wordDatabase[copiesArray[i]].pairs[j][k]);
				}
			}
			printf("------------------------------------------------\n");
			printf("Press 'X' to end the display\n");
			if (i < foundCopies - 1)
				printf("Press 'N' to view the next entry\n");
			if (i > 0)
				printf("Press 'P' to view the previous entry\n");

			validInput = 0;
			
			do {
				getchar();
				printf("Enter your choice: ");
				scanf("%c", &response);

				if (response == 'X'){
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else if (response == 'N' && i < *entryCount -1){
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0){
					i--;
					validInput = 1;
				} else {
					printf("Invalid input or out of bounds\n");
				}
			} while (!validInput);

		} while (sentinel);

	} else {
		printf("There are no word matches in the database\n");
		printf("Redirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
	
}

void SearchTranslation_With_Display(int *entryCount, entry *wordDatabase){
	SortDatabase(*entryCount, wordDatabase);
	int i = 0, j, k, sentinel = 1;
	
	string20 searchingWord;
	string20 searchingTranslation;

	int validInput;
	int foundCopies = 0;

	int foundWord;
	int copiesArray[DATABASE_SIZE];

	char response;


	printf("Input the translation you want to search in the database: ");
	//TBR: Must check for incorrect input
	scanf("%s", searchingTranslation);

	printf("Input the word you want to search in the database: ");
	scanf("%s", searchingWord);

	//must search for translation-wrod pair
	for (i = 0; i < *entryCount; i++){
		foundWord = 0;
		for (j = 0; j < wordDatabase[i].pairCount && foundWord == 0; j++){
			if (strcmp(wordDatabase[i].pairs[j][0], searchingTranslation) == 0 && strcmp(wordDatabase[i].pairs[j][1], searchingWord) == 0){
				copiesArray[foundCopies] = i;
				foundCopies += 1;
				foundWord = 1;
			}
		}
	}
	



	if (foundCopies > 0){
		i = 0;
		do {
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//TBR: This could be a separate function
			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase

			for (j = 0; j < wordDatabase[copiesArray[i]].pairCount; j++){
				for (k = 0; k < 2; k++){
					if (k == 0)
						printf("%-20s [%02d] | ", wordDatabase[copiesArray[i]].pairs[j][k], j+1);
					else	
						printf("%20s\n", wordDatabase[copiesArray[i]].pairs[j][k]);
				}
			}
			printf("------------------------------------------------\n");
			printf("Press 'X' to end the display\n");
			if (i < foundCopies - 1)
				printf("Press 'N' to view the next entry\n");
			if (i > 0)
				printf("Press 'P' to view the previous entry\n");

			validInput = 0;
			
			do {
				getchar();
				printf("Enter your choice: ");
				scanf("%c", &response);

				if (response == 'X'){
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else if (response == 'N' && i < *entryCount -1){
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0){
					i--;
					validInput = 1;
				} else {
					printf("Invalid input or out of bounds\n");
				}
			} while (!validInput);

		} while (sentinel);

	} else {
		printf("There are no word matches in the database\n");
		printf("Redirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
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

void Export(int *entryCount, entry *wordDatabase){
	int i, j;
	FILE* fPtr;
	string30 filename;
	string20 language, translation;

	printf("Indicate file name of text file: ");
	//TBR: need to verify correct input
	scanf("%s", filename);
	strcat(filename, ".txt");

	fPtr = fopen(filename, "w");

	for (i = 0; i < *entryCount; i++){
		for (j = 0; j < wordDatabase[i].pairCount; j++){
			//TBR: First character should be capitalized
			strcpy(language, wordDatabase[i].pairs[j][0]);
			strcat(language, ": ");
			strcpy(translation, wordDatabase[i].pairs[j][1]);
			strcat(translation, "\n");
			
			fputs(language, fPtr);
			fputs(translation, fPtr);
		}
		fputs("\n", fPtr);
	}

	fclose(fPtr);
	printf("Export has been successful\n");
}

void Import(int *entryCount, entry *wordDatabase){
	int i, j;
	FILE* fPtr;
	string30 filename;
	
	char perLineText[43];
	char response;

	string20 tempLanguage, tempTranslation;
	entry tempEntryDB[DATABASE_SIZE];
	int tempEntryCount = 0, colonIndex;

	int line = 0, dataAdded = 0;

	InitializeDatabase(tempEntryDB);
	
	printf("Indicate file to import data from: ");
	scanf("%s", filename);
	strcat(filename, ".txt");

	fPtr = fopen(filename, "r");

	if (fPtr != NULL){
		//need to only fill 150
		while (fgets(perLineText, 43, fPtr)){
			//printf("%s", perLineText);

			//gets index of the colon in perlinetext
			//need to check if 10
			if (strcmp(perLineText, "\n") != 0){
				colonIndex = -1;
				for (i = 0; i < strlen(perLineText) && colonIndex == -1; i++){
					if (perLineText[i] == ':'){
						colonIndex = i;
					}
				}
				//this gets the temporary language
				strncpy(tempLanguage, perLineText, colonIndex);
				tempLanguage[colonIndex] = '\0';

				//this gets the temporary Translation
				strcpy(tempTranslation, &perLineText[colonIndex+2]);
				RemoveNewline(tempTranslation);
				// we could replace this with input entry data function
		
				strcpy(tempEntryDB[tempEntryCount].pairs[line][0], tempLanguage);
				strcpy(tempEntryDB[tempEntryCount].pairs[line][1], tempTranslation);
				tempEntryDB[tempEntryCount].pairCount += 1;
				//printf("TempLanugage is: %s", tempLanguage);
				//printf("TempTranslaiton is: %s", tempTranslation);

				printf("Entry: %d\n", tempEntryCount);
				printf("%s: %s\n", tempLanguage, tempTranslation);

				
				line+= 1;
				//could just set this to one
				dataAdded += 1;
			} else if (dataAdded > 0){
				//tempEntryDB[tempEntryCount].pairCount = line;
				//printf("Insertion // TempEntryCount: %d", tempEntryCount);
				line = 0;
				tempEntryCount += 1;
				
			} 

		}

		if (dataAdded > 0){
			tempEntryCount += 1;
			printf("Temp Entry Count: %d", tempEntryCount);
		}
		
		
		for (i = 0; i < tempEntryCount; i++){
			printf("Number of Translation Pairs: %d\n", tempEntryDB[i].pairCount);
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//TBR: This could be a separate function
			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase
			for (j = 0; j < tempEntryDB[i].pairCount; j++){
	
				printf("%-20s [%02d] | ", tempEntryDB[i].pairs[j][0], j+1);
				printf("%20s\n", tempEntryDB[i].pairs[j][1]);
				
			}

			printf("------------------------------------------------\n");

			printf("Would you like to add this entry to the Database?[y,n]\n");
			getchar();
			scanf("%c", &response);
			if (response == 'y'){
				//need to check if wordDatabase is full
				//input this sole entry into the mainDB
				for (j = 0; j < tempEntryDB[i].pairCount; j++){
					strcpy(wordDatabase[*entryCount].pairs[j][0], tempEntryDB[i].pairs[j][0]);
					strcpy(wordDatabase[*entryCount].pairs[j][1], tempEntryDB[i].pairs[j][1]);
					wordDatabase[*entryCount].pairCount += 1;
				}
				*entryCount += 1;
				printf("Successfully imported data into Word Database\n");
			} else if (response == 'n'){
				//need to differ response when there are no more entries to add
				printf("Viewing next entry in source file\n");
			} else {
				//need to differ response when there are no more entries to add
				printf("Improper input, displaying next entry in source file\n");
			}
		
		}
		
		SortDatabase(*entryCount, wordDatabase);
		ManageDataMenu(entryCount, wordDatabase);
		
	} else {
		printf("File cannot be retrieved, redirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
}

void TranslateTextInput(){

}

void TranslateTextFile(){

}

void ManageDataMenu(int *entryCount, entry *wordDatabase){
	
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
    		DeleteEntry(entryCount, wordDatabase);
    		break;
    	case 4: 
    		DeleteTranslation(entryCount, wordDatabase);
    		break;
    	case 5:
    		DisplayAllEntries(entryCount, wordDatabase, 1);
    		break;
    	case 6: 
    		SearchWord_With_Display(entryCount, wordDatabase);
    		break;
    	case 7:
    		SearchTranslation_With_Display(entryCount, wordDatabase);
    		break;
    	case 8: 
    		Export(entryCount, wordDatabase);
    		break; 
    	case 9:
    		Import(entryCount, wordDatabase);
    		break;
    	default:
    		MainMenu(entryCount, wordDatabase);
    		break;
	}

}

void TranslateMenu(int *entryCount, entry* wordDatabase){

	int action;
	
	printf("TRANSLATE MENU\n");
	printf("[1] -> Translate Text Input\n");
	printf("[2] -> Translate Text File\n");
	printf("[0] -> Exit Menu\n");
	
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

void SortDatabase(int DbEntries, entry *wordDatabase){
	int i = 0, j, k, l, englishDbIndex = 0, nonEnglishDbIndex = 0, containsEnglish;
	int englishWordIndex1, englishWordIndex2;
	int successfulInsertions = 0;

	
	entry nonEnglishDatabase[DATABASE_SIZE], englishDatabase[DATABASE_SIZE];


	//Looping 1 - This should place entries with english entries to englishDatabase and entries with no english entries into the nonEnglishDatabase

	//goes through each entry in the database
	if (DbEntries > 0){
		while (successfulInsertions != DbEntries){
			//checks if any of the pairs in the entry contain english
			containsEnglish = 0;
			for (j = 0; j < wordDatabase[i].pairCount && containsEnglish == 0 && wordDatabase[i].pairCount > 0; j++){	
				//printf("wordDatabase paircount = %d\n", wordDatabase[i].pairCount);	
				if (strcmp(wordDatabase[i].pairs[j][0], "english") == 0){
					// copies all elements inside of the entry
					englishDatabase[englishDbIndex].pairCount = 0;
	
					for (k = 0; k < wordDatabase[i].pairCount; k++){
	
						for (l = 0; l < 2; l++){
							strcpy(englishDatabase[englishDbIndex].pairs[k][l], wordDatabase[i].pairs[k][l]);
						}
						
						englishDatabase[englishDbIndex].pairCount += 1;
					}
			
					containsEnglish = 1;
					englishDbIndex += 1;
					successfulInsertions += 1;
	
				} 
			}
	
			if (containsEnglish == 0 && wordDatabase[i].pairCount > 0){
				nonEnglishDatabase[nonEnglishDbIndex].pairCount = 0;
				for (k = 0; k < wordDatabase[i].pairCount; k++){
					for (l = 0; l < 2; l++){
						strcpy(nonEnglishDatabase[nonEnglishDbIndex].pairs[k][l], wordDatabase[i].pairs[k][l]);
					}
					nonEnglishDatabase[nonEnglishDbIndex].pairCount += 1;
				}
				nonEnglishDbIndex += 1;
				successfulInsertions += 1;
			}
			i += 1;
		}
	
		//loop 2 need to sort the english entries amongst themselves
	
		for (i = 0; i < englishDbIndex - 1; i++){
			for (j = 0; j < englishDbIndex - 1 - i; j++){
				//Need to find the english word and compare with the next english word of index j, implement normal swappinng
				englishWordIndex1 = -1;
				englishWordIndex2 = -1;
				for (k = 0; k < englishDatabase[j].pairCount && englishWordIndex1 == -1; k++){
					if (strcmp(englishDatabase[j].pairs[k][0], "english") == 0)
						englishWordIndex1 = k;
				}
	
				for (k = 0; k < englishDatabase[j+1].pairCount && englishWordIndex2 == -1; k++){
					if (strcmp(englishDatabase[j+1].pairs[k][0], "english") == 0)
						englishWordIndex2 = k;
				}
				
				if (strcmp(englishDatabase[j].pairs[englishWordIndex1][1], englishDatabase[j+1].pairs[englishWordIndex2][1]) > 0){
					swapEntries(&englishDatabase[j], &englishDatabase[j+1]);
				}
	
				
	
			}
		}
	
		//Sort intra-entry by alphabetical order [English]
	
		for (i = 0; i < englishDbIndex; i++) {
			// Perform bubble sort on the pairs of each entry
			for (j = 0; j < englishDatabase[i].pairCount - 1; j++) {
				for (k = 0; k < englishDatabase[i].pairCount - 1 - j; k++) {
					// Compare the languages (pairs[k][0] with pairs[k+1][0])
		
					if (strcmp(englishDatabase[i].pairs[k][0], englishDatabase[i].pairs[k+1][0]) > 0) {
						// Swap the pairs if they are not in the correct order
						string20 tempLanguage;
						string20 tempWord;
		
						// Copy current pair[k] into temp variables
						strcpy(tempLanguage, englishDatabase[i].pairs[k][0]);
						strcpy(tempWord, englishDatabase[i].pairs[k][1]);
		
						// Copy next pair[k+1] into pair[k]
						strcpy(englishDatabase[i].pairs[k][0], englishDatabase[i].pairs[k+1][0]);
						strcpy(englishDatabase[i].pairs[k][1], englishDatabase[i].pairs[k+1][1]);
		
						// Copy temp values (original pair[k]) into pair[k+1]
						strcpy(englishDatabase[i].pairs[k+1][0], tempLanguage);
						strcpy(englishDatabase[i].pairs[k+1][1], tempWord);
					}
				}
			}
		}
		
		//Sort intra-entry by alphabetical order [Non-english]
	
		//loop will combine the all entries
	
		for (i = 0; i < DbEntries; i++){
			if (i < englishDbIndex){
				for (j = 0; j < englishDatabase[i].pairCount; j++){
					for (k = 0; k < 2; k++){
						strcpy((wordDatabase+i)->pairs[j][k], englishDatabase[i].pairs[j][k]);
					}
				}
				(wordDatabase+i)->pairCount = englishDatabase[i].pairCount;
			} else {
				l = i - englishDbIndex;
				for (j = 0; j < nonEnglishDatabase[l].pairCount; j++){
					for (k = 0; k < 2; k++){
						strcpy((wordDatabase+i)->pairs[j][k], nonEnglishDatabase[l].pairs[j][k]);
					}
				}
				(wordDatabase+i)->pairCount = nonEnglishDatabase[l].pairCount;
				
			}
		}
	}

}

void swapEntries(entry *entry1, entry *entry2) {
    entry tempEntry;

	tempEntry = *entry1;
	*entry1 = *entry2;
	*entry2 = tempEntry;
    
}

void MainMenu(int *entryCount, entry *wordDatabase){

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
	int entryCount = 0;
	
	//int temp;
	entry wordDatabase[DATABASE_SIZE];	
		
	InitializeDatabase(wordDatabase);
	
	// strcpy(wordDatabase[0].pairs[0][0], "english");
	// strcpy(wordDatabase[0].pairs[0][1], "love");
	// strcpy(wordDatabase[0].pairs[1][0], "tagalog");
	// strcpy(wordDatabase[0].pairs[1][1], "mahal");
	// wordDatabase[0].pairCount = 2;
	
	// strcpy(wordDatabase[1].pairs[0][0], "tagalog");
	// strcpy(wordDatabase[1].pairs[0][1], "mahal");
	// strcpy(wordDatabase[1].pairs[1][0], "kapampangan");
	// strcpy(wordDatabase[1].pairs[1][1], "mal");
	// strcpy(wordDatabase[1].pairs[2][0], "english");
	// strcpy(wordDatabase[1].pairs[2][1], "affection");
	// wordDatabase[1].pairCount = 3;

	// strcpy(wordDatabase[0].pairs[0][0], "tagalog");
	// strcpy(wordDatabase[0].pairs[0][1], "kamusta");
	// strcpy(wordDatabase[0].pairs[1][0], "mandarin");
	// strcpy(wordDatabase[0].pairs[1][1], "ni hao");
	// wordDatabase[0].pairCount = 2;

	// strcpy(wordDatabase[1].pairs[0][0], "english");
	// strcpy(wordDatabase[1].pairs[0][1], "love");
	// strcpy(wordDatabase[1].pairs[1][0], "tagalog");
	// strcpy(wordDatabase[1].pairs[1][1], "mahal");
	// strcpy(wordDatabase[1].pairs[2][0], "hiligaynon");
	// strcpy(wordDatabase[1].pairs[2][1], "gugma");
	// strcpy(wordDatabase[1].pairs[3][0], "spanish");
	// strcpy(wordDatabase[1].pairs[3][1], "amor");
	// wordDatabase[1].pairCount = 4;

	// strcpy(wordDatabase[2].pairs[0][0], "tagalog");
	// strcpy(wordDatabase[2].pairs[0][1], "mahal");
	// strcpy(wordDatabase[2].pairs[1][0], "kapampangan");
	// strcpy(wordDatabase[2].pairs[1][1], "mal");
	// strcpy(wordDatabase[2].pairs[2][0], "cebuano");
	// strcpy(wordDatabase[2].pairs[2][1], "mahal");
	// strcpy(wordDatabase[2].pairs[3][0], "english");
	// strcpy(wordDatabase[2].pairs[3][1], "expensive");
	
	//wordDatabase[2].pairCount = 0;
	//TBR: Line below to be removed in the future
	// printf("No of entries: %d\n", entryCount);
	// printf("1st Entry Data: %s ", wordDatabase[0].pairs[0][0]);
	//printf("%s\n", wordDatabase[0].pairs[0][1]);
	

	SortDatabase(entryCount, wordDatabase);

	// printf("1st Entry Data: %s ", wordDatabase[0].pairs[0][0]);
	// printf("%s\n", wordDatabase[0].pairs[0][1]);
	// scanf("%d", &temp);
	//scanf("%d", &temp);
    MainMenu(&entryCount, wordDatabase);
    
    

    return 0;
}
