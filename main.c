#include <stdio.h>
#include <stdlib.h>

/*
translation and language pair must be at most 20 letters each
10 pairs of language and translation per entry
there must be a count of pairs in entry

at most, 150 words


*/
void AddEntry(){
    /*
    Asks language and translation pair
    
    */
}

void AddTranslations(){

}

void DeleteEntry(){

}

void DeleteTranslation(){
    
}

void DisplayAllEntries(){
    
}

void SearchWord(){

}

void SearchTranslation(){

}

void Export(){

}

void Import(){
}

void TranslateTextInput(){

}

void TranslateTextFile(){

}

void ManageDataMenu(){
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
    		// AddEntry();
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
    		MainMenu();
    		break;
	}

}

void TranslateMenu(){
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
    		MainMenu();
    		break;
	}	
}

void MainMenu(){
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
    	case 0: 
    		ManageDataMenu();
    		break;
    	case 1:
    		TranslateMenu();
    		break;
    	default:
    		printf("Thank you for using our program!");
    		break;
	}
}

int main(){
	
    MainMenu();
    
    

    return 0;
}
