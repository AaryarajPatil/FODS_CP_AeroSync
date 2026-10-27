# ✈️ AeroSync — Flight Attendance & Booking Management System

[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform: Windows / Linux](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)]()
[![Status: In Development](https://img.shields.io/badge/Status-Active%20Development-success.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**AeroSync** is a lightweight, high-performance airline flight scheduling, passenger attendance tracking, and seat allocation management system built for academic and practical airline management applications.

---

## 📌 Project Overview

Managing flight schedules, tracking passenger boarding attendance, and optimizing cabin occupancy are core challenges in aviation operations. **AeroSync** addresses these workflows through a high-performance C-based operational core paired with an intuitive interface.

Key highlights:
- **Fast In-Memory Architecture**: Rapid lookup, updates, and manifest rendering.
- **Binary Persistence**: Real-time synchronization of flight schedules and passenger manifests to disk (`flights.txt`).
- **Data Structure Optimization**: Efficient array compaction algorithms for passenger cancellations and schedule re-indexing.
- **Attendance & Manifest Audit**: Real-time gate check-in and seat availability verification.

---

## 🗺️ 3-Day Development Roadmap

| Phase | Milestone | Focus Area | Status |
| :--- | :--- | :--- | :--- |
| **Day 1** | **Core Architecture & C Engine** | Project scaffold, core data structures, binary persistence layer, flight scheduling CRUD, passenger attendance marking, sorting, and analytics. | ✅ **Completed** |
| **Day 2** | **Role-Based Portals & Commercial Engine** | Admin vs User authentication gating, commercial seat reservation, dynamic fare calculation, and simulated digital payments. | ✅ **Completed** |
| **Day 3** | **Interactive Web Dashboard & Integrations** | Modern glassmorphism UI, simulated boarding pass QR camera scanner, visual occupancy analytics, and full integration. | 🔄 **Next Up** |

---

## 🏗️ System Architecture & Data Model

AeroSync operates using structured relational memory records:

```text
+-----------------------------------------------------------+
|                       struct Flight                       |
+-----------------------------------------------------------+
| - flightNumber   : char[10]                               |
| - destination    : char[50]                               |
| - departureTime  : char[20]                               |
| - totalSeats     : int                                    |
| - bookedSeats    : int                                    |
| - fare           : float                                  |
| - passengers[]   : struct Passenger[MAX_PASSENGERS]       |
+-----------------------------+-----------------------------+
                              | 1..*
+-----------------------------v-----------------------------+
|                      struct Passenger                     |
+-----------------------------------------------------------+
| - name           : char[50]                               |
| - age            : int                                    |
| - seat           : char[10]                               |
+-----------------------------------------------------------+
```

---

## 🚀 Core Features (Day 1 & Day 2 Releases)

1. **Flight Scheduling**: Add scheduled flights with unique identifiers, destinations, departure timestamps, seating capacities, and fare pricing.
2. **Flight Schedule Browser**: View all available and active flights in formatted tabular views with fares.
3. **Role-Based Portals (RBAC)**: Password-protected Admin Panel (`admin123`) and self-service User Portal.
4. **Commercial Seat Booking**: End-to-end flight booking with real-time seat decrementation and fare estimation.
5. **Billing & Fare Lookup**: Instant ticket pricing query and payment confirmation simulation.
6. **Passenger Attendance Tracking**: Mark gate attendance and record passenger details with instant verification.
7. **Passenger Manifest Inspection**: Print full passenger manifests for any scheduled flight.
8. **Search Engine**: Search flights dynamically using flight numbers or destination keywords.
9. **Cancellation & Compaction**: Delete flights or cancel passenger bookings with in-memory array compaction.
10. **Temporal Sorting**: Chronologically sort flight schedules using departure time comparisons.
11. **Real-time Occupancy Analytics**: Calculate and report capacity percentage utilization across all active flights.
12. **Binary File Storage**: Automatically save and restore state from binary storage on startup and shutdown.

---

## 💻 Compilation & Execution

### Prerequisites
- GCC / MinGW or Clang compiler
- Standard C library (`stdio.h`, `stdlib.h`, `string.h`)

### Build with GCC
```bash
# Compile the Day 1 CLI backend
gcc -O2 backend.c -o backend.exe

# Compile the Day 2 Commercial & RBAC backend
gcc -O2 backend2.c -o backend2.exe

# Run the executable (Windows)
.\backend2.exe

# Run on Linux / macOS
./backend2
```

---

## 🛠️ Tech Stack
- **Core Engine:** C (C99/C11 standard)
- **Data Persistence:** Binary I/O streams
- **Frontend Dashboard:** HTML5, CSS3, JavaScript *(Releasing Day 3)*

---

## 👤 Authors
Developed by **Aaryaraj Patil** & **Tirtha Patil**  
- Aaryaraj: [@AaryarajPatil](https://github.com/AaryarajPatil)  
- Tirtha: [github.com/tirtha-patil](https://github.com/tirtha-patil)
