#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPERSONS 240
#define MAXNAME 100 

// grade 10/10 
// displayfunction is not working

struct person_t {
    char name[MAXNAME];
    float height;
};
// fucntion to display on a displayboard of the pynq
void displayValues(struct person_t persons[], int nrPersons, int from, int to) {
    // Implement this function to display values and highlight swapped values in red
    // printf(", persons[from].name, persons[from].height);
    // printf(", persons[to].name, persons[to].height);
}
// function to display the current array
void printValues(struct person_t persons[], int startArray, int endArray) {
    printf("[");
    for (int i = startArray; i <= endArray; i++) {
        printf("(\"%s\",%.2f)", persons[i].name, persons[i].height);
        if (i < endArray) {
            printf(",");
        }
    }
    printf("]\n");
}
// function to do the swapping in a tedious way
void bubbleSort(struct person_t persons[], int nrPersons) {
    for (int i = 0; i < nrPersons - 1; i++) {
        for (int j = 0; j < nrPersons - i - 1; j++) {
            // compare the height
            if (persons[j].height > persons[j + 1].height) {
                // swap persons
                struct person_t temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;

                // printValues and displayValues after swapping
                printf("after swapping: ");
                printValues(persons, 0, nrPersons - 1);
                displayValues(persons, nrPersons, j, j + 1);
            }
            // if heights are equal, compare names and swap if necessary
            else if (persons[j].height == persons[j + 1].height && strcmp(persons[j].name, persons[j + 1].name) > 0) {
                // swap the persons
                struct person_t temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;

                // printValues and displayValues after swapping
                printf("after swapping: ");
                printValues(persons, 0, nrPersons - 1);
                displayValues(persons, nrPersons, j, j + 1);
            }
        }
    }
}
// function to do the swapping in an 'easier' way
void merge(struct person_t persons[], int left, int mid, int right) {
    struct person_t tmp[right - left + 1];
    int pos = 0;
    int lpos = left;
    int rpos = mid + 1;

    while (lpos <= mid && rpos <= right) {
        if (persons[lpos].height < persons[rpos].height ||
            (persons[lpos].height == persons[rpos].height && strcmp(persons[lpos].name, persons[rpos].name) < 0)) {
            tmp[pos++] = persons[lpos++];
        } else {
            tmp[pos++] = persons[rpos++];
        }
    }

    while (lpos <= mid) {
        tmp[pos++] = persons[lpos++];
    }

    while (rpos <= right) {
        tmp[pos++] = persons[rpos++];
    }

    // copy sorted values back to the original array
    for (int i = 0; i < pos; i++) {
        persons[left + i] = tmp[i];
    }
}

// function to print the swapping
void mrgeSort(struct person_t persons[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        printf("need to sort      ");
        printValues(persons, left, right);

        mrgeSort(persons, left, mid);
        printf("after sorting lhs ");
        printValues(persons, left, mid);

        mrgeSort(persons, mid + 1, right);
        printf("after sorting rhs ");
        printValues(persons, mid + 1, right);

        merge(persons, left, mid, right);
        printf("after merging     ");
        printValues(persons, left, right);
    }
}



// function to find the maximum height among the first nrPersons 
float maxValue(struct person_t persons[], int nrPersons) {  
    if (nrPersons <= 0) {
        return 0.0;
    }

    float max = persons[0].height; 
    for (int i = 1; i < nrPersons; i++) {
        if (persons[i].height > max) {  
            max = persons[i].height; 
        }
    }
    return max; 
}

// function to find the minimum height among the first nrPersons 
float minValue(struct person_t persons[], int nrPersons) {
    if (nrPersons <= 0) {
        return 0.0;
    }

    float min = persons[0].height;
    for (int i = 1; i < nrPersons; i++) {
        if (persons[i].height < min) {
            min = persons[i].height;
        }
    }
    return min;
}

// function to change the amount of persons in the array
int initialise(struct person_t persons[], int nrPersons) {
    int newSize;

    printf("Number of persons? ");
    scanf("%d", &newSize);

    if (newSize >= 1 && newSize <= MAXPERSONS) {
        for (int i = 0; i < newSize; i++) {
            sprintf(persons[i].name, "person-%d", i);
            persons[i].height = newSize - i - 1;
        }
        return newSize;
    } else {
        printf("Number of persons must be from 1 up to 240\n");
        return nrPersons;
    }
}

// function to replace the name and height of a person in the array
void replacePerson(struct person_t persons[], int nrPersons) {
    int index;
    printf("Index? ");
    scanf("%d", &index);

    if (index >= 0 && index < nrPersons) {
        printf("Name? ");
        scanf("%s", persons[index].name); // %s to read string
        printf("Height? ");
        scanf("%f", &persons[index].height); // %f to read float
    } else {
        printf("Index must be from 0 up to %d\n", nrPersons - 1);
    }
}
// main function to call the stack when right character is called upon
int main() {
    struct person_t persons[MAXPERSONS];
    int nrPersons = 0;
    char cmd;

    while (1) {
        printf("Command? ");
        scanf(" %c", &cmd);

        if (cmd == 'd') {
            
        } else if (cmd == 'i') {
            nrPersons = initialise(persons, nrPersons);
        } else if (cmd == 'p') {
            printValues(persons, 0, nrPersons - 1);
        } else if (cmd == 'h') {
            float max = maxValue(persons, nrPersons);
            float min = minValue(persons, nrPersons);
            float range = max - min;
            printf("Min: %.3f\nMax: %.3f\nRange: %.3f\n", min, max, range);
        } else if (cmd == 'r') {
            replacePerson(persons, nrPersons);
        } else if (cmd == 'b') {
            bubbleSort(persons, nrPersons);
        } else if (cmd == 'm') {
           mrgeSort(persons, 0, nrPersons - 1);
        } else if (cmd == 'q') {
            printf("Bye!\n");
            return 0;
        } else {
            printf("Unknown command '%c'\n", cmd);
        }
    }

    return 0;
}
