#include <stdio.h>

int main(void) {
    printf("** Complex Calculator **\n");

    float curr_re = 0.0; // floating point real number
    float curr_im = 0.0; // floating point imaginary number(i)

    char q; // define character q

    do { // do this at all times
        printf("Operation [0+-*crpq]? ");
        scanf(" %c", &q); // scan input and store in q

        if (q == '+' || q == '-' || q == '*') {
            printf("Complex operand? ");
            float new_re, new_im; // define floating point for the input numbers
            scanf("%f %f", &new_re, &new_im); // scan the input numbers and 'store' them in new_re and new_im

            if (q == '+') {
                curr_re += new_re; // curr_re = curr_re + new_re
                curr_im += new_im; // curr_im = curr_im + new_im
            } else if (q == '-') {
                curr_re -= new_re; // ^
                curr_im -= new_im; // ^
            } else if (q == '*') {
                float temp_re = curr_re * new_re - curr_im * new_im; // define temporary floating points
                float temp_im = curr_re * new_im + new_re * curr_im;  //

                curr_re = temp_re; // redefine new temporary to new current
                curr_im = temp_im; // solves the issue of the answer of curr_re*new_re being used as new_re
            }

            if (curr_im >= 0) {
                printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
            } else {
                printf("Current value is %.6f%.6fi\n", curr_re, curr_im);
            }
        } else if (q == 'p') {
            for (int outer = 10; outer >= -10; outer--) { // domain of the x-axis
                for (int inner = -10; inner <= 10; inner++) { // domain of the y-axis
                    if (outer == 0 && inner == 0) { // the origin of the graph
                        if (curr_im == 0 && curr_re == 0) {
                            printf("*");
                        } else {
                            printf("+");
                        }
                    } else if (outer == 0) { // print an x-axis
                        printf("-");
                    } else if (inner == 0) { // print a y-axis
                        printf("|");
                    } else if (inner == (int)curr_re && outer == (int)curr_im) {
                        printf("*"); // print the point of the current value
                    } else {
                        if (outer >= -10 && outer <= 10 && inner >= -10 && inner <= 10) { // print out the graph in this domain
                            printf(".");
                        } else {
                            printf(" ");
                        }
                    }
                }
                printf("\n");
            }
            if (curr_im >= 0) { 
                printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
            } else { 
                printf("Current value is %.6f%.6fi\n", curr_re, curr_im);
            }
        } else if (q == 'r') {
            int exponent;
            printf("Natural operand? ");
            scanf("%d", &exponent); // scan the input and store it in int exponent

            if (exponent >= 0) {
                float temp_re = 1.0; // starting point so exponent 0 works
                float temp_im = 0.0;

                for (int i = 0; i < exponent; i++) { // if the exponent is above zero, the loop runs 'exponent' times
                    float new_re = temp_re * curr_re - temp_im * curr_im; // runs over and over again with new temporary and new numbers
                    float new_im = temp_re * curr_im + temp_im * curr_re;
                    temp_im = new_im;
                    temp_re = new_re;
                }
                curr_re = temp_re; // the final temporary number is stored as the current
                curr_im = temp_im;

                if (curr_im >= 0) {
                    printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
                } else {
                    printf("Current value is %.6f%.6fi\n", curr_re, curr_im);
                }
            } else if (exponent < 0) { // if the exponent is smaller than zero, the command does not work
                printf("Natural command should be greater or equal to zero!\n");
            }
        } else if (q == '0') {
            curr_re = 0;
            curr_im = 0;
            printf("Current value is %.6f+%.6fi\n", curr_re, curr_im); // resets current and imaginary value back to zero
        } else if (q == 'c') {
            curr_im = -curr_im; // conjugate of the i function

            if (curr_im >= 0) {
                printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
            } else {
                printf("Current value is %.6f%.6fi\n", curr_re, curr_im);
            }
        } else if (q != 'q') {
            printf("Invalid command '%c'\n", q);  // if the character q is not defined as something stated earlier, Invalid command is printed
            if (curr_im >= 0) { 
              printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
            } else { 
              printf("Current value is %.6f%.6fi\n", curr_re, curr_im);
            }
        }
    } while (q != 'q');

    if (curr_im >= 0) { 
      printf("Current value is %.6f+%.6fi\n", curr_re, curr_im);
    } else { 
      printf("Current value is %.6f%.6fi\n", curr_re, curr_im); 
    }
    printf("Bye!\n"); // whilst q is equal to q "Bye" is printed
    return 0;
}
