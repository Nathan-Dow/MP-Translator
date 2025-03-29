
#include "function_prototypes.h"

/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
<Nathan Gabriel D. Dolot, Franz Patrick Magbitang>, DLSU ID# <12410195, ..., respectively>
*********************************************************************************************************/

/*
RemoveNewLine function modifies the input string such that it removes the newline escape character
@param string - string containing only 1 word
@return N/A
Pre-condition: None
*/
void 
RemoveNewline(char *string)
{
	string[strcspn(string, "\n")] = '\0';
}

/* clearInputBuffer function clears the input buffer by reading the buffer characters until the end and discards them
@return - N/A
Pre-condition: None
Note: As this is just to prevent the program from breaking when entering the wrong input type, it is best to treat this function as if it doesn't exist and avoid using the wrong input types (e.g. string input on int)
*/
void 
clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* inputString function handles string input and input errors
@param str - address where the string input is assigned to
@param size - size of the string input
@return - N/A
Pre-condition: None
*/
void 
inputString(char* str, int size)
{
	int valid = 0;
	do
	{
		fgets(str, size, stdin);
		RemoveNewline(str);
		
		if (strlen(str) < 1)
		{
			printf("Please input a string that has atleast 1 character\n");
		} else
		{
			valid = 1;
		}
	} while(!valid);
}

/* intInput function is used for various integer inputs that will be done by the user
@param low - lowest value that choice is allowed to be
@param high - highest value that choice is allowed to be
@return - value of choice, if valid
@Pre-condition: The input is an integer and high's value is now lower than low
*/
int 
intInput(int low, int high) 
{
    int choice;
    char buffer[50]; // Buffer to store user input as a string
    int validInput = 0; // Flag to check if input is valid
	
    while (!validInput) { // Keep looping until valid input is received
        printf("Input (%d - %d): ", low, high);

        // Read input as a string
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Try converting input to an integer
            if (sscanf(buffer, "%d", &choice) == 1) {
                // Check if input is within range
                if (choice >= low && choice <= high) {
                    validInput = 1; // 
                } else {
                    printf("Out of range! Please enter a number between %d and %d.\n", low, high);
                }
            } else {
                printf("Invalid input. Please enter a valid number between %d and %d.\n", low, high);
            }
        } else {
            printf("Input error. Please try again.\n");
        }
    }

    return choice;
}

/* inputYesNo function is used for various yes or no inputs that will be done by the user
@param decision - address where the corresponding value of the yes/no input will be stored
@return - N/A
Pre-condition: The input is a singular string
*/
void
inputYesNo(int *decision)
{
	char input[4];
	*decision = -999;
	//do-while loop to repeat if the input is invalid
	do
	{
		printf("Input: ");
		scanf(" %4s", input);
		//clears stray chars on the input
		
		clearInputBuffer();
		//checks if the input is valid or not
		
		if (strcmp(input, "yes") == 0){
			*decision = 1;
		} else if (strcmp(input, "no") == 0){
			*decision = 0;
		} else {
			printf("Invalid input. Please try again.\n");
		}
	
	} while(*decision != 1 && *decision != 0);
}

/* toLowercase function sets the input string to all lowercase
@param string - original string to be modified
@return - N/A
Pre-condition: Characters in the input string are all from the english alphabet
*/
void 
toLowerCase(char *string)
{
	int i;

	for(i=0; i<strlen(string); i++)
	{
		if(string[i] >= 'A' && string[i] <= 'Z')
			string[i]+=32;
	}
}

void 
tokenizeString(char* str, string150* strArr)
{
	char word[151];
	int i, j=0, k=0; //i: index of the string input, j: index of word, k: index of string array

	//convert str to lowercase
	toLowerCase(str);
	for(i=0; i<150; i++)
	{
		//if str[i] is a letter, append str[i] to word
		if(str[i] != ',' && str[i] != '.' && str[i] != '!' && str[i] != '?' && str[i] != ' ')
		{
			word[j]=str[i];
			j++;
		}

		//else if str[i] is a space, separate the tokens by ending word with a null char and copying it to the string array
		if(str[i] == ' ')
		{
			word[j] = '\0';
			j=0;
			strcpy(strArr[k], word);
			strcpy(word, "");
			k++;
		}
		
		//if str[i] is a null character, terminate the loop and add the last word to the string array
		if(str[i] == '\0')
		{
			word[j] = '\0';
			j=0;
			strcpy(strArr[k], word);
			strcpy(word, "");
			strcpy(strArr[k+1], "");
			k=0;
			i+=1000;
		}
	}
}

/* InitializeDatabase function removes all content from the database
@param wordDatabase - address where the all data is stored
@return - N/A
Pre-condition: The function is called to initialize the database and to wipe the database of data
*/
void 
InitializeDatabase(int *entryCount, entry *wordDatabase)
	{
	int i, j;
	for (i = 0; i < DATABASE_SIZE; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//This sets the first index of the language and translation to a null byte, removing all contents of the string
			wordDatabase[i].pairs[j][0][0] = '\0';
			wordDatabase[i].pairs[j][1][0] = '\0';
		}
		wordDatabase[i].pairCount = 0;
	}

	*entryCount = 0;
}

