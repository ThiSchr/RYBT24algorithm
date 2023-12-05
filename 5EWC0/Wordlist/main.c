#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAXWORDS 12
#define MAXLEN 25 

// grade 6.19/10.00

// function to print the wordlist
void printWordList(char *wordList[MAXWORDS], int wordCount) { // print the wordlist 
    for (int i = 0; i < wordCount; i++) { // when the wordlist is not full print every word
        printf("\"%s\" is referenced from entries %d\n", wordList[i], i); // print the string (word) and the place in the string i 
    }
}

// function to insert a word in the wordlist
void insertWord(char *wordList[MAXWORDS], char *word, int *wordCount) { // insert a word 
    if (*wordCount >= MAXWORDS) { // if the amount of words is larger than the defined maximum amount of words
        printf("List is full\n"); 
        return;
    }

    int i; // global integer so i can update and be changed in the order 
    for (i = *wordCount - 1; i >= 0 && strcmp(word, wordList[i]) < 0; --i) { // find the correct position to insert the word in alphabetical order 
        wordList[i + 1] = wordList[i]; // shift elements to make space for the new word
    }

    wordList[i + 1] = malloc(strlen(word) + 1); // mallocate space for the new inserted word 
    strcpy(wordList[i + 1], word); // copy the wordlist into the mallocated space 
    (*wordCount)++; // there is now an extra word in the list so the count goes up
} 

// function to find a word in the wordlist 
void findWord(char **wordList, char *word, int *index, int wordCount) { 
    *index = -1; // initialize index to -1, or not found
     for (int i = wordCount - 1; i >= 0; i--) { // loop goes through the wordlist array (from last to first index can also be made with +1 and i++)
        if (strcmp(word, wordList[i]) == 0)  {  // compares the input word with the current word in the wordlist at i 
            *index = i; // if the wrod and wordlist[i] matches the pointer to an index is updated 
            break; 
        }
     }
} 

// function to swap words from the wordlist
void swapWords(char *wordList[MAXWORDS], char *word1, char *word2, int wordCount) { 
    int index1 = -1, index2 = -1; // standard place of the index is not in the list(-1)
    findWord(wordList, word1, &index1, wordCount); // find word 1
    findWord(wordList, word2, &index2, wordCount); // find word 2

    if (index1 != -1 && index2 != -1) { // if both the words are found (meaning they are both not -1, or not in list)
        char *temp = wordList[index1]; // tempory pointer becomes index 1
        wordList[index1] = wordList[index2]; // index 1 becomes index 2
        wordList[index2] = temp; // index 2 becomes temp, which is index1
    } else { 
        printf("Word(s) not in list\n"); // if only one word is found or neither, print wrod not in list
    }
} 

// function to find the longest word in the wordlist 
void longestWord(char *WordList[MAXWORDS], char **longest, int wordCount) { 
    *longest = NULL; // set longest to NULL for when the word list is empty  
    
    for (int i = 0; i < wordCount; i++) { // goes through the wordlist to find the longest word
        if (*longest == NULL || strlen(WordList[i]) >= strlen(*longest)) { // checks whether current longest is a NULL or longer than the previous longest. if equal its higher index
            *longest = WordList[i]; // the longest pointer points to the longest word in the wordList
        } 
    }
} 

// function to change vowels 
void changeVowels(char *word) { // pointer to characters making a word so function changes the characters  
    while (*word) { // loop through the character of a word until a NULL char is met
        if (*word == 'a') { // if the current character is an a 
            *word = 'e'; // the character becomes e 
        } else if (*word == 'e') { 
            *word = 'a'; 
        } else if (*word == 'o') { 
            *word = 'u'; 
        } else if (*word == 'u') { 
            *word = 'o'; 
        }
        word++; // to make sure all the characters of the word are checked 
    }
}  

