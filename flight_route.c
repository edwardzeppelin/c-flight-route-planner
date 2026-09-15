#define _CRT_SECURE_NO_WARNINGS //visual studio disable warnings

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include <malloc.h>

struct Flight {
    char flightNumber[10];
    char departureAirport[10]; // код IATA
    char arrivalAirport[10]; // код IATA
    struct tm departureTime;
    struct tm arrivalTime;
    double ticketPrice; // в долларах США
};

void inputflight(struct Flight* flight);

void printflight(struct Flight* flights, int numFlights, const char* flightName);

void editflight(struct Flight* flights, int numFlights, const char* flightName);

void deleteflight(struct Flight* flights, int* numFlights, const char* flightName);

void printallflights(struct Flight* flights, int numFlights);

void findcheapestroute(struct Flight* flights, int numFlights, const char* departureAirport, const char* arrivalAirport);

void findshortestwait(struct Flight* flights, int numFlights, const char* departureAirport, const char* arrivalAirport);

void loadflights(struct Flight** flights, int* numFlights);

void saveflights(struct Flight* flights, int numFlights);

int main()
{

    struct Flight* flights = NULL;
    int numFlights = 0;

    loadflights(&flights, &numFlights);

    int choice;

    while (1)
    {
        printf("-------------------------------------------------------------\n");
        printf("Menu:\n");
        printf("1. Add flight\n");
        printf("2. Edit flight\n");
        printf("3. Show flight\n");
        printf("4. Delete flight\n");
        printf("5. Search the fastest route\n");
        printf("6. Search the cheapest route\n");
        printf("7. Show all flights\n");
        printf("8. Save and Exit\n");
        printf("-------------------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("-------------------------------------------------------------\n");

        switch (choice)
        {
        case 1:
            printf("Adding new flight...\n");
            flights = (struct Flight*)realloc(flights, (numFlights + 1) * sizeof(struct Flight));
            inputflight(&flights[numFlights]);
            numFlights++;
            break;
        case 2:
            printf("Enter name of flight to edit: ");
            char flightToEdit[10];
            scanf("%s", flightToEdit);
            editflight(flights, numFlights, flightToEdit);
            break;
        case 3:
            printf("Enter name of flight: ");
            char flightName[10];
            scanf("%s", flightName);
            printflight(flights, numFlights, flightName);
            break;
        case 4:
            printf("Enter name of flight to delete: ");
            char flightToDelete[10];
            scanf("%s", flightToDelete);
            deleteflight(flights, &numFlights, flightToDelete);
            break;
        case 5:
            printf("Enter departure airport code: ");
            char departureAirport[10];
            scanf("%s", departureAirport);

            printf("Enter arrival airport code: ");
            char arrivalAirport[10];
            scanf("%s", arrivalAirport);

            printf("-------------------------------------------------------------\n");

            findshortestwait(flights, numFlights, departureAirport, arrivalAirport);
            break;
        case 6:
            printf("Enter departure airport: ");
            char departureAirport1[10];
            scanf("%s", departureAirport1);

            printf("Enter arrival airport: ");
            char arrivalAirport1[10];
            scanf("%s", arrivalAirport1);

            printf("-------------------------------------------------------------\n");

            findcheapestroute(flights, numFlights, departureAirport1, arrivalAirport1);

            break;
        case 7:
            printallflights(flights, numFlights);
            break;
        case 8:
            saveflights(flights, numFlights);
            return 0;
        default:
            printf("No such function. Try again\n");
        }
    }
    free(flights);
    return 0;
}

void inputflight(struct Flight* flight)
{
    printf("Enter number of flight: ");
    scanf("%s", flight->flightNumber);

    printf("Enter departure airport: ");
    scanf("%s", flight->departureAirport);

    printf("Enter arrival airport: ");
    scanf("%s", flight->arrivalAirport);

    int temphour = 0, tempmin = 0;

    while (1) {
        printf("Enter departure time (HH:MM): ");
        scanf("%d:%d", &temphour, &tempmin);
        if (temphour > 23 || tempmin > 59) {
            printf("Try again\n");
        }
        else {
            flight->departureTime.tm_hour = temphour;
            flight->departureTime.tm_min = tempmin;
            break;
        }
    }

    temphour = tempmin = 0;

    while (1) {
        printf("Enter arrival time (HH:MM): ");
        scanf("%d:%d", &temphour, &tempmin);
        if (temphour > 23 || tempmin > 59) {
            printf("Try again\n");
        }
        else {
            flight->arrivalTime.tm_hour = temphour;
            flight->arrivalTime.tm_min = tempmin;
            break;
        }
    }

    printf("Enter cost of ticket in USD: ");
    scanf("%lf", &flight->ticketPrice);

    printf("Flight has been added.\n");

    return;
}

void printflight(struct Flight* flights, int numFlights, const char* flightName) {
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].flightNumber, flightName) == 0) {
            printf("Flight %s:\n", flightName);
            printf("Departure airport: %s\n", flights[i].departureAirport);
            printf("Arrival airport: %s\n", flights[i].arrivalAirport);
            printf("Departure time : %02d:%02d\n", flights[i].departureTime.tm_hour, flights[i].departureTime.tm_min);
            printf("Arrival time : %02d:%02d\n", flights[i].arrivalTime.tm_hour, flights[i].arrivalTime.tm_min);
            printf("Cost of ticket: %.2f USD\n", flights[i].ticketPrice);
            return;
        }
    }
    printf("No such flight %s.\n", flightName);
}

