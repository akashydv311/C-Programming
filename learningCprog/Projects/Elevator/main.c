#include <stdio.h>
#include <stdlib.h> // for system()
#include <time.h>   // for delay function

#define MIN_FLOOR 0
#define MAX_FLOOR 9

// Simple delay function (approximate, in milliseconds)
void delay(int ms) {
    clock_t start_time = clock();
    while (clock() < start_time + ms * CLOCKS_PER_SEC / 1000);
}

// Clear screen function for Windows (MinGW) and others
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Draw the elevator shaft with elevator at currentFloor
void drawElevator(int currentFloor) {
    for (int floor = MAX_FLOOR; floor >= MIN_FLOOR; floor--) {
        if (floor == currentFloor) {
            printf("| [%2d][E] |\n", floor);
        } else {
            printf("| [%2d][ ] |\n", floor);
        }
    }
    printf("+---------+\n");
}

int main() {
    int currentFloor = 0;
    int requestedFloor;

    printf("Welcome to the Interactive Elevator Simulator!\n");
    printf("The building has floors from %d to %d.\n", MIN_FLOOR, MAX_FLOOR);
    printf("Press -1 to exit.\n");
    delay(5000);

    while (1) {
        clearScreen();
        drawElevator(currentFloor);

        printf("\nEnter the floor number you want to go to: ");
        scanf("%d", &requestedFloor);

        if (requestedFloor == -1) {
            printf("Exiting the elevator simulator. Goodbye!\n");
            break;
        }

        if (requestedFloor < MIN_FLOOR || requestedFloor > MAX_FLOOR) {
            printf("Invalid floor. Please enter a floor between %d and %d.\n", MIN_FLOOR, MAX_FLOOR);
            delay(1500);
            continue;
        }

        if (requestedFloor == currentFloor) {
            printf("You are already on floor %d.\n", currentFloor);
            delay(1500);
            continue;
        }

        printf("Moving from floor %d to floor %d...\n", currentFloor, requestedFloor);
        delay(1000);

        if (requestedFloor > currentFloor) {
            for (int floor = currentFloor + 1; floor <= requestedFloor; floor++) {
                clearScreen();
                drawElevator(floor);
                delay(700);  // pause to show movement
            }
        } else {
            for (int floor = currentFloor - 1; floor >= requestedFloor; floor--) {
                clearScreen();
                drawElevator(floor);
                delay(700);
            }
        }

        currentFloor = requestedFloor;
    }

    printf("Press Enter to exit...");
    getchar(); // consume newline from scanf
    getchar(); // wait for Enter key

    return 0;
}
