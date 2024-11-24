 #include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include<limits>
#include<fstream>
#include<iomanip>
using namespace std;
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

// Structure to hold patient details
struct PatientDetails {
string name;
int age;
string medicalHistory;
string emergencyContact;
string primaryDoctor;
float outstandingBalance; // Payment details for the patient
};
// Structure to hold payment details
struct PaymentDetails {
float amount;
string paymentMethod;
};
// Base class for all users
class User {
public:
virtual void login() = 0;
virtual void showMenu() = 0;
};
// Admin class
class Admin : public User {
private:
vector<PatientDetails> patientRecords; // Holds patient records for the admin to view
public:
void login() override {
string id;
cout << "Enter Admin ID (Default: 123): ";
cin >> id;
if (id == "123") {
cout <<GREEN<< "Admin login successful!\n";} else {
cout <<RED<< "Invalid ID!\n";
}
}
void showMenu() override {
int choice;
cout <<RESET<< "\nAdmin Menu:\n";
cout << "1. View All Patient Records\n";
cout << "2. View System Reports\n";
cout << "3. Exit\n";
cout << "Enter your choice: ";
cin >> choice;
switch(choice) {
case 1:
viewAllPatients();
break;
case 2:
cout << "Viewing system reports...\n";
break;
case 3:
cout << "Exiting Admin Menu.\n";
break;
default:
cout << "Invalid choice.\n";
}
}
// Function to add a new patient record
void addPatientRecord(const PatientDetails& patient) {
patientRecords.push_back(patient);
savePatientData(); // Save updated records to file
cout << "Patient record updated for Admin.\n";
}
// Function to view all patient records
 // Function to view all patient records in table format
void viewAllPatients() {
    if (patientRecords.empty()) {
        cout << RED << "No patient records available.\n" << RESET;
        return;
    }

    cout << GREEN << "Viewing all patient records...\n" << RESET;

    // Print table header with column names
    cout << CYAN 
         << setw(20) << left << "Name"
         << setw(5) << "Age"
         << setw(25) << "Medical History"
         << setw(20) << "Emergency Contact"
         << setw(10) << "Balance" 
         << RESET << "\n";

    cout << CYAN << string(80, '-') << RESET << "\n";

    // Print patient details row by row
    for (const auto& patient : patientRecords) {
        cout << setw(20) << left << patient.name
             << setw(5) << patient.age
             << setw(25) << patient.medicalHistory
             << setw(20) << patient.emergencyContact
             << setw(10) << fixed << setprecision(2) << patient.outstandingBalance
             << "\n";
    }

    cout << CYAN << string(80, '-') << RESET << "\n";

}
// Function to load patient data from file
void loadPatientData() {
ifstream file("patients.txt");
if (file.is_open()) {
PatientDetails patient;
while (file >> patient.name >> patient.age >> patient.medicalHistory
>> patient.emergencyContact >> patient.primaryDoctor >>
patient.outstandingBalance) {
patientRecords.push_back(patient);
}
file.close();
} else {
cout<<RED << "Unable to load patient data from file.\n";
}
}
// Function to save patient data to file
void savePatientData() {
ofstream file("patients.txt", ios::trunc);
if (file.is_open()) {
for (const auto& patient : patientRecords) {
file << patient.name << " " << patient.age << " " << patient.medicalHistory
<< " " << patient.emergencyContact << " " << patient.primaryDoctor
<< " " << patient.outstandingBalance << "\n";
}
file.close();
} else {
cout << "Unable to save patient data to file.\n";
}
}
};
// Doctor class
class Doctor : public User {
public:
void login() override {
string id;
cout << "Enter Doctor ID (Default: 123): ";
cin >> id;
if (id == "123") {
cout <<GREEN<< "Doctor login successful!\n";
} else {
cout << "Invalid ID!\n";
}
}
void showMenu() override {
int choice;
cout <<RESET<< "\nDoctor Menu:\n";
cout << "1. View Schedule\n";
cout << "2. Assign Prescription\n";
cout << "3. Exit\n";
cout << "Enter your choice: ";
cin >> choice;
switch(choice) {
case 1:
viewSchedule();
break;
case 2:
cout << "Assigning prescription...\n";
break;
case 3:
cout << "Exiting Doctor Menu.\n";
break;
default:
cout <<RED<< "Invalid choice.\n";
}
}
void viewSchedule() {
    const string daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    const string timeSlots[] = {"9:00 AM - 11:00 AM", "11:30 AM - 1:30 PM", "2:00 PM - 4:00 PM", "4:30 PM - 6:30 PM"};
    const string patientNames[] = {"John Doe", "Alice Smith", "David Johnson", "Emily Davis", "Chris Brown"};

    cout << GREEN << "Doctor's Weekly Schedule:\n" << RESET;
    cout << CYAN
         << setw(15) << left << "Day"
         << setw(25) << "Time Slot"
         << setw(20) << "Patient"
         << RESET << "\n";
    cout << CYAN << string(60, '-') << RESET << "\n";

    // Generate random schedule for each day
    for (const auto& day : daysOfWeek) {
        int timeSlotIndex = rand() % 4; // Random time slot
        int patientIndex = rand() % 5; // Random patient name

        cout << setw(15) << left << day
             << setw(25) << timeSlots[timeSlotIndex]
             << setw(20) << patientNames[patientIndex]
             << "\n";
    }

    cout << CYAN << string(60, '-') << RESET<<"\n";
}
};

