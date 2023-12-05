#include <stdio.h>
#include <string.h>

#define LENGTH 120

//grade 6.00/10.00

// print the array 
void printArray(char array[], int length) {
    for (int i = 0; i < length; i++) {
        if (array[i] == '\0') { // to not print a null character 
            printf("\\0");
        } else {
            printf("%c", array[i]);
        }
    }
    printf("\n");
}

// Function to insert a name in the array 
void insertName(char *startPos[], int *nrNames, char newName[]) {
    int spaceUsed(char *startPos[], int nrNames); // to use LENGTH - spaceUsed
    int length = strlen(newName) + 1; // Calculate length of the name including the null 
    int spaceLeft = LENGTH - spaceUsed(startPos, *nrNames); // the entire length (120 - spaceUsed)

    if (length <= spaceLeft) { 
        if (*nrNames > 0) {
            startPos[*nrNames] = startPos[*nrNames - 1] + strlen(startPos[*nrNames - 1]) + 1;
        } // to point to the next free space in the naems array
        strcpy(startPos[*nrNames], newName); // copy the string to a free space 
        (*nrNames)++; 
    } else {
        printf("Not enough space left\n"); 
    }
}

// Function to count how many characters of the array ahve been used
int spaceUsed(char *startPos[], int nrNames) {
    int totalCharacters = 0; 
    for (int i = 0; i < nrNames; i++) { 
        totalCharacters += strlen(startPos[i]) + 1; // include the null characters
    }
    return totalCharacters;
}

// Function to print the starting position, length and string of the names in the array 
void printNames(char names[], char *startPos[], int nrNames) { 
    for (int i = 0; i < nrNames; i++) {
        printf("startPos[%d]=%03d #chars=%03d string=\"%s\"\n", i, (int)(startPos[i] - names) , (int)strlen(startPos[i]) + 1, startPos[i]); // calculates the offsset and length of the ith name (w null char)
    }
}

// function to search for the names in the array 
int lookupName(char names[], char *startPos[], int nrNames, char name[]) {
    int lastIndex = -1; // if lastindex stays -1 we know then naem was not found
    for (int i = 0; i < nrNames; i++) { 
        if (strcmp(startPos[i], name) == 0) { // compare the name in the startpos to the name
            lastIndex = i;
        }
    }
    return lastIndex != -1 ? (int)(startPos[lastIndex] - names) : -1; // either calculates the difference between the beginning and the startpos of the name or if -1 the name wasnot found 
}

// function to remove a name out of the array 
void removeName(char *startPos[], int *nrNames, char name[]) {
    int indexToRemove = -1;
    for (int i = 0; i < *nrNames; i++) {
        if (strcmp(startPos[i], name) == 0) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        // move the last name in the startPos list to the position of the removed name
        startPos[indexToRemove] = startPos[*nrNames - 1];
        (*nrNames)--;
    } else {
        printf("Did not find \"%s\"\n", name);
    }
}

// function to swap two names
void swapNames(char *startPos[], int i, int j) {
    char *temp = startPos[i];
    startPos[i] = startPos[j];
    startPos[j] = temp;
}

// function to merge two names together (does currently not work correctly)
void mergeNames(char *names, char *startPos[], int *nrNames, int startPosIndex) {
    int len = strlen(startPos[startPosIndex]);
    char *startOfNextName = startPos[startPosIndex] + len;

    // check if the next name exists and has not been removed
    int nextNameIndex = lookupName(names, startPos, *nrNames, startOfNextName);

    if (nextNameIndex != -1) {
        removeName(startPos, nrNames, startOfNextName);
        len += strlen(startPos[startPosIndex]) + 1; // include null character in the length
        // replace the null character between the two names by '+'
        startPos[startPosIndex][len - 1] = '+';
    }
}

int main() {
    char names[LENGTH];
    for (int i = 0; i < LENGTH; i++) {
        names[i] = '\0';
    }

    char *startPos[LENGTH];
    int nrNames = 0;

    startPos[nrNames] = names;

    char command;
    char newName[LENGTH];

    while (1) {
        printf("Command? ");
        scanf(" %c", &command);
        if (command == 'd') {
            // to print on the display 
        } else if (command == 'p') {
            printArray(names, LENGTH);
        } else if (command == 'i') {
            printf("Name? ");
            scanf("%s", newName);
            insertName(startPos, &nrNames, newName);
        } else if (command == 'u') {
            printf("Space used is %d\n", spaceUsed(startPos, nrNames));
        } else if (command == 'n') {
            printNames(names, startPos, nrNames);
        } else if (command == 'l') {
            printf("Name? ");
            scanf("%s", newName);
            int index = lookupName(names, startPos, nrNames, newName);
            printf("\"%s\" has index %d\n", newName, index);
        } else if (command == 'r') {
            printf("Name? ");
            scanf("%s", newName);
            removeName(startPos, &nrNames, newName);
        } else if (command == 's') {
            int i, j;
            printf("Indices? ");
            scanf("%d %d", &i, &j);
            swapNames(startPos, i, j);
        } else if (command == 'm') {
            int startPosIndex;
            printf("StartPos index? ");
            scanf("%d", &startPosIndex);
            mergeNames(names, startPos, &nrNames, startPosIndex);
        } else if (command == 'q') {
            printf("Bye!\n");
            break;
        } else {
            printf("Unknown command '%c'\n", command);
        }
    }

    return 0;
}
