#include <stdio.h>
#include <string.h> 
// grade 3.08/10

#define LENGTH 30

// Function to read a line of the input
void readLine(char inputString[], int maxLength) {
    if (fgets(inputString, maxLength, stdin) != NULL) {
        // Remove the newline character
        size_t len = strlen(inputString);
        if (len > 0 && inputString[len - 1] == '\n') {
            inputString[len - 1] = '\0';
        }
    }
}

void printString(char str[]) {
    printf("The current string is: \"%s\"\n", str);
}

// Function to print the current array
void printArray(char str[]) {
    printf("The current array is: [");
    for (int i = 0; i < LENGTH; i++) {
        if (i > 0) {
            printf(",");
        }
        if (str[i] == '\0') {
            printf("\\0");
        } else {
            printf("%c", str[i]);
        }
    }
    printf("]\n");
}



// Function to find the first occurrence of a character in a string
int findFirstOccurrence(char str[], char aChar) {
    size_t length = strlen(str);
    
    for (size_t i = 0; i < length; i++) {
        if (str[i] == aChar) {
            return i;
        }
    }
    
    return -1; // Character not found
}

// Function to read a positive integer from a string
int readInt(char str[], int length) {
    int result = 0;
    int i = 0;

    while (i < length && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (i == 0 || str[i] != '\0') {
        return -1; // Not a valid integer
    }

    return result;
}

// Function to insert a character at a specific index in a string
void insertChar(char str[], char aChar, int index) {
    int length = strlen(str);

    if (index < 0 || index > length) {
        printf("Invalid index\n");
        return;
    }

    for (int i = length; i >= index; i--) {
        str[i + 1] = str[i];
    }

    str[index] = aChar;
}

// Function to replace characters in a string
void replaceChars(char str[], char fromString[], char toChar) {
    int replaced = 0;
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        if (strchr(fromString, str[i]) != NULL) {
            str[i] = toChar;
            replaced++;
        }
    }

    printf("Replaced %d characters\n", replaced);
}

int main() {
    char currString[LENGTH] = "";
    char inputString[LENGTH];
    char fromString[LENGTH];
    char toChar;

    do {
        printf("Command? ");
        readLine(inputString, LENGTH);

        switch (inputString[0]) {
            case 'p':
                printString(currString);
                break;
            case 'a':
                printArray(currString);
                break;
            case 's':
                printf("Please enter a string? ");
                readLine(currString, LENGTH);
                break;
            case 'o':
                printf("Find first occurrence of which character? ");
                readLine(inputString, LENGTH);
                int index = findFirstOccurrence(currString, inputString[0]);
                printf("The first occurrence of '%c' is at index %d\n", inputString[0], index);
                break;
            case 'i':
                printf("Insert which character? ");
                readLine(inputString, LENGTH);
                char charToInsert = inputString[0];
                printf("At what index? ");
                readLine(inputString, LENGTH);
                int insertIndex = readInt(inputString, LENGTH);
                if (insertIndex != -1) {
                    insertChar(currString, charToInsert, insertIndex);
                    printf("Insertion completed\n");
                } else {
                    printf("Invalid index or character\n");
                }
                break;
            case 'r':
                printf("Replace which characters? ");
                readLine(fromString, LENGTH);
                printf("with which character? ");
                readLine(inputString, LENGTH);
                toChar = inputString[0];
                replaceChars(currString, fromString, toChar);
                break;
            case 'q':
                printf("Bye!\n");
                break;
            default:
                printf("Unknown command '%c'\n", inputString[0]);
                break;
        }
    } while (inputString[0] != 'q');

    return 0;
}
