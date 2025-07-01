#ifndef PATIENT_INTERFACE_H
#define PATIENT_INTERFACE_H

#include "Patient.h"
#include <vector>

class PatientInterface {
public:
    static Patient* registerPatient(int idCounter);
};

#endif