void editflight(struct Flight* flights, int numFlights, const char* flightName) {
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].flightNumber, flightName) == 0) {
            printf("Editing flight %s:\n", flightName);

            printf("Enter new departure airport: ");
            scanf("%s", flights[i].departureAirport);

            printf("Enter new arrival airport: ");
            scanf("%s", flights[i].arrivalAirport);

            int temphour = 0, tempmin = 0;

            while (1) {
                printf("Enter new departure time (HH:MM): ");
                scanf("%d:%d", &temphour, &tempmin);
                if (temphour > 23 || tempmin > 59) {
                    printf("Try again\n");
                }
                else {
                    flights[i].departureTime.tm_hour = temphour;
                    flights[i].departureTime.tm_min = tempmin;
                    break;
                }
            }

            temphour = tempmin = 0;

            while (1) {
                printf("Enter new arrival time (HH:MM): ");
                scanf("%d:%d", &temphour, &tempmin);
                if (temphour > 23 || tempmin > 59) {
                    printf("Try again\n");
                }
                else {
                    flights[i].arrivalTime.tm_hour = temphour;
                    flights[i].arrivalTime.tm_min = tempmin;
                    break;
                }
            }

            printf("Enter new cost of ticket in USD: ");
            scanf("%lf", &flights[i].ticketPrice);

            printf("Flight %s has been edited.\n", flightName);
            return;
        }
    }
    printf("No such flight %s.\n", flightName);
}

void deleteflight(struct Flight* flights, int* numFlights, const char* flightName) {
    int found = 0;

    for (int i = 0; i < *numFlights; i++) {
        if (strcmp(flights[i].flightNumber, flightName) == 0) {
            found = 1;
            printf("Deleting flight %s...\n", flightName);

            for (int j = i; j < (*numFlights - 1); j++) {
                flights[j] = flights[j + 1];
            }
            (*numFlights)--;

            printf("Flight %s has been deleted.\n", flightName);
            break;
        }
    }

    if (!found) {
        printf("No such flight %s.\n", flightName);
    }
}

void printallflights(struct Flight* flights, int numFlights)
{
    printf("All Flight Names:\n");
    for (int i = 0; i < numFlights; i++)
    {
        printf("%s\n", flights[i].flightNumber);
    }
}