// Staff class
class Staff : public User {
public:
void login() override {
string id;
cout << RESET<< "Enter Staff ID (Default: 123): ";
cin >> id;
if (id == "123") {
cout <<GREEN<<"Staff login successful!\n";
} else {
cout <<RED<< "Invalid ID!\n";
}
}
void showMenu() override {
int choice;
cout <<RESET<< "\nStaff Menu:\n";
cout << "1. View Duties\n";
cout << "2. View Attendance\n";
cout << "3. Exit\n";
cout << "Enter your choice: ";
cin >> choice;
switch(choice) {
case 1:
cout << "Viewing duties...\n";
break;
case 2:
cout << "Viewing attendance...\n";
break;
case 3:
cout << "Exiting Staff Menu.\n";
break;
default:
cout <<RED<< "Invalid choice.\n";
}
}
};
// Patient class
class Patient : public User {
public:
PatientDetails details; // Holds patient-specific details
PaymentDetails payment; // Holds payment details
void login() override {
string id;
cout << "Enter Patient ID (Default: 123): ";
cin >> id;
if (id == "123") {
cout << GREEN<<"Patient login successful!\n";
enterDetails(); // Prompt patient to enter details upon successful login
} else {
cout <<RED<< "Invalid ID!\n";
}
}
void showMenu() override {
int choice;
cout << RESET<<"\nPatient Menu:\n";
cout << "1. View Medical Records\n";
cout << "2. View Emergency Contact\n";
cout << "3. View Primary Doctor\n";
cout << "4. Make Payment\n";
cout << "5. Exit\n";
cout << "Enter your choice: ";
cin >> choice;
switch(choice) {
case 1:
cout << "Medical History: " << details.medicalHistory << "\n";
break;
case 2:
cout << "Emergency Contact: " << details.emergencyContact << "\n";
break;
case 3:
cout << "Primary Doctor: " << details.primaryDoctor << "\n";
break;
case 4:
makePayment();
break;
case 5:
cout << "Exiting Patient Menu.\n";
break;
default:
cout << RED<<"Invalid choice.\n";
}
}
void enterDetails() {
cout << RESET<<"Enter Patient Name: ";
cin.ignore();
getline(cin, details.name);
cout << "Enter Age: ";
cin >> details.age;
cin.ignore();
cout << "Enter Medical History: ";
getline(cin, details.medicalHistory);
cout << " Emergency Contact details: ";
getline(cin, details.emergencyContact);
cout << "Primary Doctor details:398479387 ";
getline(cin, details.primaryDoctor);
details.outstandingBalance = 0.0f; // Initialize balance to 0
}
void makePayment() {
float amount;
cout << "Enter payment amount: $";
cin >> amount;
cout << "Enter payment method (Cash/Card): ";
cin >> payment.paymentMethod;
details.outstandingBalance -= amount; // Deduct payment from outstanding balance
cout << "Payment of $" << amount << " received via " << payment.paymentMethod <<"Remaining balance: $" << details.outstandingBalance << "\n";
}
};
// Main function
int main() {
srand(time(0)); // Seed random number generator
int choice;
User* user = nullptr;
Admin admin; // Admin instance to manage patient records
admin.loadPatientData(); // Load patient data from file
Patient patient; // Create a reusable patient instance
while (true) {
cout << MAGENTA<<"\nHospital Management System\n";
cout <<RESET<< "1. Admin Login\n";
cout << "2. Doctor Login\n";
cout << "3. Staff Login\n";
cout << "4. Patient Login\n";
cout << "5. Exit\n";
cout <<RESET<< "Enter your choice: ";
cin >> choice;
switch(choice) {
case 1:
user = &admin;
user->login();
user->showMenu();
break;
case 2:
user = new Doctor();
user->login();
user->showMenu();
delete user;
break;
case 3:
user = new Staff();
user->login();
user->showMenu();
delete user;
break;
case 4:
user = &patient;
user->login();
admin.addPatientRecord(patient.details); // Update admin with patient info
user->showMenu();
break;
case 5:
cout << "Exiting Hospital Management System.\n";
return 0;
default:
cout << "Invalid choice. Please try again.\n";
    }
}
return 0;
}