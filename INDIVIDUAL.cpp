#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Node structure for a patient
struct PatientNode {
    int patientID;
    string patientName;
    int age;
    string disease;
    int priority;
    PatientNode* next;
};

// Priority Queue class
class PriorityQueue {
private:
    PatientNode* front;
    PatientNode* rear;
    int count;

public:
    // Constructor
    PriorityQueue() {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Add patient according to priority
    void Add(int id, string name, int patientAge,
             string patientDisease, int patientPriority) {

        PatientNode* patient = new PatientNode;

        patient->patientID = id;
        patient->patientName = name;
        patient->age = patientAge;
        patient->disease = patientDisease;
        patient->priority = patientPriority;
        patient->next = NULL;

        // If queue is empty
        if (front == NULL) {
            front = patient;
            rear = patient;
        }
        // If new patient has higher priority
        else if (patientPriority < front->priority) {
            patient->next = front;
            front = patient;
        }
        // Insert at the correct position
        else {
            PatientNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= patientPriority) {
                current = current->next;
            }

            patient->next = current->next;
            current->next = patient;

            if (patient->next == NULL) {
                rear = patient;
            }
        }

        count++;
        cout << "Patient added successfully!\n";
    }

    // Remove and process highest-priority patient
    void Remove() {
        if (front == NULL) {
            cout << "No patients waiting in the queue.\n";
            return;
        }

        PatientNode* temp = front;

        cout << "\n===== Patient Being Processed =====\n";
        cout << "Patient ID: " << temp->patientID << "\n";
        cout << "Patient Name: " << temp->patientName << "\n";
        cout << "Age: " << temp->age << "\n";
        cout << "Disease: " << temp->disease << "\n";
        cout << "Priority: " << temp->priority << "\n";

        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;
        count--;

        cout << "Patient removed from waiting queue.\n";
    }

    // Check whether queue is empty
    bool IsEmpty() {
        return front == NULL;
    }

    // Check whether queue is not empty
    bool IsNotEmpty() {
        return front != NULL;
    }

    // Display all waiting patients
    void PrintQueue() {
        if (IsEmpty()) {
            cout << "No patients waiting in the queue.\n";
            return;
        }

        PatientNode* current = front;

        cout << "\n===== Hospital Waiting Queue =====\n";

        while (current != NULL) {
            cout << "\nPatient ID: " << current->patientID << "\n";
            cout << "Patient Name: " << current->patientName << "\n";
            cout << "Age: " << current->age << "\n";
            cout << "Disease: " << current->disease << "\n";
            cout << "Priority: " << current->priority << "\n";
            cout << "-----------------------------\n";

            current = current->next;
        }
    }

    // Display queue status
    void QueueStatus() {
        if (IsEmpty()) {
            cout << "Queue Status: Empty\n";
        }
        else {
            cout << "Queue Status: Not Empty\n";
            cout << "Patients Waiting: " << count << "\n";
        }
    }

    // Destructor to release memory
    ~PriorityQueue() {
        while (front != NULL) {
            PatientNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }
};

// Read integer input safely
bool ReadInteger(const string& message, int& value) {
    cout << message;

    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return false;
    }

    return true;
}

int main() {
    PriorityQueue hospital;
    int choice = 0;

    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Process Highest-Priority Patient\n";
        cout << "3. Display All Waiting Patients\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";

        if (!ReadInteger("Enter your choice: ", choice)) {
            continue;
        }

        switch (choice) {
            case 1: {
                int id, age, priority;
                string name, disease;

                if (!ReadInteger("Enter Patient ID: ", id)) {
                    break;
                }

                cout << "Enter Patient Name: ";
                getline(cin >> ws, name);

                if (!ReadInteger("Enter Patient Age: ", age)) {
                    break;
                }

                if (age < 0 || age > 130) {
                    cout << "Please enter a valid age.\n";
                    break;
                }

                cout << "Enter Disease or Complaint: ";
                getline(cin >> ws, disease);

                if (!ReadInteger(
                    "Enter Priority (1=Urgent, 2=Regular, 3=Low): ",
                    priority)) {
                    break;
                }

                if (priority < 1 || priority > 3) {
                    cout << "Invalid priority. Enter 1, 2, or 3.\n";
                    break;
                }

                hospital.Add(id, name, age, disease, priority);
                break;
            }

            case 2:
                hospital.Remove();
                break;

            case 3:
                hospital.PrintQueue();
                break;

            case 4:
                hospital.QueueStatus();
                break;

            case 5:
                cout << "Exiting Hospital Management System.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
