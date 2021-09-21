#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <errno.h>
//these are libraries which I used in my code..
#define Att 5
// Att is constant variable which defines number of user's attempts..
typedef struct listOfWords{
	struct listitem *next;	
	char* data;				
} wordList;
/* This struct is used for list words which gets from 
file by the chosem length that is defined by user. Char* data is string 
(one word in list)..
*/
int getDifficulty(){
	int choice, length;
	char* s;
	s="\n\tEnter length of word ";
	printf("\n\tSelect Difficulty:\n");
	printf("\t1)Easy (3-7)\n\t2)Medium (8-11)\n\t3)Hard (12-14)\n\n\t");
	scanf("%d", &choice);
	if(choice==1){
		printf("%s between 3 and 7 (inclusive): ", s);
	}else if(choice==2){
		printf("%s between 8 and 11 (inclusive): ", s);
	}else if(choice==3){
		printf("%s between 12 and 14 (inclusive): ", s);
	}
	scanf("%d", &length);
	return length;
}
/* This function returns length of random word. First this function
is called in main there are some printf statements which is for 
understanding for users..
*/
int checkLetter(char* word, char letter){
	int i=0;
	while(word[i]!='\0'){
		if(word[i]==letter) return 1;
	    i++;
	}
	return 0;
}
/* This function is boolean logic. So, variable letter is char, 
and function gets two parameters letter(char) and word(string)
and returns 1 if there is at least 1 char which has value same
with letter in word..
*/
void findLetter(char letter, char* word, char* guess){
	int i=0;
	while(word[i]!='\0'){
		if(word[i]==letter) guess[i]=letter;
	   i++;
	}
	return ;
}
/*This function is void, but gets 3 parameters: letter(char), word(char*), 
guess(char*). This function depends on result of "checkLetter) function.
So, if result of checkLetter function is 1, then this function called.
And in the result, guess string replace characters with this letter in everywhere..
*/
int checkGuess(char* guess, char* word){
    int i=0;
	while(word[i]!='\0'){
		if(guess[i]!=word[i]) return 0;
		i++;
	}
	return 1;
}
/* This function is so important, in all attempts this function has to be
called. If user's guess equal to word which user is looking for, then program
would stop and no need for new attempts. This is useful for last guess as well.. 
*/
int getLength(char* str){
	int i=0;
	while(str[i]!='\0'){
		i++;
	}
	return i;
}
// This is for getting length of any string
int getLengthOFList(wordList *listt){
	int i=0;
	while(listt->next!=NULL){
		i++;
		listt=(wordList*)listt->next;
		
	}
	return i+1;
}
//This is for getting number of elements in list
void getRandomWord(wordList *temp, char* word){
	int x;
	srand(time(0));
	x=rand()%getLengthOFList(temp);
	while(x>0){
		temp=(wordList*)temp->next;
		x--;
	}
	strcpy(word,temp->data);
	}
/* This function is used for getting random word with length
which was defined by user. And we call getLengthOfList function here,
because program has to know how many words in the file with this length..
*/	
FILE* chooseLanguage(){
	FILE* fp;
	char *lang;
	int choice;
	printf("\t\t\tHANGMAN\t\t\t\n\n\n");
	printf("\tChoose language:\n");
	printf("\t1)English\n\t2)Azerbaijani\n");
	printf("\t3)Turkish\n\t4)Russian\n\t5)Hungarian\n\n\t");
	scanf("%d", &choice);
    printf("\n\t");
    if(choice==1)
	lang="english.txt";
	else if(choice==2)
    lang="azerbaijani.txt";
    else if(choice==3)
    lang="turkish.txt";
    else if(choice==4)
    lang="russian.txt";
    else if(choice==5)
    lang="hungarian.txt";
    errno = 0;
    fp=fopen(lang, "r");
    if ( errno != 0 )
    {
        perror("Error occurred while opening file.\n");
        exit(1);
    }
   return fp;
}
/* This function is for extra task. Clearly, In folder there are
5 different files which are consist of words in different language.
And this function asks user for choosing language and returns pointer 
which type is (*FILE) and points to file which are words in chosen language..
*/
int main(){
	FILE* fp=(FILE*)chooseLanguage();   
	/* first call this function for getting fp pointer which 
	point to file in chosen language..
	*/
   wordList *head, *temp; //head is begining of list 
   head=NULL;
   int length=getDifficulty(); //length is defined by user in this function
   int attempt=Att; //this is number of attemps
   char c[16]; //it is for reading words from file
   while ( fscanf ( fp , "%s", c ) != EOF){
    if(getLength(c)==length){
    temp=(wordList*)malloc(sizeof(wordList));
	temp->data=(char*)malloc(sizeof(char)*16);
    strncpy(temp->data,c,16*sizeof(char));
    temp->next=head;
	head=temp;
	/*In this while I allocate memory for each item of list,
	and item of list is also pointer because it is string.
	I allocate memory for each item as well.
	*/
}
} 
	temp=head;
	char *word;
	word=(char*)malloc(length*sizeof(char));
	int g=getLengthOFList(temp);
	getRandomWord(temp,word);// for getting random word
	char guess[length+1];
	int i=0;
   while(i<length){
    	guess[i]='#';
	    i++;
	}/*before any attempt user's guess nothing, and 
	all chars initiliazed by this character
	*/
	guess[length]='\0'; // terminator for array
	i=0;
	char ch;
	while(attempt>0){ // this is main loop for proccess every attemps
		printf("\n\tYou have %d attempts!!\n\tEnter letter: ", attempt);
		scanf(" %c", &ch); //this is user's guess
		if(checkLetter(word, ch)) 
		//if there is this letter, then result is 1, or 0
		{	findLetter(ch, word, guess);}
		else {
			printf("\n\tThis letter was not found in the word!! ");
			
		}
			// if result is 1 add this letter to user's guess
			printf("\n\t%s\n", guess);
      
      	if(checkGuess(guess,word)) {
      		/*after every attempts program has to check whether user 
			find word completely or not
			*/attempt=-1;
            printf("\n\tCongrats!!\n");
		break;
	}
	attempt--;
}   
/* When all attempts had finished, program gives last chance to user 
for guessing whole word
*/
    if(attempt!=-1){
    	printf("\n\n\tLAST CHANCE!!\n\tGuess the word:");
		char lastG[length+1];
		scanf("%s",lastG);
		lastG[length]='\0';
		if(checkGuess(lastG, word)){
			// and again check the result
			printf("\n\tYou won!!\n");
		}
		else {
			printf("\n\tGame Over!!\n\tYou lost!!\n\n");
		}
	}
	printf("\n\tThe Word is: %s\n", word);
    printf("\n\tFinish!!\n");
	fclose(fp);
	//in the final we have to close file
	return 0;
}
