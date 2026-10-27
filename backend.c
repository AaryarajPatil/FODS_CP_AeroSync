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
    
    
    if (fread(&flightCount, sizeof(int), 1, fp) != 1) {
        flightCount = 0;
        fclose(fp);
        return;
    }
    
    
    if (flightCount > MAX_FLIGHTS) {
        flightCount = MAX_FLIGHTS;
    }
    
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
    if (scanf("%9s", f.flightNumber) != 1) {
        printf("Error reading flight number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Destination: ");
    if (fgets(f.destination, sizeof(f.destination), stdin) == NULL) {
        printf("Error reading destination.\n");
        return;
    }
    f.destination[strcspn(f.destination, "\n")] = 0;

    printf("Enter Departure Time: ");
    if (scanf("%19s", f.departureTime) != 1) {
        printf("Error reading departure time.\n");
        clearBuffer();
        return;
    }

    printf("Enter Total Seats: ");
    if (scanf("%d", &f.totalSeats) != 1) {
        printf("Error reading total seats.\n");
        clearBuffer();
        return;
    }

    
    if (f.totalSeats <= 0 || f.totalSeats > MAX_PASSENGERS) {
        printf("Invalid number of seats. Must be between 1 and %d.\n", MAX_PASSENGERS);
        clearBuffer();
        return;
    }

    f.bookedSeats = 0;
    flights[flightCount++] = f;
    saveToFile();

    printf("\nFlight Added Successfully\n");
}

void viewFlights() {
    if (flightCount == 0) {
        printf("\nNo flights available\n");
        return;
    }

    printf("\nList of Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("%d. Flight %s -> %s | Time: %s | Seats: %d/%d\n",
               i + 1,
               flights[i].flightNumber,
               flights[i].destination,
               flights[i].departureTime,
               flights[i].bookedSeats,
               flights[i].totalSeats);
    }
}

void markAttendance() {
    if (flightCount == 0) {
        printf("\nNo flights available. Please add a flight first.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number: ");
    if (scanf("%9s", flightNum) != 1) {
        printf("Error reading flight number.\n");
        clearBuffer();
        return;
    }

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nFlight not found\n");
        return;
    }

    struct Flight *f = &flights[found];
    if (f->bookedSeats >= f->totalSeats) {
        printf("\nNo available seats\n");
        return;
    }

    struct Passenger p;
    clearBuffer();

    printf("\nEnter Passenger Name: ");
    if (fgets(p.name, sizeof(p.name), stdin) == NULL) {
        printf("Error reading passenger name.\n");
        return;
    }
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    if (scanf("%d", &p.age) != 1) {
        printf("Error reading age.\n");
        clearBuffer();
        return;
    }

    // Validate age
    if (p.age <= 0 || p.age > 120) {
        printf("Invalid age.\n");
        clearBuffer();
        return;
    }

    printf("Enter Seat Number: ");
    if (scanf("%9s", p.seat) != 1) {
        printf("Error reading seat number.\n");
        clearBuffer();
        return;
    }

    f->passengers[f->bookedSeats++] = p;
    saveToFile();

    printf("\nAttendance Marked Successfully\n");
}

void viewPassengers() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number: ");
    if (scanf("%9s", flightNum) != 1) {
        printf("Error reading flight number.\n");
        clearBuffer();
        return;
    }

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nFlight not found\n");
        return;
    }

    struct Flight f = flights[found];
    if (f.bookedSeats == 0) {
        printf("\nNo passengers\n");
        return;
    }

    printf("\nPassengers for Flight %s:\n", f.flightNumber);
    for (int i = 0; i < f.bookedSeats; i++) {
        printf("%d. %s (Age: %d, Seat: %s)\n",
               i + 1,
               f.passengers[i].name,
               f.passengers[i].age,
               f.passengers[i].seat);
    }
}

void searchFlight() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char query[50];
    clearBuffer();

    printf("\nEnter Flight Number or Destination: ");
    if (fgets(query, sizeof(query), stdin) == NULL) {
        printf("Error reading search query.\n");
        return;
    }
    query[strcspn(query, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < flightCount; i++) {
        if (strstr(flights[i].flightNumber, query) != NULL ||
            strstr(flights[i].destination, query) != NULL) {
            printf("%s -> %s | Time: %s | Seats: %d/%d\n",
                   flights[i].flightNumber,
                   flights[i].destination,
                   flights[i].departureTime,
                   flights[i].bookedSeats,
                   flights[i].totalSeats);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo matching flights found\n");
    }
}

void deleteFlight() {
    if (flightCount == 0) {
        printf("\nNo flights available to delete.\n");
        return;
    }

    char flightNum[10];
    printf("\nEnter Flight Number to Delete: ");
    if (scanf("%9s", flightNum) != 1) {
        printf("Error reading flight number.\n");
        clearBuffer();
        return;
    }

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nFlight not found\n");
        return;
    }

    for (int i = found; i < flightCount - 1; i++) {
        flights[i] = flights[i + 1];
    }

    flightCount--;
    saveToFile();

    printf("\nFlight deleted successfully\n");
}

void cancelPassenger() {
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    char flightNum[10], name[50];

    printf("\nEnter Flight Number: ");
    if (scanf("%9s", flightNum) != 1) {
        printf("Error reading flight number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Passenger Name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Error reading passenger name.\n");
        return;
    }
    name[strcspn(name, "\n")] = 0;

    int found = -1;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nFlight not found\n");
        return;
    }

    struct Flight *f = &flights[found];
    int index = -1;
    for (int j = 0; j < f->bookedSeats; j++) {
        if (strcmp(f->passengers[j].name, name) == 0) {
            index = j;
            break;
        }
    }

    if (index == -1) {
        printf("\nPassenger not found\n");
        return;
    }

    for (int j = index; j < f->bookedSeats - 1; j++) {
        f->passengers[j] = f->passengers[j + 1];
    }

    f->bookedSeats--;
    saveToFile();

    printf("\nPassenger cancelled successfully\n");
}

void sortFlightsByTime() {
    if (flightCount == 0) {
        printf("\nNo flights available to sort.\n");
        return;
    }

    for (int i = 0; i < flightCount - 1; i++) {
        for (int j = i + 1; j < flightCount; j++) {
            if (strcmp(flights[i].departureTime, flights[j].departureTime) > 0) {
                struct Flight temp = flights[i];
                flights[i] = flights[j];
                flights[j] = temp;
            }
        }
    }
    printf("\nFlights sorted by time\n");
}

void showStatistics() {
    if (flightCount == 0) {
        printf("\nNo flights available\n");
        return;
    }

    printf("\nFlight Statistics:\n");
    for (int i = 0; i < flightCount; i++) {
        float percent = (flights[i].bookedSeats * 100.0f) / flights[i].totalSeats;
        printf("%s -> %s | %.2f%% Seats Filled\n",
               flights[i].flightNumber,
               flights[i].destination,
               percent);
    }
}