// function to add two strings together 
void appendWords(char *wordList[MAXWORDS], char *word1, char *word2, int *wordCount) { 
    int index1 = -1, index2 = -1; // set the indexes to not found (-1)
    findWord(wordList, word1, &index1, *wordCount); // find word1 and store in index1
    findWord(wordList, word2, &index2, *wordCount); // find word2 and store in index 2

    if (index1 != -1 && index2 != -1) { // if both are found 
        char *newWord = malloc(MAXLEN * sizeof(char)); // malocate memory for the new word, the size is calulated by the sum of word1 and word2
        snprintf(newWord, MAXLEN, "%s+%s", word1, word2); // format the words, using snprintf to not have the newWord go over the MAXLEN
        free(wordList[index1]); // free the mallocated memory from word1 because it will be removed
        wordList[index1] = newWord; // the wordlist at index1 is updated for the newly created word
        free(wordList[index2]); // the mallocated memory from word2 is freed 
        for (int i = index2; i < *wordCount - 1; i++) { // from element index2 + 1 to wordCOunt - 1 are shifted  
            wordList[i] = wordList[i + 1]; // wordlist is updated because of the freed index from word 2
        }
        (*wordCount)--; // there is a word removed from the list so wordCount is decremented 
    } else {
        printf("Word(s) not in list\n");
    }
} 

// function to delete a word from the wordlist
void deleteWord(char *wordList[MAXWORDS], char *word, int *wordCount) { 
    int index = -1; // index set to not found 
    findWord(wordList, word, &index, *wordCount); // find the entered word in the list

    if (index != -1) { // if the word is found 
        free(wordList[index]); // free the memory from the word 
        wordList[index] = NULL; // set the pointer to NULL 
        for (int i = index; i < *wordCount - 1; i++) { // shift elements to fill in for the removed word just like in appendWords
            wordList[i] = wordList[i + 1]; 
        } 
        (*wordCount)--; // there is a wrod removed from teh list so wordCount is decremetned
    } else { 
        printf("Word not found\n"); 
    }
} 


int main(void) { 
    // declare character and integers
    char *wordList[MAXWORDS];
    char cmd; 
    char *longest = NULL; // pointer to the longest word, set as NULL 
    int wordCount = 0;

    do {
        printf("Command? ");
        scanf(" %c", &cmd); // scan the character and put in cmd

        switch (cmd) {
            case 'q':
                printf("Bye!\n");
                break;
            case 'p':
                printWordList(wordList, wordCount); // print the wordlist
                break;
            case 'i':
                {
                    char input[MAXLEN]; // string input which cannot be longer then defined MAXLEN
                    printf("Word? ");
                    scanf("%s", input); // scan a string (of words) and put in the string input
                    insertWord(wordList, input, &wordCount); // insert the word in the list keeping track ofthe wordlist, wordcoutn and entered input
                }
                break; 
            case 'f': 
                { 
                    char input[MAXLEN]; // string input which cannot be longe then defined MAXLEN
                    printf("Word? "); 
                    scanf("%s", input); // scan a string (of words) and put in the string input 
                    int index; 
                    findWord(wordList, input, &index, wordCount); // find the word in the list and add the place of the word in the int index
                    printf("The index is %d\n", index); // print the place of the word
                }
                break; 
            case 'w': 
                {
                    char word1[MAXLEN], word2[MAXLEN]; // declare strings for word1 and word2
                    printf("Words? "); 
                    scanf("%s %s", word1, word2); // scan the input as a string, and store the strings in word1 and word2
                    swapWords(wordList, word1, word2, wordCount); // swap word1 and word2
                }   
                break; 
            case 'l':
                longestWord(wordList, &longest, wordCount); // find the longest word with the function 
                if (longest != NULL) { // if the longest word is not a NULL char
                    printf("The longest word is %s\n", longest); 
                } else { // if the longest word is a NULL char 
                    printf("No words\n"); 
                } 
                break; 
            case 'v': 
                for (int i = 0; i < wordCount; i++) { // to loop through all of the words
                    changeVowels(wordList[i]); // use the function to change the vowels
                } 
                break; 
            case 'a': 
                { 
                    char word1[MAXLEN], word2[MAXLEN]; // ask for two words to be added together 
                    printf("Words? "); 
                    scanf("%s %s", word1, word2); 
                    appendWords(wordList, word1, word2, &wordCount); // add the two words together 
                }      
                break; 
            case 'd': 
                { 
                    char input[MAXLEN]; // set a string for the input 
                    printf("Word? "); 
                    scanf("%s", input); // scan the word entered
                    deleteWord(wordList, input, &wordCount); // delete the word using the funciotn 
                } 
                break;
            default:
                printf("Unknown command '%c'\n", cmd);
                break;
        }
    } while (cmd != 'q');

    // do this every time; 
    for (int i = 0; i < wordCount; ++i) { // whenever the wordcount is not full 
        free(wordList[i]); // free the mallocated space from the wordlist
    }
    return 0; 
}
