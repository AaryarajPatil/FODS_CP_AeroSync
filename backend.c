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