void findcheapestroute(struct Flight* flights, int numFlights, const char* departureAirport, const char* arrivalAirport) {
    double cheapestPrice = DBL_MAX;
    struct Flight cheapestFlight1, cheapestFlight2;

    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].departureAirport, departureAirport) == 0 && strcmp(flights[i].arrivalAirport, arrivalAirport) != 0) {
            for (int j = 0; j < numFlights; j++) {
                if (strcmp(flights[j].departureAirport, flights[i].arrivalAirport) == 0 && strcmp(flights[j].arrivalAirport, arrivalAirport) == 0) {
                    double totalCost = flights[i].ticketPrice + flights[j].ticketPrice;
                    if (totalCost < cheapestPrice) {
                        cheapestPrice = totalCost;
                        cheapestFlight1 = flights[i];
                        cheapestFlight2 = flights[j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].departureAirport, departureAirport) == 0 && strcmp(flights[i].arrivalAirport, arrivalAirport) == 0) {
            if (flights[i].ticketPrice < cheapestPrice) {
                cheapestPrice = flights[i].ticketPrice;
                cheapestFlight1 = flights[i];
                cheapestFlight2 = flights[i];
            }
        }
    }

    if (cheapestPrice != DBL_MAX) {
        printf("Cheapest route:\n");
        printf("\nFirst flight:\n");
        printflight(&cheapestFlight1, 1, cheapestFlight1.flightNumber);
        if (cheapestFlight1.ticketPrice != cheapestFlight2.ticketPrice) {
            printf("\nSecond flight:\n");
            printflight(&cheapestFlight2, 1, cheapestFlight2.flightNumber);
        }
        printf("\nTotal cost: %.2f USD\n", cheapestPrice);
    }
    else {
        printf("Route doesn't found\n");
    }
}

void findshortestwait(struct Flight* flights, int numFlights, const char* departureAirport, const char* arrivalAirport) {
    int minLayoverTime = INT_MAX;
    struct Flight shortestLayoverFlight1, shortestLayoverFlight2;

    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].departureAirport, departureAirport) == 0 && strcmp(flights[i].arrivalAirport, arrivalAirport) != 0) {
            for (int j = 0; j < numFlights; j++) {
                if (strcmp(flights[j].departureAirport, flights[i].arrivalAirport) == 0 && strcmp(flights[j].arrivalAirport, arrivalAirport) == 0) {
                    int layoverTime = (flights[j].departureTime.tm_hour - flights[i].arrivalTime.tm_hour) * 60 + (flights[j].departureTime.tm_min - flights[i].arrivalTime.tm_min);
                    if (layoverTime < minLayoverTime) {
                        minLayoverTime = layoverTime;
                        shortestLayoverFlight1 = flights[i];
                        shortestLayoverFlight2 = flights[j];
                    }
                }
            }
        }
    }

    if (minLayoverTime != INT_MAX) {
        printf("Route with the shortest layover time:\n");
        printf("\nFirst flight:\n");
        printflight(&shortestLayoverFlight1, 1, shortestLayoverFlight1.flightNumber);
        printf("\nSecond flight:\n");
        printflight(&shortestLayoverFlight2, 1, shortestLayoverFlight2.flightNumber);
        printf("\nLayover time: %d minutes\n", minLayoverTime);
    }
    else {
        printf("Route doesn't found\n");
    }
}

void loadflights(struct Flight** flights, int* numFlights) {
    FILE* file = fopen("flights.dat", "rb");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Flight flight;
    size_t size = sizeof(struct Flight);

    *numFlights = 0;

    struct Flight* temp = NULL;

    while (fread(&flight, size, 1, file) == 1) {
        temp = realloc(*flights, (*numFlights + 1) * sizeof(struct Flight));
        if (!temp) {
            printf("Memory allocation error.\n");
            fclose(file);
            return;
        }

        *flights = temp;
        (*flights)[*numFlights] = flight;
        (*numFlights)++;
    }

    fclose(file);
}

void saveflights(struct Flight* flights, int numFlights) {
    FILE* file = fopen("flights.dat", "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    size_t size = sizeof(struct Flight);

    for (int i = 0; i < numFlights; i++) {
        fwrite(&(flights)[i], size, 1, file);
    }

    fclose(file);
}