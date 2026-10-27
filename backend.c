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
