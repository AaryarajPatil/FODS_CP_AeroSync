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