/* DisplaySpecificEntries function displays entries inside of a word database
@param wordDatabase - serves as the source of data
@param FoundEntryArray - address where indexes of matched certain entries inside of the word database is stored
@param FoundEntryArrayElements - number of elements in the foundEntryArray
@return - N/A
Pre-condition: FoundEntryArray has valid indexes inside. FoundEntryArrayElements should match the number of elements in FoundEntryArray
*/
void 
DisplaySpecificEntries(entry *wordDatabase, int *FoundEntryArray, int FoundEntryArrayElements)
	{
	int i, j;
	//TBR: This does not display inta-entry nor inter-entry
	for (i = 0; i < FoundEntryArrayElements; i++)
	{
		printf("\nEntry No: [%d]\n", i+1);
		printf("------------------------------------------------\n");
		printf("%-25s | %20s\n", "Language", "Translation");
		printf("------------------------------------------------\n");

		for (j = 0; j < wordDatabase[FoundEntryArray[i]].pairCount; j++)
		{
			printf("%-20s [%02d] | ", wordDatabase[FoundEntryArray[i]].pairs[j][0], j+1);
			printf("%20s\n", wordDatabase[FoundEntryArray[i]].pairs[j][1]);
		}
		printf("------------------------------------------------\n");
	}
};

/* AddEntry function is responsible for handling requests to add entries into the word database
@param entryCount - integer value that represents the current number of entries inside wordDatabase
@param wordDatabase - serves as the source & destination of entries
@return - N/A
Pre-condition: wordDatabase must be properly initialized, entryCount should properly correspond to the current number of entries isnide of wordDatabase
*/
void 
AddEntry(int *entryCount, entry *wordDatabase)
{
	string20 translation,
			 word;
	int sentinel = 1;
	//TBR: Maybe this could be a struct
	int FoundEntryArray[DATABASE_SIZE];
	int FoundEntryArrayElements = 0;
	int decision;
	
	do 
	{
		FoundEntryArrayElements = 0;
		
		printf("Indicate desired language: ");
		inputString(translation, 20);
		
		printf("Indicate desired word: ");
		inputString(word, 20);
	
		if (SearchTranslation(word, translation, wordDatabase, entryCount, FoundEntryArray, &FoundEntryArrayElements))
		{
			printf("Displaying instances of language translation pair matches in current database \n");
			DisplaySpecificEntries(wordDatabase, FoundEntryArray, FoundEntryArrayElements);
			
			printf("Is this a new entry?[yes/no]\n");

			inputYesNo(&decision);
			
			if (decision)
			{
				if (*entryCount < DATABASE_SIZE){
					InputEntryData(word, translation, wordDatabase, entryCount, -1);
				
					printf("New entry successfully created\n");
					printf("\nDo you want to input another language translation pair?[yes/no]\n");

					inputYesNo(&decision);

					if (decision)
					{
						do 
						{
							printf("Indicate desired language: ");
							fgets(translation, sizeof(translation), stdin);
							RemoveNewline(translation);
							
							printf("Indicate desired word: ");
							fgets(word, sizeof(word), stdin);
							RemoveNewline(word);
							
							InputEntryData(word, translation, wordDatabase, entryCount, *entryCount-1);

							printf("Successfully added translation pair\n");

							printf("\nDo you want to input another language translation pair?[yes/no]\n");
							
							inputYesNo(&decision);
							
						} while (decision && wordDatabase[*entryCount-1].pairCount <= 9);
						sentinel = 0;
						if (wordDatabase[*entryCount-1].pairCount == 10){
							printf("Maximum capacity of entry reached\n");
						}
						printf("\nRedirecting to Manage Data Menu");
						ManageDataMenu(entryCount, wordDatabase);
					} else 
					{
						sentinel = 0;
						printf("\nRedirecting to Manage Data Menu\n");
						ManageDataMenu(entryCount, wordDatabase);
					}
				} else {
					printf("Word database already has the maximum number of entries\n");
					printf("Redirecting to Manage Data Menu\n");
					sentinel = 0;
				}
				
						
			} else 
			{
				sentinel = 0;
				printf("\nRedirecting to Manage Data Menu\n");
				ManageDataMenu(entryCount, wordDatabase);
			}
			
		} else 
		{
			printf("Word is not found in database\n");
			printf("Is this a new entry?[yes/no]\n");
			inputYesNo(&decision);
			
			if (decision)
			{
				if (*entryCount < DATABASE_SIZE){
					InputEntryData(word, translation, wordDatabase, entryCount, -1);
					printf("\nNew entry has been created\n");
					printf("\nDo you want to input another language translation pair?[yes/no]\n");
					inputYesNo(&decision);
					
					if (decision)
					{
						do 
						{
							printf("Indicate desired language: ");
							fgets(translation, sizeof(translation), stdin);
							RemoveNewline(translation);
							
							printf("Indicate desired word: ");
							fgets(word, sizeof(word), stdin);
							RemoveNewline(word);

							InputEntryData(word, translation, wordDatabase, entryCount, *entryCount-1);

							printf("Successfully added translation pair\n");

							
							printf("\nDo you want to input another language translation pair?[yes/no]\n");
							
							inputYesNo(&decision);
							
						} while (decision && wordDatabase[*entryCount-1].pairCount <= 9);
						sentinel = 0;
						if (wordDatabase[*entryCount-1].pairCount == 10){
							printf("Maximum capacity of entry reached\n");
						}
						printf("\nRedirecting to Manage Data Menu");
						ManageDataMenu(entryCount, wordDatabase);
					} else 
					{
						sentinel = 0;
						printf("\nRedirecting to Manage Data Menu\n");
						ManageDataMenu(entryCount, wordDatabase);
					}

				} else {
					printf("Word database already has the maximum number of entries\n");
					printf("Redirecting to Manage Data Menu\n");
					sentinel = 0;
				}

						
			} else 
			{
				sentinel = 0;
				printf("\nRedirecting to Manage Data Menu\n");
				ManageDataMenu(entryCount, wordDatabase);
			}
		}
	} while (sentinel == 1);
}

