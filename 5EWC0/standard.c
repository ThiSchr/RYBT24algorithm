#include <stdio.h> 

// standard task 1 

int main () { 
    char cmd; 
    do { 
        printf("Command? "); 
        scanf(" %c", &cmd); 

        switch (cmd) {
            case 'q': 
                printf("Bye!\n"); 
                break;
            default: 
                printf("Unknown command '%c'\n", cmd); 
                break;
        }
    } 
    while (cmd != 'q'); 
    return 0; 
}