#include <string.h>
#include <stdio.h> 
#include <libpynq.h> 

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240
#define START 'S' /* starting position*/
#define DESTINATION 'D' /* destination*/
#define WALL '#' /* Wall*/
#define NOT_VISITED '.' /* corridor */
#define PATH '+' /* path */
#define VISITED '~' /* visited */

// grade 6.67/10.00

typedef struct {
    int x;
    int y;
} coordinate_t;

typedef struct {
    char grid[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    coordinate_t size;
} maze_t;

// function to initialize the maze 
void inputMaze(maze_t *maze) {
    printf("Number of rows? ");
    scanf("%d", &maze->size.x);
    printf("Number of columns? ");
    scanf("%d", &maze->size.y);
// if the maze is too small
    if (maze->size.x < 2 || maze->size.y < 2) {
        printf("The number of rows and columns must be at least two\n");
        maze->size.x = maze->size.y = -1;
        return;
    }

    int startCount = 0; // to check for amout of starting point to replace some with walls 

    // clear input buffer
    while ((getchar()) != '\n');

    for (int i = 0; i < maze->size.x; i++) {
        printf("Input row  %d: ", i);
        scanf("%s", maze->grid[i]);

        // check for multiple starting points and replace them with walls
        for (int j = 0; j < maze->size.y; j++) {
            if (maze->grid[i][j] == START) {
                if (startCount > 0) {
                    printf("Dropping extra starting point\n");
                    maze->grid[i][j] = WALL;
                }
                startCount++;
            }
        }
    }
}

// fucniton to print the maze in characters 
void printMaze(maze_t *maze) {
    if (maze->size.x < 2 || maze->size.y < 2) {
        // do nothing if the maze is too small
        return;
    }

    for (int i = 0; i < maze->size.x; i++) {
        for (int j = 0; j < maze->size.y; j++) {
            printf("%c", maze->grid[i][j]);
        }
        printf("\n");
    }
}

// fucniton to display the maze on the pynq display
void displayMaze(maze_t *maze) {
    if (maze->size.x < 2 || maze->size.y < 2) {
        // do nothing if the maze is too small
        return;
    }

    for (int i = 0; i < maze->size.x; i++) {
        for (int j = 0; j < maze->size.y; j++) {
            int x1 = j * (DISPLAY_WIDTH / maze->size.y);
            int y1 = i * (DISPLAY_HEIGHT / maze->size.x);
            int x2 = (j + 1) * (DISPLAY_WIDTH / maze->size.y) - 1;
            int y2 = (i + 1) * (DISPLAY_HEIGHT / maze->size.x) - 1;
            int c;

            switch (maze->grid[i][j]) {
                case '#': // WALL
                    c = RGB_RED;
                    break;
                case '+': // PATH
                    c = RGB_YELLOW;
                    break;
                case 'S': // START
                    c = RGB_BLUE;
                    break;
                case 'D': // DESTINATION
                    c = RGB_GREEN;
                    break;
                case '~': // VISITED
                    c = rgb_conv(100, 100, 100);
                    break;
                case '.': // NOT_VISITED
                    c = RGB_BLACK;
                    break;
                default:
                    c = RGB_BLACK;
            }

            printf("dfr %d %d %d %d %d\n", x1, y1, x2, y2, c);
        }
    }
} 

// fucniton to print where the start is 
coordinate_t findStartDestination(maze_t *maze, coordinate_t *destination) { 
    coordinate_t start = {-1, -1}; 
    *destination = start; 

    for (int i = 0; i < maze->size.x; i++) { 
        for (int j = 0; j < maze->size.y; j++) { 
            if (maze->grid[i][j] == START) { 
                start.x = i; 
                start.y = j; 
            } else if (maze->grid[i][j] == DESTINATION) { 
                if (destination->x == -1 || destination->y == -1 || (i < destination->x) || (i == destination->x && j< destination->y)) { 
                    destination->x = i; 
                    destination->y = j; 
                }
            }
        }
    }
    return start; 
}

// fucniton to swap the start of the maze with the destination
void swapStartDestination(maze_t *maze, coordinate_t *start, coordinate_t *destination) {
    if (start->x != -1 && start->y != -1 && destination->x != -1 && destination->y != -1) {
        char temp = maze->grid[start->x][start->y];
        maze->grid[start->x][start->y] = maze->grid[destination->x][destination->y];
        maze->grid[destination->x][destination->y] = temp;

        // update start and destination coordinates after swapping
        int tempX = start->x;
        int tempY = start->y;
        start->x = destination->x;
        start->y = destination->y;
        destination->x = tempX;
        destination->y = tempY;
    }
}
// fucniton to ruin your mental sanity and find a path 
int findPath(maze_t *maze, coordinate_t current, int length) {
    // check if the current position is outside the maze
    if (current.x < 0 || current.x >= maze->size.x || current.y < 0 || current.y >= maze->size.y) {
        return 0;
    }

    // check if the current position is blocked by a wall or already part of the path
    if (maze->grid[current.x][current.y] == WALL || maze->grid[current.x][current.y] == PATH || maze->grid[current.x][current.y] == VISITED) {
        return 0;
    }

    // check if the current position is the destination
    if (maze->grid[current.x][current.y] == DESTINATION) {
        return length - 1; // Return the length 
    }

    // mark the current position as part of the path
    if (maze->grid[current.x][current.y] != START) {
        maze->grid[current.x][current.y] = PATH;
    }

    // find the path by searching in differnet directions
    int len = findPath(maze, (coordinate_t){current.x - 1, current.y}, length + 1);
    if (len > 0) return len;

    len = findPath(maze, (coordinate_t){current.x, current.y + 1}, length + 1);
    if (len > 0) return len;

    len = findPath(maze, (coordinate_t){current.x + 1, current.y}, length + 1);
    if (len > 0) return len;

    len = findPath(maze, (coordinate_t){current.x, current.y - 1}, length + 1);
    if (len > 0) return len;

    // if there is no path mark as visited 
    if (maze->grid[current.x][current.y] != START) {
        maze->grid[current.x][current.y] = VISITED;
    }

    // if there is no path found from this position
    return 0;
}

// function to mirror the maze sideways/swap the x and y coordinate 
void mirrorMaze(maze_t *maze) {
    maze_t mirroredMaze;
    mirroredMaze.size.x = maze->size.y;
    mirroredMaze.size.y = maze->size.x;

    for (int i = 0; i < mirroredMaze.size.x; i++) {
        for (int j = 0; j < mirroredMaze.size.y; j++) {
            mirroredMaze.grid[i][j] = maze->grid[j][i];
        }
    }

    // swap the size of the maze after mirroring
    maze->size.x = mirroredMaze.size.x;
    maze->size.y = mirroredMaze.size.y;

    // copy the mirrored grid back to the original maze
    for (int i = 0; i < maze->size.x; i++) {
        for (int j = 0; j < maze->size.y; j++) {
            maze->grid[i][j] = mirroredMaze.grid[i][j];
        }
    }
}


int main() {
    char cmd;
    maze_t maze;
    maze.size.x = -1;
    maze.size.y = -1;
    coordinate_t start, destination; 
    int pathLength;
    
    while (1) {
        printf("Command? ");
        scanf(" %c", &cmd);

        switch (cmd) {
            case 'q':
                printf("Bye!\n");
                return 0;

            case 'i':
                inputMaze(&maze);
                break;
    
            case 'p':
                printMaze(&maze);
                break;

            case 'd':
                displayMaze(&maze);
                break;
                
                case 'm':
                if (maze.size.x > 1 && maze.size.y > 1) {
                    mirrorMaze(&maze);
                } else {
                    printf("Maze is too small to mirror.\n");
                }
                break;
                
            case 'f':
                if (maze.size.x > 1 && maze.size.y > 1) {
                    start = findStartDestination(&maze, &destination);
                if (start.x == -1 || start.y == -1 || destination.x == -1 || destination.y == -1) {                        printf("Maze contains no start or destination.\n");
                } else {
                    pathLength = findPath(&maze, start, 1);
                if (pathLength > 0) {
                    printf("Found a path of length %d\n", pathLength);
                } else {
                    printf("No path found.\n");
                }
                    printMaze(&maze);
                }
                } else {
                    printf("Maze is too small to find a path.\n");
                }
                break;

            case 's': { 
                start = findStartDestination(&maze, &destination); // Assign values to start and destination
                if (start.x == -1 || start.y == -1) { 
                    printf("Maze contains no start\n"); 
                    printf("Maze contains no destination\n");
                }   
                else {
                    printf("The start is at             (%3d,%3d)\n", start.y, start.x); 
                    printf("The first destination is at (%3d,%3d)\n", destination.y, destination.x); 
                } 
                break; 
            }
        
            case 'S':
                swapStartDestination(&maze, &start, &destination);
                break;

            default:
                printf("Unknown command '%c'\n", cmd);
                break;
        }
    } 
    return(0); 
}
