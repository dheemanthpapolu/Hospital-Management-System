# Hospital Management System

A comprehensive C++-based Hospital Management System that simulates core hospital workflows, including patient registration, triage-based admissions, doctor-patient interaction, and billing. Designed for command-line interaction and structured for modular expansion, this project models realistic administrative and clinical decision-making processes.

---

## Table of Contents

- [Features](#features)
- [System Overview](#system-overview)
- [User Roles](#user-roles)
- [Core Modules](#core-modules)
- [Usage](#usage)
- [Folder Structure](#folder-structure)
- [Design Highlights](#design-highlights)
- [Build Instructions](#build-instructions)
- [Future Work](#future-work)

---

## Features

- Patient registration with medical history and symptoms  
- Emergency score assignment by administrators  
- Triage queue system based on emergency severity  
- Smart doctor allocation based on patient load  
- Doctor-patient interactions: view, add notes, discharge  
- Billing queue generation and final bill processing  
- Departmental bed management  
- Modular, extensible design with clear class responsibilities  

---

## System Overview

The application models a small-scale hospital workflow where patients are first registered and later triaged based on emergency score. Administrators assign these scores, and the system uses a **priority queue** to ensure that patients with higher urgency are admitted first. Upon admission, patients are assigned to doctors with the lowest patient load within the department. Doctors can add notes and discharge patients, who are then routed to billing.

---

## User Roles

1. **Patient**
   - Registers with basic details, past illnesses, and symptoms.
   - Assigned a unique patient ID.

2. **Admin**
   - Assigns emergency scores to newly registered patients.
   - Admits patients based on triage queue.
   - Views available beds and admitted patients.

3. **Doctor**
   - Logs in via ID.
   - Views assigned patients, adds/modifies notes.
   - Marks patients for discharge.

4. **Billing Clerk**
   - Processes discharge bills.
   - Views queue of pending bills.

---

## Core Modules

### `Patient`
- Stores medical data and interaction notes.
- Includes logic for discharge marking, doctor linking, etc.

### `Doctor`
- Handles multiple patients.
- Adds notes, discharges patients, and transfers them to billing.

### `Department`
- Represents individual departments like Cardiology, Neurology.
- Tracks doctors and admitted patients.
- Manages bed availability.

### `Admin`
- Assigns emergency scores and admits patients to departments.
- Uses triage queue (priority-based admission).

### `Billing`
- Maintains billing queue.
- Generates formatted bills on discharge.

### `Hospital`
- Central controller class managing all workflows.
- Interfaces with CLI input and routes control to role-specific modules.

---

## Usage

Upon running the program:

1. The user is asked to select a role.
2. Patients register themselves with basic details.
3. Admins:
   - Assign emergency scores to registered patients.
   - Admit patients based on triage priority.
4. Doctors:
   - Login using IDs.
   - Manage their patient lists (view, note, discharge).
5. Billing Clerks:
   - Process bills of discharged patients.

Each role has a custom CLI menu for interaction.

---

## Folder Structure

```
HospitalProject/
├── include/
│   ├── Patient.h
│   ├── Doctor.h
│   ├── Department.h
│   ├── Admin.h
│   ├── Billing.h
│   └── Hospital.h
├── src/
│   ├── main.cpp
│   ├── Patient.cpp
│   ├── Doctor.cpp
│   ├── Department.cpp
│   ├── Admin.cpp
│   ├── Billing.cpp
│   └── Hospital.cpp
├── README.md
└── hospital.exe (generated)
```

---

## Design Highlights

- **Triage System**: Implemented using a priority queue based on emergency scores. Ensures critical patients are attended to first.
- **Modular Roles**: Each class has a focused responsibility: Patient stores state, Admin makes decisions, Doctor manages treatment, etc.
- **Dynamic Assignment**: Patients are assigned to the doctor with the least load in the selected department.
- **Billing Workflow**: Only patients marked for discharge by doctors are sent to the billing queue, ensuring controlled processing.

---

## Build Instructions

### Requirements:
- C++11 or later
- g++ (MinGW or any GCC-compatible compiler)

### To Compile:
```bash
g++ -Iinclude src/*.cpp -o hospital.exe
```

### To Run:
```bash
./hospital.exe
```

Ensure that all `.cpp` files are inside `src/` and all `.h` files are inside `include/`.

---

## Future Work

- Implement persistent storage using file I/O or database integration.
- Add UI frontend (e.g., Qt or web interface).
- Support scheduling and appointment management.
- Improve discharge summaries and patient report generation.
- Expand to include pharmacy, diagnostics, and insurance modules.

---

## License

This project is open for educational and non-commercial use. Feel free to fork and modify.
