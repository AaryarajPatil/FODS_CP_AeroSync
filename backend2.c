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
