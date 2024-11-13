#include <stdio.h>
#include <string.h>

// Structure to store train details
struct Train {
    int train_number;
    char train_name[50];
    char source[50];
    char destination[50];
    int seats_available;
};

// Structure to store passenger details
struct Passenger {
    char name[50];
    int age;
    int train_number;
    int seat_number;
    int aadhaar_number; 
};

// Array of trains (assuming a small fixed number for simplicity)
struct Train trains[10] = {
    {101, "Express 1", "City A", "City B", 100},
    {102, "Express 2", "City C", "City D", 50},
    {103, "Express 3", "City E", "City F", 75},
    {104, "Express 4", "City G", "City H", 20},
    {105, "Express 5", "City I", "City J", 55},
    {106, "Express 6", "City K", "City L", 80},
    {107, "Express 7", "City M", "City N", 65},
    {108, "Express 8", "City O", "City P", 25},
    {109, "Express 9", "City Q", "City R", 40},
    {110, "Express 10", "City S", "City T", 60}
};

// Array of passengers
struct Passenger passengers[100];
int passenger_count = 0;

void viewTrains() {
    printf("\nAvailable Trains:\n");
    int i;
    for(i = 0; i < 10; i++) {  // Corrected loop to go through all trains
        printf("Train Number: %d, Name: %s, From: %s, To: %s, Seats Available: %d\n",
               trains[i].train_number, trains[i].train_name, trains[i].source, trains[i].destination, trains[i].seats_available);
    }
}

void bookTicket() {
    int train_number, seat_number, aadhaar_number;
    char name[50];
    int age;
    
    printf("\nEnter Train Number: ");
    scanf("%d", &train_number);

    int found = 0, train_index = -1;
    int i;
    for(i = 0; i < 10; i++) {
        if(trains[i].train_number == train_number) {
            found = 1;
            train_index = i;
            break;
        }
    }

    if(found) {
        if(trains[train_index].seats_available > 0) {
            printf("Enter Passenger Name: ");
            scanf("%s", name);
            printf("Enter Passenger Age: ");
            scanf("%d", &age);
            printf("Enter Aadhaar Number (10 digits): ");
            scanf("%d", &aadhaar_number);

            passengers[passenger_count].train_number = train_number;
            passengers[passenger_count].age = age;
            strcpy(passengers[passenger_count].name, name);
            passengers[passenger_count].seat_number = 100 - trains[train_index].seats_available + 1;
            passengers[passenger_count].aadhaar_number = aadhaar_number;  // Store Aadhaar number
            trains[train_index].seats_available--;
            passenger_count++;

            printf("Ticket booked successfully! Seat Number: %d\n", passengers[passenger_count - 1].seat_number);
        } else {
            printf("Sorry, no seats available on this train.\n");
        }
    } else {
        printf("Invalid Train Number.\n");
    }
}

void viewBookings() {
    printf("\nCurrent Bookings:\n");
    int i;
    for(i = 0; i < passenger_count; i++) {
        printf("Passenger Name: %s, Age: %d, Train Number: %d, Seat Number: %d, Aadhaar Number: %d\n",
               passengers[i].name, passengers[i].age, passengers[i].train_number, passengers[i].seat_number, passengers[i].aadhaar_number);
    }
}

void cancelTicket() {
    char name[50];
    printf("\nEnter Passenger Name to Cancel Ticket: ");
    scanf("%s", name);

    int found = 0;
    int i,j;
    for(i = 0; i < passenger_count; i++) {
        if(strcmp(passengers[i].name, name) == 0) {
            found = 1;
            int train_number = passengers[i].train_number;

            // Shift all passengers after the found one to the left
            for(j = i; j < passenger_count - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            passenger_count--;

            // Increment the seats available on the train
            for(j = 0; j < 10; j++) {
                if(trains[j].train_number == train_number) {
                    trains[j].seats_available++;
                    break;
                }
            }
            printf("Ticket cancelled successfully.\n");
            break;
        }
    }
    if(!found) {
        printf("No booking found with that name.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n*** Railway Ticket Reservation System ***\n");
        printf("1. View Trains\n");
        printf("2. Book Ticket\n");
        printf("3. View Bookings\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                viewTrains();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                viewBookings();
                break;
            case 4:
                cancelTicket();
                break;
            case 5:
                printf("Exiting system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
    return 0;
}

