#include <iostream>
#include <string>
using namespace std;


struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};


void bookTicket(int seats[], int totalSeats, Passenger*& head);
void cancelTicket(int seats[], int totalSeats, Passenger*& head);
void viewTrainStatus(int seats[], int totalSeats);
void viewPassengerList(Passenger* head);
void freeMemory(Passenger*& head);

int main() {
    int totalSeats = 30;
    int* seats = new int[totalSeats]; // Dynamic array for seat status
    for (int i = 0; i < totalSeats; i++)
        seats[i] = 0; // 0 = available

    Passenger* head = nullptr; // linked list head

    int choice;
    do {
        cout << "\n===== Railway Reservation System =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookTicket(seats, totalSeats, head); break;
            case 2: cancelTicket(seats, totalSeats, head); break;
            case 3: viewTrainStatus(seats, totalSeats); break;
            case 4: viewPassengerList(head); break;
            case 5: freeMemory(head); delete[] seats; cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}


void bookTicket(int seats[], int totalSeats, Passenger*& head) {
    int seatNo = -1;
    for (int i = 0; i < totalSeats; i++) {
        if (seats[i] == 0) { // available
            seatNo = i + 1;
            seats[i] = 1; // mark as booked
            break;
        }
    }

    if (seatNo == -1) {
        cout << "Sorry, no seats available.\n";
        return;
    }

    Passenger* newPassenger = new Passenger;
    newPassenger->seatNo = seatNo;
    cout << "Enter Name: ";
    cin >> newPassenger->name;
    cout << "Enter Age: ";
    cin >> newPassenger->age;
    cout << "Enter Gender (M/F): ";
    cin >> newPassenger->gender;
    newPassenger->next = nullptr;

    
    if (head == nullptr) {
        head = newPassenger;
    } else {
        Passenger* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newPassenger;
    }

    cout << "Ticket booked! Seat No: " << seatNo << endl;
}

void cancelTicket(int seats[], int totalSeats, Passenger*& head) {
    if (head == nullptr) {
        cout << "No passengers to cancel.\n";
        return;
    }

    int seatNo;
    cout << "Enter Seat No to cancel: ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > totalSeats || seats[seatNo - 1] == 0) {
        cout << "Invalid or unbooked seat number.\n";
        return;
    }

    Passenger* temp = head;
    Passenger* prev = nullptr;

    while (temp != nullptr && temp->seatNo != seatNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Passenger not found.\n";
        return;
    }

    if (prev == nullptr) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }

    seats[seatNo - 1] = 0; // free the seat
    delete temp;

    cout << "Ticket cancelled for Seat No: " << seatNo << endl;
}


void viewTrainStatus(int seats[], int totalSeats) {
    cout << "\n--- Train Status ---\n";
    for (int i = 0; i < totalSeats; i++) {
        cout << "Seat " << (i + 1) << ": " << (seats[i] == 1 ? "Booked" : "Available") << endl;
    }
}


void viewPassengerList(Passenger* head) {
    if (head == nullptr) {
        cout << "No passengers booked.\n";
        return;
    }

    cout << "\n--- Passenger List ---\n";
    Passenger* temp = head;
    while (temp != nullptr) {
        cout << "Seat No: " << temp->seatNo 
             << " | Name: " << temp->name 
             << " | Age: " << temp->age 
             << " | Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}


void freeMemory(Passenger*& head) {
    Passenger* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

return 0;
}
