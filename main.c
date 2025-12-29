#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 10
#define NUM_CATEGORIES 6
#define FILENAME "seats.txt"

typedef enum {
    SLEEPER,
    FIRST_AC,
    SECOND_AC,
    THIRD_AC,
    CHAIR_CAR,
    CHAIR_CAR_AC
} Category;

typedef struct {
    char name[20];
    int seats[ROWS][COLS];
} Coach;

Coach coaches[NUM_CATEGORIES] = {
    {"Sleeper Coach", {0}},
    {"1st AC", {0}},
    {"2nd AC", {0}},
    {"3rd AC", {0}},
    {"Chair Car", {0}},
    {"Chair Car AC", {0}}
};

// Load all coaches from file
void loadSeats() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No file found, starting fresh.\n");
        return;
    }
    for (int c = 0; c < NUM_CATEGORIES; c++) {
        char buffer[20];
        fscanf(file, "%s", buffer);  // this is used to read category name (not used)
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                fscanf(file, "%d", &coaches[c].seats[i][j]);
            }
        }
    }
    fclose(file);
    printf("Seats loaded from file.\n");
}

// Save all coaches to file
void saveSeats() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int c = 0; c < NUM_CATEGORIES; c++) {
        fprintf(file, "%s\n", coaches[c].name);
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                fprintf(file, "%d ", coaches[c].seats[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    printf("Seats saved to file.\n");
}

// Display seats for a specific coach
void displaySeats(int category) {
    printf("Seat Layout for %s (0 = Available, 1 = Booked):\n", coaches[category].name);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", coaches[category].seats[i][j]);
        }
        printf("\n");
    }
}

// Book a seat in a specific coach
void bookSeat(int category, int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid position.\n");
        return;
    }
    if (coaches[category].seats[row][col] == 1) {
        printf("Seat already booked.\n");
    } else {
        coaches[category].seats[row][col] = 1;
        printf("Seat booked in %s!\n", coaches[category].name);
    }
}

// Cancel a seat in a specific coach
void cancelSeat(int category, int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid position.\n");
        return;
    }
    if (coaches[category].seats[row][col] == 0) {
        printf("Seat not booked.\n");
    } else {
        coaches[category].seats[row][col] = 0;
        printf("Seat cancelled in %s!\n", coaches[category].name);
    }
}

int main() {
    //Firstly we initialize all seats to 0 
    loadSeats();
    
    int choice, category;
    while (1) {
        printf("\nRailway Reservation System\n");
        printf("Choose Coach Category:\n");
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            printf("%d. %s\n", i + 1, coaches[i].name);
        }
        printf("7. Exit\n");
        printf("Enter category (1-%d) or 7 to exit: ", NUM_CATEGORIES);
        scanf("%d", &category);
        
        if (category == 7) {
            saveSeats();
            break;
        }
        
        category--;  // this is used to subtracts 1 from the user's input to convert it to 0-based indexing.
        
        if (category < 0 || category >= NUM_CATEGORIES) {
            printf("Invalid category.\n");
            continue;
        }
        
        printf("\nOperations for %s:\n", coaches[category].name);
        printf("1. Display Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Seat\n");
        printf("4. Save and Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            displaySeats(category);
        } else if (choice == 2) {
            int row, col;
            printf("Enter row (0-4): ");
            scanf("%d", &row);
            printf("Enter column (0-9): ");
            scanf("%d", &col);
            bookSeat(category, row, col);
        } else if (choice == 3) {
            int row, col;
            printf("Enter row (0-4): ");
            scanf("%d", &row);
            printf("Enter column (0-9): ");
            scanf("%d", &col);
            cancelSeat(category, row, col);
        } else if (choice == 4) {
            saveSeats();
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    
    return 0;
}