/* InputEntryData function is reponsible for creating new entries and adding translations to existing entries
@param word - the word that will be inserted into the word database
@param word - the language of the word that will be inserted into the word database
@param wordDatabase - serves as the destination of new entries and entry modifications
@param entryCount - corresponds to the number of entries inside of wordDatabase
@param mode - indicates what action the function will do
@return - N/A
*/
void 
InputEntryData(char *word, char *language, entry *wordDatabase, int *entryCount, int mode)
{
	//mode = -1 : to add a new entry
	//mode != -1 : to add a new translation to an existing entry
	if (mode == -1)
	{
		strcpy(wordDatabase[*entryCount].pairs[0][0], language);
		strcpy(wordDatabase[*entryCount].pairs[0][1], word);
		wordDatabase[*entryCount].pairCount = 1;
		*entryCount += 1;
	
	} else 
	{
		strcpy(wordDatabase[mode].pairs[wordDatabase[mode].pairCount][0], language);
		strcpy(wordDatabase[mode].pairs[wordDatabase[mode].pairCount][1], word);
		wordDatabase[mode].pairCount+=1;
		
	}
	
};

/* AddTranslations function is responsible for handling requests to add translations to existing entries in the wordDatabase
@param entryCount - integer value that represents the current number of entries inside wordDatabase
@param wordDatabase - serves as the source and destination of entries
@return - N/A
*/
void 
AddTranslations(int *entryCount, entry *wordDatabase)
{
	//To remove line below in the future
	string20 queryTranslation,
			 queryWord,
			 translation,
			 word;
	
	
	int confirmation;
	int sentinel = 1;
	//TBR: Maybe this could be a struct
	int FoundEntryArray[DATABASE_SIZE];
	int FoundEntryArrayElements = 0;
	int translationID;
	int decision;

	FoundEntryArrayElements = 0;
	printf("Indicate language to search: ");
	inputString(queryTranslation, 20);
	
	printf("Indicate word to search: ");
	inputString(queryWord, 20);

	if (SearchTranslation(queryWord, queryTranslation, wordDatabase, entryCount, FoundEntryArray, &FoundEntryArrayElements))
	{
		
		if (FoundEntryArrayElements > 1)
		{
			DisplaySpecificEntries(wordDatabase, FoundEntryArray, FoundEntryArrayElements);
			printf("Language - Translation pairs have been found\n");

			printf("Please indicate which entry receive additional translations[number]\n");
			printf("Input number of entry: ");
			scanf("%d", &translationID);


			if (wordDatabase[FoundEntryArray[translationID-1]].pairCount == 10)
			{
				printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
				ManageDataMenu(entryCount, wordDatabase);
			} else 
			{
				while (sentinel == 1)
				{
					clearInputBuffer();
					printf("Indicate language to be added: ");
					inputString(translation, 20);
				
					printf("Indicate word translation to be added: ");
					inputString(word, 20);
					
					InputEntryData(word, translation, wordDatabase, entryCount, FoundEntryArray[translationID-1]);
	
					printf("Successfully added to entry\n");
	
					if (wordDatabase[FoundEntryArray[0]].pairCount == 10)
					{
						printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
						sentinel = 0;
						printf("Redirecting to Manage Data Menu\n");
						ManageDataMenu(entryCount, wordDatabase);
					} else 
					{
					printf("Would you like to add more translations to the same entry? [yes/no]\n");
					inputYesNo(&decision);
	
						if (!decision)
						{
							sentinel = 0;
							printf("\nRedirecting to Manage Data Menu\n");
							ManageDataMenu(entryCount, wordDatabase);
						}
					}
					
				}
			}
			
		} else if (FoundEntryArrayElements == 1)
		{
			DisplaySpecificEntries(wordDatabase, FoundEntryArray, FoundEntryArrayElements);
			printf("A Language - Translation pair has been found\n");

			if (wordDatabase[FoundEntryArray[0]].pairCount == 10)
			{
				printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
				ManageDataMenu(entryCount, wordDatabase);
			} else 
			{
				while (sentinel == 1)
				{
					printf("Indicate language to be added: ");
					inputString(translation, 20);

					printf("Indicate word translation to be added: ");
					inputString(word, 20);
					
					InputEntryData(word, translation, wordDatabase, entryCount, FoundEntryArray[0]);
	
					printf("Successfully added to entry\n");
	
					if (wordDatabase[FoundEntryArray[0]].pairCount == 10)
					{
						printf("[Entry Capacity Reached] No additional translation pairs can be added to this entry\n");
						sentinel = 0;
						printf("Redirecting to Manage Data Menu\n");
						ManageDataMenu(entryCount, wordDatabase);
					}else 
					{
					printf("Would you like to add more translations to the same entry? [yes/no]\n");
					inputYesNo(&decision);
	
						if (!decision)
						{
							sentinel = 0;
							printf("\nRedirecting to Manage Data Menu\n");
							ManageDataMenu(entryCount, wordDatabase);
						}
					}
				}
			}
			
		}
		
	} else 
	{
		printf("Word is not found\n");
		printf("Please return to the Manage Data menu and use the Add Entry option\n");
	
		while (confirmation != 1)
		{
			printf("Input 1 if understood\n");
			scanf("%d", &confirmation);
			
			if (confirmation == 1)
			{
				ManageDataMenu(entryCount, wordDatabase);
			} else 
			{
				printf("Unrecognized command, please re-input\n");
			}
		}
		
	}
}

