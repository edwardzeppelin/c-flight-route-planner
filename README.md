# Flight Route Planner & Search System

A C terminal application for managing flight schedules, persisting flight data to binary files, and finding optimal direct or connecting routes based on price or layover time.

## Features

* **Flight Data Management**: Add, edit, display, and delete individual flight records.
* **Cheapest Route Finder**: Computes the lowest total price for both direct flights and 1-stop connecting routes between specified airports.
* **Shortest Layover Finder**: Finds connecting routes with the minimum wait time between flights.
* **Binary File Persistence**: Automatically loads existing records from `flights.dat` on startup and saves changes upon exit.

## Data Structure

| Field | Type | Description |
| :--- | :--- | :--- |
| `flightNumber` | `char[10]` | Flight identifier code |
| `departureAirport` | `char[10]` | Departure IATA airport code |
| `arrivalAirport` | `char[10]` | Arrival IATA airport code |
| `departureTime` | `struct tm` | Departure time formatted as HH:MM |
| `arrivalTime` | `struct tm` | Arrival time formatted as HH:MM |
| `ticketPrice` | `double` | Cost of ticket in USD |

## Menu Options

1. **Add flight**: Prompt for flight attributes and store in dynamic memory.
2. **Edit flight**: Update details of an existing flight by flight number.
3. **Show flight**: Display detailed information for a specific flight.
4. **Delete flight**: Remove a flight record and reallocate memory.
5. **Search the fastest route**: Calculate the connecting route with shortest wait time.
6. **Search the cheapest route**: Locate the cheapest direct or 1-stop route.
7. **Show all flights**: Print list of all flight numbers.
8. **Save and Exit**: Write database to `flights.dat` and terminate.

## Building & Running

### Compilation
Compile the project using standard C compilers (such as GCC):

```bash
gcc -O2 flight_route.c -o flight_planner
