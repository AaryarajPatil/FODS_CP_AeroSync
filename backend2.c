#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FLIGHTS 50
#define MAX_PASSENGERS 100

struct Passenger {
    char name[50];
    int age;
    char seat[10];
};

struct Flight {
    char flightNumber[10];
    char destination[50];
    char departureTime[20];
    int totalSeats;
    int bookedSeats;
    float fare;
    struct Passenger passengers[MAX_PASSENGERS];
};

struct Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void saveToFile() {
    FILE *fp = fopen("flights.txt", "wb");
    if (!fp) {
        printf("Error: Unable to save file.\n");
        return;
    }
    fwrite(&flightCount, sizeof(int), 1, fp);
    fwrite(flights, sizeof(struct Flight), flightCount, fp);
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("flights.txt", "rb");
    if (!fp) return;
    fread(&flightCount, sizeof(int), 1, fp);
    fread(flights, sizeof(struct Flight), flightCount, fp);
    fclose(fp);
}

void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("\nFlight limit reached.\n");
        return;
    }

    struct Flight f;
    printf("\nAdd Flight\n");

    printf("Enter Flight Number: ");
    scanf("%9s", f.flightNumber);
    clearBuffer();

    printf("Enter Destination: ");
    fgets(f.destination, sizeof(f.destination), stdin);
    f.destination[strcspn(f.destination, "\n")] = 0;

    printf("Enter Departure Time: ");
    scanf("%19s", f.departureTime);

    printf("Enter Total Seats: ");
    scanf("%d", &f.totalSeats);

    if (f.totalSeats <= 0 || f.totalSeats > MAX_PASSENGERS) {
        printf("Invalid number of seats.\n");
        return;
    }

    printf("Enter Fare per Ticket: Rs.");
    scanf("%f", &f.fare);

    f.bookedSeats = 0;
    flights[flightCount++] = f;
    saveToFile();
    printf("\nFlight Added Successfully!\n");
}

void viewFlights() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }
    printf("\nList of Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("%d. %s -> %s | Time: %s | Seats: %d/%d | Fare: Rs.%.2f\n",
               i + 1,
               flights[i].flightNumber,
               flights[i].destination,
               flights[i].departureTime,
               flights[i].bookedSeats,
               flights[i].totalSeats,
               flights[i].fare);
    }
}

void bookFlight() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number to Book: ");
    scanf("%9s", flightNum);

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0)
            found = i;
    }

    if (found == -1) {
        printf("\nFlight not found!\n");
        return;
    }

    struct Flight *f = &flights[found];
    if (f->bookedSeats >= f->totalSeats) {
        printf("\nSorry, this flight is fully booked!\n");
        return;
    }

    struct Passenger p;
    clearBuffer();
    printf("Enter Your Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Seat Number: ");
    scanf("%9s", p.seat);

    f->passengers[f->bookedSeats++] = p;
    saveToFile();

    printf("\nFlight booked successfully!\n");
    printf("Amount to Pay: Rs.%.2f\n", f->fare);
}

void deleteFlight() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number to Delete: ");
    scanf("%9s", flightNum);

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0)
            found = i;
    }

    if (found == -1) {
        printf("\nFlight not found!\n");
        return;
    }

    for (int i = found; i < flightCount - 1; i++) {
        flights[i] = flights[i + 1];
    }
    flightCount--;
    saveToFile();
    printf("\nFlight deleted successfully!\n");
}

void showAmount() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number: ");
    scanf("%9s", flightNum);

    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) {
            printf("\nFare for Flight %s -> Rs.%.2f per ticket\n", flights[i].flightNumber, flights[i].fare);
            return;
        }
    }
    printf("\nFlight not found.\n");
}

void payment() {
    printf("\nPayment Successful\nThank you for choosing our Airline!\n");
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n============================\n");
        printf("  Admin Panel\n");
        printf("============================\n");
        printf("1. Add Flight\n");
        printf("2. View Flights\n");
        printf("3. Mark Attendance\n");
        printf("4. View Passengers\n");
        printf("5. Search Flight\n");
        printf("6. Delete Passenger\n");
        printf("7. Delete Flight\n");
        printf("8. Sort Flights by Time\n");
        printf("9. Show Statistics\n");
        printf("10. Show Amount\n");
        printf("11. Payment\n");
        printf("12. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addFlight(); break;
            case 2: viewFlights(); break;
            case 10: showAmount(); break;
            case 11: payment(); break;
            case 12: printf("\nLogging out...\n"); return;
            default: printf("\nInvalid choice.\n");
        }
    }
}

void userMenu() {
    int choice;
    while (1) {
        printf("\n============================\n");
        printf("  User Panel\n");
        printf("============================\n");
        printf("1. View Available Flights\n");
        printf("2. Search Flight\n");
        printf("3. Book Flight\n");
        printf("4. Cancel My Booking\n");
        printf("5. View Amount for Flight\n");
        printf("6. Payment\n");
        printf("7. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewFlights(); break;
            case 3: bookFlight(); break;
            case 5: showAmount(); break;
            case 6: payment(); break;
            case 7: printf("\nLogging out...\n"); return;
            default: printf("\nInvalid choice.\n");
        }
    }
}