/* DeleteEntry function is responsible for handling entry deletion requests
@param entryCount - integer value that represents the current number of entries inside wordDatabase
@param wordDatabase - serves as the data source to be modified
@return - N/A
Pre-condition: 
*/
void 
DeleteEntry(int *entryCount, entry *wordDatabase)
{
	int deleteID, i, j;

	DisplayAllEntries(entryCount, wordDatabase, -1);

	if (*entryCount != 0)
	{
		printf("Which entry would you like to delete [number]? ");
		scanf("%d", &deleteID);

		if (deleteID >= 1 && deleteID <= *entryCount)
		{
			for (i = 0; i < wordDatabase[deleteID-1].pairCount; i++)
			{
				for (j = 0; j < 2; j++)
				{
					strcpy(wordDatabase[deleteID-1].pairs[i][j], "");
				}
			}
			wordDatabase[deleteID-1].pairCount = 0;
			*entryCount -=1;
			printf("Successfully deleted\n");
			ManageDataMenu(entryCount, wordDatabase);
		} else 
		{
			printf("Input has been incorrect, redirecting to Manage Data Menu\n");
			ManageDataMenu(entryCount, wordDatabase);
		}
		getchar();
	} else 
	{
		ManageDataMenu(entryCount, wordDatabase);
	}
	
}

