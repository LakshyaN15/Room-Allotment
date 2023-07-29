#include <iostream>
#include <vector>
#include<limits>
#include <unordered_map>
using namespace std;

class Room {
public:
    string roomNumber;
    string host;
    string startTime;
    string endTime;
    unordered_map<int, string> chairBookings;

    Room(const string& roomNumber, const string& host, const string& startTime, const string& endTime)
        : roomNumber(roomNumber), host(host), startTime(startTime), endTime(endTime) {}

    void ReserveChair(int chairNumber, const string& travelerName) {
        chairBookings[chairNumber] = travelerName;
    }

    void ReleaseChair(int chairNumber) {
        chairBookings.erase(chairNumber);
    }

    bool IsChairAvailable(int chairNumber) const {
        return chairBookings.find(chairNumber) == chairBookings.end();
    }

    bool IsRoomAvailable() const {
        return chairBookings.size() < MaxCapacity();
    }

    int MaxCapacity() const {
        return 40; // Maximum number of chairs in a room
    }

    void Display() const {
        cout << "Room Number: " << roomNumber << "\n"
                  << "Host: " << host << "\n"
                  << "Start Time: " << startTime << "\n"
                  << "End Time: " << endTime << "\n"
                  << "Chair Bookings:\n";
        for (const auto& booking : chairBookings) {
            cout << "Chair " << booking.first << ": " << booking.second << "\n";
        }
        cout << "-----------------------------------\n";
    }
};

class RoomBookingSystem {
private:
    vector<Room> rooms;

public:
    void AddRoom(const string& roomNumber, const string& host, const string& startTime, const string& endTime) {
        Room room(roomNumber, host, startTime, endTime);
        rooms.push_back(room);
    }

    Room* FindRoom(const string& roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                return &room;
            }
        }
        return nullptr;
    }

    void BookRoom(const string& roomNumber, const string& travelerName, int chairNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            if (room->IsChairAvailable(chairNumber)) {
                room->ReserveChair(chairNumber, travelerName);
                cout << "Chair " << chairNumber << " has been booked for " << travelerName << "\n";
            } else {
                cout << "The chair " << chairNumber << " is already reserved\n";
            }
        } else {
            cout << "Room " << roomNumber << " not found\n";
        }
    }

    void ReleaseRoom(const string& roomNumber, int chairNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            if (!room->IsChairAvailable(chairNumber)) {
                room->ReleaseChair(chairNumber);
                cout << "Chair " << chairNumber << " has been released\n";
            } else {
                cout << "The chair " << chairNumber << " is not reserved\n";
            }
        } else {
            cout << "Room " << roomNumber << " not found\n";
        }
    }

    void DisplayRoom(const string& roomNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            room->Display();
        } else {
            cout << "Room " << roomNumber << " not found\n";
        }
    }

    void DisplayAllRooms() {
        for (const auto& room : rooms) {
            room.Display();
        }
    }
};

int main() {
    RoomBookingSystem bookingSystem;

    while (true) {
        cout << "---------- Room Booking System ----------\n";
        cout << "1. Add Room\n";
        cout << "2. Book Room\n";
        cout << "3. Release Room\n";
        cout << "4. Display Room\n";
        cout << "5. Display All Rooms\n";
        cout << "6. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string roomNumber, host, startTime, endTime, travelerName;
        int chairNumber;

        switch (choice) {
            case 1:
                cout << "Enter Room Number: ";
                getline(cin, roomNumber);

                cout << "Enter Host: ";
                getline(cin, host);

                cout << "Enter Start Time: ";
                getline(cin, startTime);

                cout << "Enter End Time: ";
                getline(cin, endTime);

                bookingSystem.AddRoom(roomNumber, host, startTime, endTime);
                cout << "Room " << roomNumber << " added successfully\n";
                break;

            case 2:
                cout << "Enter Room Number: ";
                getline(cin, roomNumber);

                cout << "Enter Traveler Name: ";
                getline(cin, travelerName);

                cout << "Enter Chair Number: ";
                cin >> chairNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bookingSystem.BookRoom(roomNumber, travelerName, chairNumber);
                break;

            case 3:
                cout << "Enter Room Number: ";
                getline(cin, roomNumber);

                cout << "Enter Chair Number: ";
                cin >> chairNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bookingSystem.ReleaseRoom(roomNumber, chairNumber);
                break;

            case 4:
                cout << "Enter Room Number: ";
                getline(cin, roomNumber);

                bookingSystem.DisplayRoom(roomNumber);
                break;

            case 5:
                bookingSystem.DisplayAllRooms();
                break;

            case 6:
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "\n";
    }
}


