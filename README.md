# AeroSync - Flight Attendance and Booking Management System

AeroSync is a flight management system developed in C with a web-based dashboard. It supports flight scheduling, passenger booking, attendance tracking, and seat availability management.

## Features

- Add, view, search, sort, and cancel flights
- Book seats and calculate fares
- Separate admin and user portals
- Track passenger attendance and view passenger manifests
- Calculate flight occupancy
- Save and restore flight data
- Web dashboard with booking and occupancy information

## Tech Stack

- **Backend:** C (C99/C11)
- **Frontend:** HTML, CSS, JavaScript
- **APIs:** WebRTC and Canvas API
- **Tools:** GCC / MinGW or Clang

## Getting Started

### Prerequisites

Install GCC, MinGW, or Clang.

### Compile and Run

Compile the backend from the project directory:

```bash
gcc -O2 backend.c -o backend
./backend
```

For the second backend version:

```bash
gcc -O2 backend2.c -o backend2
./backend2
```

On Windows, run the generated executable, such as `backend2.exe`.

To launch the dashboard, open the frontend HTML file in a browser. Alternatively, start a local server:

```bash
python -m http.server 8000
```

Then visit `http://localhost:8000`.

## Authors

- [Aaryaraj Patil](https://github.com/AaryarajPatil)
- [Tirtha Patil](https://github.com/tirtha-patil)