/* DeleteTranslation function is responsible for handing translation deletion requests
@param entryCount - integer value that represents the current number of entries inside wordDatabase
@param wordDatabase - serves as the data source to be modified
@return - N/A
Pre-condition: 
*/
void 
DeleteTranslation(int *entryCount, entry *wordDatabase)
{
    int i, entryID, translationID, sentinel = 1;
	char response;

	DisplayAllEntries(entryCount, wordDatabase, -1);

	if (*entryCount != 0)
	{
		printf("From which entry would you like to delete a language-translation pair?\n");

		scanf("%d", &entryID);

		if (entryID >= 1 && entryID <= *entryCount)
		{
			do
			{
				printf("What language-translation pair would you want to be deleted? [Number]\n");
				printf("Input [-1] to stop deletion\n");
				scanf("%d", &translationID);

				if (translationID >= 1 && translationID <= wordDatabase[entryID-1].pairCount)
				{

					for (i = translationID; i < wordDatabase[entryID-1].pairCount; i++)
					{
						strcpy(wordDatabase[entryID - 1].pairs[i - 1][0], wordDatabase[entryID - 1].pairs[i][0]);
						strcpy(wordDatabase[entryID - 1].pairs[i - 1][1], wordDatabase[entryID - 1].pairs[i][1]);
					}
					strcpy(wordDatabase[entryID - 1].pairs[wordDatabase[entryID - 1].pairCount - 1][0], "");
					strcpy(wordDatabase[entryID - 1].pairs[wordDatabase[entryID - 1].pairCount - 1][1], "");

					wordDatabase[entryID - 1].pairCount -= 1;

					if (wordDatabase[entryID-1].pairCount == 0)
					{
						*entryCount -= 1;
						printf("Successfully deleted language-translation pair\n");
						printf("Entry has been deleted completely\n");
						printf("\necting to Manage Data Menu\n");
						sentinel = 0;
						SortDatabase(*entryCount, wordDatabase);
						ManageDataMenu(entryCount, wordDatabase);
					} else 
					{
						SortDatabase(*entryCount, wordDatabase);
						printf("Successfully deleted language-translation pair\n");
					}

					

				} else if (translationID == -1)
				{
					printf("\nRedirecting to Manage Data Menu\n");
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else 
				{
					//not accounting for already 0 language-translation pairs in entry
					printf("Invalid translation-pair ID given. Would you like to retry?[y/n] \n");
					scanf(" %c", &response);

					if (response != 'y')
					{
						printf("\nRedirecting to Manage Data Menu\n");
						sentinel = 0;
						ManageDataMenu(entryCount, wordDatabase);
					}
				}

			} while (sentinel);
		} else 
		{
			printf("Input has been incorrect, redirecting to Manage Data Menu\n");
			ManageDataMenu(entryCount, wordDatabase);
		}
	} else 
	{
		ManageDataMenu(entryCount, wordDatabase);
	}

	

}

/* DisplayAllEntries function is responsible for displaying all entries inside of the wordDatabase
@param entryCount - integer value that represents the current number of entries inside wordDatabase
@param wordDatabase - serves as the data source
@param mode - this integer value will indicate if the function will return to ManageDataMenu function or not
@return - N/A
Pre-condition:
*/
void 
DisplayAllEntries(int *entryCount, entry *wordDatabase, int mode)
{
	//mode = 1 would return to ManageDataMenu()
	//mode = -1 would be for delete entry/delete translation
	int i = 0, j, sentinel = 1;
	
	int validInput;
	char response;

    SortDatabase(*entryCount, wordDatabase);

	if (*entryCount == 0)
	{
		printf("Database currently has no entries\n");
		printf("\nRedirecting to Manage Data menu\n\n");
	} else 
	{
		do
		{
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");
			//TBR: This could be a separate function
			for (j = 0; j < wordDatabase[i].pairCount; j++)
			{
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
			
			do 
			{
				printf("Enter your choice: ");
				scanf(" %c", &response);
	
				if (response == 'X')
				{
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
				} else if (response == 'N' && i < *entryCount -1)
				{
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0)
				{
					i--;
					validInput = 1;
				} else 
				{
					printf("Invalid input or out of bounds\n");
				}
				getchar();
			} while (!validInput);
	
		} while (sentinel);
	
	}

	if (mode > 0)
	{
		ManageDataMenu(entryCount, wordDatabase);
	}
	
	
}

/* SearchWord_With_Display function is responsible to display entries in the wordDatabase with specific words
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition: 
*/
void 
SearchWord_With_Display(int *entryCount, entry *wordDatabase)
{
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
	inputString(searchingWord, 20);

	//must search for the word

	for (i = 0; i < *entryCount; i++){
		foundWord = 0;
		for (j = 0; j < wordDatabase[i].pairCount && foundWord == 0; j++)
		{
			if (strcmp(wordDatabase[i].pairs[j][1], searchingWord) == 0)
			{
				copiesArray[foundCopies] = i;
				foundCopies += 1;
				foundWord = 1;
			}
		}
	}




	if (foundCopies > 0)
	{
		i = 0;
		do 
		{
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//TBR: This could be a separate function
			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase

			for (j = 0; j < wordDatabase[copiesArray[i]].pairCount; j++)
			{
				for (k = 0; k < 2; k++)
				{
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
			
			do 
			{
				printf("Enter your choice: ");
				scanf("%c", &response);

				if (response == 'X')
				{
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else if (response == 'N' && i < *entryCount -1)
				{
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0)
				{
					i--;
					validInput = 1;
				} else 
				{
					printf("Invalid input or out of bounds\n");
				}
				getchar();
			} while (!validInput);

		} while (sentinel);

	} else 
	{
		printf("There are no word matches in the database\n");
		printf("\nRedirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
	
}

/* SearchTranslation_With_Display function is responsible to display entries in wordDatabase with specific language-translation pairs
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
*/
void 
SearchTranslation_With_Display(int *entryCount, entry *wordDatabase)
{
	SortDatabase(*entryCount, wordDatabase);
	int i = 0, j, sentinel = 1;
	
	string20 searchingWord;
	string20 searchingTranslation;

	int validInput;
	int foundCopies = 0;

	int foundWord;
	int copiesArray[DATABASE_SIZE];

	char response;


	printf("Input the translation you want to search in the database: ");
	//TBR: Must check for incorrect input
	inputString(searchingTranslation, 20);
	printf("Input the word you want to search in the database: ");
	inputString(searchingWord, 20);

	//must search for translation-word pair
	for (i = 0; i < *entryCount; i++)
	{
		foundWord = 0;
		for (j = 0; j < wordDatabase[i].pairCount && foundWord == 0; j++)
		{
			if (strcmp(wordDatabase[i].pairs[j][0], searchingTranslation) == 0 && strcmp(wordDatabase[i].pairs[j][1], searchingWord) == 0)
			{
				copiesArray[foundCopies] = i;
				foundCopies += 1;
				foundWord = 1;
			}
		}
	}
	



	if (foundCopies > 0)
	{
		i = 0;
		do 
		{
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//TBR: This could be a separate function
			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase

			for (j = 0; j < wordDatabase[copiesArray[i]].pairCount; j++)
			{
				printf("%-20s [%02d] | ", wordDatabase[copiesArray[i]].pairs[j][0], j+1);
				printf("%20s\n", wordDatabase[copiesArray[i]].pairs[j][1]);
			}
			printf("------------------------------------------------\n");
			printf("Press 'X' to end the display\n");
			if (i < foundCopies - 1)
				printf("Press 'N' to view the next entry\n");
			if (i > 0)
				printf("Press 'P' to view the previous entry\n");

			validInput = 0;
			
			do {
				printf("Enter your choice: ");
				scanf("%c", &response);

				if (response == 'X')
				{
					printf("Ending the display\n");
					validInput = 1;
					sentinel = 0;
					ManageDataMenu(entryCount, wordDatabase);
				} else if (response == 'N' && i < *entryCount -1)
				{
					i++;
					validInput = 1;
				} else if (response == 'P' && i > 0)
				{
					i--;
					validInput = 1;
				} else 
				{
					printf("Invalid input or out of bounds\n");
				}
				getchar();
			} while (!validInput);

		} while (sentinel);

	} else 
	{
		printf("There are no word matches in the database\n");
		printf("\nRedirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
}

/* SearchTranslation function is responsbile to search through the word database and record indexes where the language-translation pair is found
@param word - string that represents the translation from the language-translation pair
@param language - string that represents the language from the language-translation pair
@param wordDatabse - address that serves as the data source
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param FoundEntryArray - address that stores the indexes where the language-translation pair is found
@param FoundEntryArrayElements - integer value that represents the current number of elements in FoundEntryArray
@return - function returns 0[not found] or 1[found], indicating if the language-translation pair was found in wordDatabase
Pre-condition: 
*/
int 
SearchTranslation(char *word, char *language, entry *wordDatabase, int *entryCount, int *FoundEntryArray, int *FoundEntryArrayElements)
{
	int i, j, found = 0;
	int displayIndex = 0;
	
	for (i = 0; i < *entryCount; i++)
	{
		for (j = 0; j < wordDatabase[i].pairCount; j++)
		{
			if (strcmp(wordDatabase[i].pairs[j][0], language) == 0 && strcmp(wordDatabase[i].pairs[j][1], word) == 0)
			{
				found = 1; 
				FoundEntryArray[displayIndex] = i;
				*FoundEntryArrayElements += 1;
				displayIndex += 1;
			}
		}
	}
	
	return found;
}

/* Export function is responsible for exporting the current database contents into a text file following a proper format
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition: 
*/
void 
Export(int *entryCount, entry *wordDatabase)
{
	int i, j;
	FILE* fPtr;
	string30 filename;
	string20 language, translation;

	printf("Indicate file name of text file: [include .txt]");
	//TBR: need to verify correct input
	inputString(filename, 30);
	

	fPtr = fopen(filename, "w");

	for (i = 0; i < *entryCount; i++)
	{
		for (j = 0; j < wordDatabase[i].pairCount; j++)
		{
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

/* Import function is responsible for importing data from a text file that follows prescribed format
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@param condition -
@return - N/A
Pre-condition:
*/
void 
Import(int *entryCount, entry *wordDatabase, int condition)
{
	int i, j, response;
	FILE* fPtr;
	string30 filename;
	
	char perLineText[43];
	

	string20 tempLanguage, tempTranslation;
	entry tempEntryDB[DATABASE_SIZE];
	int tempEntryCount = 0, colonIndex;

	int line = 0, dataAdded = 0, decision = 1;

	InitializeDatabase(&tempEntryCount, tempEntryDB);
	
	printf("Indicate file to import data from: [Include .txt]");
	inputString(filename, 30);

	fPtr = fopen(filename, "r");

	if (fPtr != NULL)
	{
		//need to only fill 150
		while (fgets(perLineText, 43, fPtr))
		{
			//printf("%s", perLineText);

			//gets index of the colon in perlinetext
			//need to check if 10
			if (strcmp(perLineText, "\n") != 0)
			{
				colonIndex = -1;
				for (i = 0; i < strlen(perLineText) && colonIndex == -1; i++)
				{
					if (perLineText[i] == ':')
					{
						colonIndex = i;
					}
				}
				//this gets the temporary language
				strncpy(tempLanguage, perLineText, colonIndex);
				tempLanguage[colonIndex] = '\0';
				toLowerCase(tempLanguage);
				
				//this gets the temporary Translation
				strcpy(tempTranslation, &perLineText[colonIndex+2]);
				RemoveNewline(tempTranslation);
				toLowerCase(tempTranslation);
				// we could replace this with input entry data function
		
				strcpy(tempEntryDB[tempEntryCount].pairs[line][0], tempLanguage);
				strcpy(tempEntryDB[tempEntryCount].pairs[line][1], tempTranslation);
				tempEntryDB[tempEntryCount].pairCount += 1;
				//printf("TempLanugage is: %s", tempLanguage);
				//printf("TempTranslaiton is: %s", tempTranslation);

				
				line+= 1;
				//could just set this to one
				dataAdded += 1;
			} else if (dataAdded > 0)
			{
				//tempEntryDB[tempEntryCount].pairCount = line;
				//printf("Insertion // TempEntryCount: %d", tempEntryCount);
				line = 0;
				tempEntryCount += 1;
				
			} 

		}

		if (dataAdded > 0)
		{
			tempEntryCount += 1;
		}
		
		
		for (i = 0; i < tempEntryCount; i++)
		{
			printf("\nEntry No: [%d]\n", i+1);
			printf("------------------------------------------------\n");
			printf("%-25s | %20s\n", "Language", "Translation");
			printf("------------------------------------------------\n");

			//copiesArray[i] would be the index of the found in wordDatabase
			
			//this should access the number of pairs inside of the current index in wordDatabase
			for (j = 0; j < tempEntryDB[i].pairCount; j++)
			{
				printf("%-20s [%02d] | ", tempEntryDB[i].pairs[j][0], j+1);
				printf("%20s\n", tempEntryDB[i].pairs[j][1]);
				
			}

			printf("------------------------------------------------\n");

			printf("Would you like to add this entry to the Database?[yes,no]\n");
			
			inputYesNo(&response);
			if (response == 1)
			{
				//need to check if wordDatabase is full
				//input this sole entry into the mainDB
				for (j = 0; j < tempEntryDB[i].pairCount; j++){
					strcpy(wordDatabase[*entryCount].pairs[j][0], tempEntryDB[i].pairs[j][0]);
					strcpy(wordDatabase[*entryCount].pairs[j][1], tempEntryDB[i].pairs[j][1]);
					wordDatabase[*entryCount].pairCount += 1;
				}
				*entryCount += 1;
				printf("Successfully imported data into Word Database\n");
			} else if (response == 0)
			{
				//need to differ response when there are no more entries to add
				printf("Viewing next entry in source file\n");
			} //else 
		
		
		}
		
		SortDatabase(*entryCount, wordDatabase);
		if (condition)
		{
			ManageDataMenu(entryCount, wordDatabase);
		}
			
		
	} 
	else if(condition)
	{
		printf("File cannot be retrieved, redirecting to Manage Data menu\n");
		ManageDataMenu(entryCount, wordDatabase);
	}
	else 
	{
		while(decision)
		{
			printf("File cannot be retrieved, do you want to retry? (yes/no)\n");
			inputYesNo(&decision);

			if(decision)
				Import(entryCount, wordDatabase, condition);
			else
			{
				printf("\nRedirecting back to Main Menu");
				MainMenu(entryCount, wordDatabase);
			}
		}
	}
}


void 
translate(string150 text, string20 srcLanguage, string20 finLanguage, string150* strArr, int *entryCount, entry *wordDatabase)
{
	int i, j, k, l;
	
	tokenizeString(text, strArr); //text is text to be translated, strArr is array of words
	//for each word sa word array, search translation then translate word if found
	//if word exists in database
	//if final language exists in the first instance
	//replace word with translation

	for(i=0; strcmp(strArr[i],"") != 0; i++) //while strArr is not a null string
	{
		for(j=0; j<*entryCount; j++) //loop through all entries
		{
			for(k=0; k<wordDatabase[j].pairCount; k++) //for the jth wordDatabase, loop through all pairs
			{
				//this checks if the original language is in the database
				if(strcmp(strArr[i], wordDatabase[j].pairs[k][1]) == 0 && strcmp(srcLanguage, wordDatabase[j].pairs[k][0]) == 0)
				{
					//this checks if the output language is in the database
					for(l=0; l<wordDatabase[j].pairCount; l++)
					{
						if(strcmp(finLanguage, wordDatabase[j].pairs[l][0]) == 0)
						{
							strcpy(strArr[i], wordDatabase[j].pairs[l][1]);
							
						}
							
					}
					
				}
			}
		}
	}

}

void 
TranslateTextInput(int *entryCount, entry *wordDatabase)
{
	
	string20 srcLanguage; //source language
	string20 finLanguage; //final language
	string150 text;       //text to be translated
	string150 strArr[75]; //word array after tokenize
	int i, condition = 0;

	printf("Indicate the language of the source text: ");
	inputString(srcLanguage, 30);
	
	printf("Indicate the language to be translated to: ");
	inputString(finLanguage, 30);

	do
	{
		printf("Indicate the text to be translated:\n");
		inputString(text, 150);
		translate(text, srcLanguage, finLanguage, strArr, entryCount, wordDatabase);

		printf("\nTranslation:\n");
		for(i=0; strcmp(strArr[i], ""); i++)
		{
			printf("%s ", strArr[i]);
		}

		printf("\n\nDo you want to translate again with the same source and output language? [yes/no]\n");
		inputYesNo(&condition);
	} while (condition);

	
}

void 
TranslateTextFile(int *entryCount, entry *wordDatabase)
{
	//
	string20 srcLanguage; //source language
	string20 srcFileName; //source FileName
	string20 outLanguage; //output language
	string20 outFileName; //output fileName
	string150 sentence;
	string150 strArr[75];
	FILE* fPtrSource = NULL;
	FILE* fPtrOutput;
	int decision = 1, i, toStop = 0;
	char sym;

	printf("Indicate the language of your source file: ");
	inputString(srcLanguage, 20);

	while(fPtrSource == NULL && !toStop)
	{
		printf("Indicate the filename of your source file: [include .txt] ");
		inputString(srcFileName, 30);

		fPtrSource = fopen(srcFileName, "r");

		if (fPtrSource != NULL){ 
			printf("Indicate the language to be translated to: ");
			inputString(outLanguage, 20);

			printf("Indicate the filename of your output file: [include .txt] ");
			inputString(outFileName, 30);

			fPtrOutput = fopen(outFileName, "w");
			
			printf("-----------Start of Translation-----------\n");
			while ((sym = fgetc(fPtrSource)) != EOF)
			{
				if(!(sym == '.' || sym == '!' || sym == '?'))
				{
					if(!(i==0 && sym == ' ') && sym != '\n')
					{
						sentence[i] = sym;
						i++;
					}
				}
				else
				{
					sentence[i] = '\0';
					translate(sentence, srcLanguage, outLanguage, strArr, entryCount, wordDatabase);

					
					for(i=0; strcmp(strArr[i], ""); i++)
					{
						if(strcmp(strArr[i+1], ""))
						{
							printf("%s ", strArr[i]);
							fprintf(fPtrOutput, "%s ", strArr[i]);
						}
						else
						{
							printf("%s", strArr[i]);
							fprintf(fPtrOutput, "%s", strArr[i]);
						}
					}
					printf("%c", sym);
					printf("\n");
					fprintf(fPtrOutput, "%c", sym);
					fprintf(fPtrOutput, "\n");
					
					//write sa file here

					strcpy(sentence, "");
					i=0;
				}
			}
			printf("-------------End of Translation-----------\n");
			fclose(fPtrSource);
			fclose(fPtrOutput);
		}
		else 
		{
			while(decision)
			{
				printf("File cannot be retrieved, do you want to retry? (yes/no)\n");
				inputYesNo(&decision);

				if(!decision)
				{
					toStop = 1;
					printf("\nRedirecting to Translate Menu\n");
					TranslateMenu(entryCount, wordDatabase);
				}
			}
		}
	}
	
}

/* ManageDataMenu function is responsible for displaying the Manage Data menu & handling operations within the menu
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition:
*/
void 
ManageDataMenu(int *entryCount, entry *wordDatabase)
{
	
	int action;
	
	printf("\nMANAGE DATA MENU\n");
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
	
	action = intInput(0,9);
	
	switch (action)
	{
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
    		Import(entryCount, wordDatabase, 1);
    		break;
    	default:
			InitializeDatabase(entryCount, wordDatabase);
    		MainMenu(entryCount, wordDatabase);
    		break;
	}

}

/* TranslateMenu function is responsible for displaying the Translate menu & handing operations within the menu
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition:
*/
void 
TranslateMenu(int *entryCount, entry* wordDatabase)
{
	Import(entryCount, wordDatabase, 0);
	int action = 1;
	
	while(action)
	{
		printf("TRANSLATE MENU\n");
		printf("[1] -> Translate Text Input\n");
		printf("[2] -> Translate Text File\n");
		printf("[0] -> Exit Menu\n");
		
		action = intInput(0,2);
		switch (action)
		{
			case 1:
				TranslateTextInput(entryCount, wordDatabase);
				break;
			case 2: 
				TranslateTextFile(entryCount, wordDatabase);
				break;
			default:
				InitializeDatabase(entryCount, wordDatabase);
				MainMenu(entryCount, wordDatabase);
				break;
		}	
	}
}


/* SortDatabase function is responsible for sorting the current word database inter-entry and intra-entry
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition: 
*/
void 
SortDatabase(int entryCount, entry *wordDatabase)
{
	int i = 0, j, k, l, englishDbIndex = 0, nonEnglishDbIndex = 0, containsEnglish;
	int englishWordIndex1, englishWordIndex2;
	int successfulInsertions = 0;

	
	entry nonEnglishDatabase[DATABASE_SIZE], englishDatabase[DATABASE_SIZE];


	//Looping 1 - This should place entries with english entries to englishDatabase and entries with no english entries into the nonEnglishDatabase

	//goes through each entry in the database
	if (entryCount > 0)
	{
		while (successfulInsertions != entryCount)
		{
			//checks if any of the pairs in the entry contain english
			containsEnglish = 0;
			for (j = 0; j < wordDatabase[i].pairCount && containsEnglish == 0 && wordDatabase[i].pairCount > 0; j++)
			{	
				//printf("wordDatabase paircount = %d\n", wordDatabase[i].pairCount);	
				if (strcmp(wordDatabase[i].pairs[j][0], "english") == 0)
				{
					// copies all elements inside of the entry
					englishDatabase[englishDbIndex].pairCount = 0;
	
					for (k = 0; k < wordDatabase[i].pairCount; k++)
					{
						for (l = 0; l < 2; l++)
						{
							strcpy(englishDatabase[englishDbIndex].pairs[k][l], wordDatabase[i].pairs[k][l]);
						}
						
						englishDatabase[englishDbIndex].pairCount += 1;
					}
			
					containsEnglish = 1;
					englishDbIndex += 1;
					successfulInsertions += 1;
	
				} 
			}
	
			if (containsEnglish == 0 && wordDatabase[i].pairCount > 0)
			{
				nonEnglishDatabase[nonEnglishDbIndex].pairCount = 0;
				for (k = 0; k < wordDatabase[i].pairCount; k++)
				{
					for (l = 0; l < 2; l++)
					{
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
	
		for (i = 0; i < englishDbIndex - 1; i++)
		{
			for (j = 0; j < englishDbIndex - 1 - i; j++)
			{
				//Need to find the english word and compare with the next english word of index j, implement normal swappinng
				englishWordIndex1 = -1;
				englishWordIndex2 = -1;
				for (k = 0; k < englishDatabase[j].pairCount && englishWordIndex1 == -1; k++)
				{
					if (strcmp(englishDatabase[j].pairs[k][0], "english") == 0)
						englishWordIndex1 = k;
				}
	
				for (k = 0; k < englishDatabase[j+1].pairCount && englishWordIndex2 == -1; k++)
				{
					if (strcmp(englishDatabase[j+1].pairs[k][0], "english") == 0)
						englishWordIndex2 = k;
				}
				
				if (strcmp(englishDatabase[j].pairs[englishWordIndex1][1], englishDatabase[j+1].pairs[englishWordIndex2][1]) > 0)
				{
					swapEntries(&englishDatabase[j], &englishDatabase[j+1]);
				}
	
				
	
			}
		}
	
		//Sort intra-entry by alphabetical order [English]
	
		for (i = 0; i < englishDbIndex; i++) 
		{
			// Perform bubble sort on the pairs of each entry
			for (j = 0; j < englishDatabase[i].pairCount - 1; j++) 
			{
				for (k = 0; k < englishDatabase[i].pairCount - 1 - j; k++) 
				{
					// Compare the languages (pairs[k][0] with pairs[k+1][0])
		
					if (strcmp(englishDatabase[i].pairs[k][0], englishDatabase[i].pairs[k+1][0]) > 0) 
					{
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
	
		for (i = 0; i < entryCount; i++)
		{
			if (i < englishDbIndex)
			{
				for (j = 0; j < englishDatabase[i].pairCount; j++)
				{
					for (k = 0; k < 2; k++)
					{
						strcpy((wordDatabase+i)->pairs[j][k], englishDatabase[i].pairs[j][k]);
					}
				}
				(wordDatabase+i)->pairCount = englishDatabase[i].pairCount;
			} else 
			{
				l = i - englishDbIndex;
				for (j = 0; j < nonEnglishDatabase[l].pairCount; j++)
				{
					for (k = 0; k < 2; k++)
					{
						strcpy((wordDatabase+i)->pairs[j][k], nonEnglishDatabase[l].pairs[j][k]);
					}
				}
				(wordDatabase+i)->pairCount = nonEnglishDatabase[l].pairCount;
				
			}
		}
	}

}

/* swapEntries function is responsible for swapping two entries
@param entry1 - address that contains the data of an entry
@param entry2 - address that contains the data of an entry
@return - N/A
Pre-condition: 
*/
void 
swapEntries(entry *entry1, entry *entry2) 
{
    entry tempEntry;

	tempEntry = *entry1;
	*entry1 = *entry2;
	*entry2 = tempEntry;
    
}

/* MainMenu function is responsible for displaying the main menu options & handing the operations within the menu
@param entryCount - integer value that represents the current number of entries inside of wordDatabase
@param wordDatabase - address that serves as the data source
@return - N/A
Pre-condition:
*/
void 
MainMenu(int *entryCount, entry *wordDatabase)
{

	int action;
    
    printf("---------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t\t|\n");
    printf("|\t\tCCPROG2 Machine Project\t\t\t|\n");
    printf("|\t\t   Simple Translator\t\t\t|\n");
   	printf("|\tCreated By: Nathan Dolot & Franz Magbitang\t|\n");
 	printf("|\t\t\t\t\t\t\t|\n");
 	printf("---------------------------------------------------------\n");
 
    printf("[1] -> Manage Data\n");
    printf("[2] -> Translation Panel\n");
    printf("[0] -> Exit Program\n");
    
    action = intInput(0,2);
    
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

int 
main()
{
	int entryCount = 0;
	
	entry wordDatabase[DATABASE_SIZE];	
	InitializeDatabase(&entryCount, wordDatabase);
    MainMenu(&entryCount, wordDatabase);
    
    return 0;
}
