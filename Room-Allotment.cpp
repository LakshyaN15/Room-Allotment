#include <iostream>
#include <vector>
#include<limits>
#include <unordered_map>

class Room {
public:
    std::string roomNumber;
    std::string host;
    std::string startTime;
    std::string endTime;
    std::unordered_map<int, std::string> chairBookings;

    Room(const std::string& roomNumber, const std::string& host, const std::string& startTime, const std::string& endTime)
        : roomNumber(roomNumber), host(host), startTime(startTime), endTime(endTime) {}

    void ReserveChair(int chairNumber, const std::string& travelerName) {
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
        std::cout << "Room Number: " << roomNumber << "\n"
                  << "Host: " << host << "\n"
                  << "Start Time: " << startTime << "\n"
                  << "End Time: " << endTime << "\n"
                  << "Chair Bookings:\n";
        for (const auto& booking : chairBookings) {
            std::cout << "Chair " << booking.first << ": " << booking.second << "\n";
        }
        std::cout << "-----------------------------------\n";
    }
};

class RoomBookingSystem {
private:
    std::vector<Room> rooms;

public:
    void AddRoom(const std::string& roomNumber, const std::string& host, const std::string& startTime, const std::string& endTime) {
        Room room(roomNumber, host, startTime, endTime);
        rooms.push_back(room);
    }

    Room* FindRoom(const std::string& roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                return &room;
            }
        }
        return nullptr;
    }

    void BookRoom(const std::string& roomNumber, const std::string& travelerName, int chairNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            if (room->IsChairAvailable(chairNumber)) {
                room->ReserveChair(chairNumber, travelerName);
                std::cout << "Chair " << chairNumber << " has been booked for " << travelerName << "\n";
            } else {
                std::cout << "The chair " << chairNumber << " is already reserved\n";
            }
        } else {
            std::cout << "Room " << roomNumber << " not found\n";
        }
    }

    void ReleaseRoom(const std::string& roomNumber, int chairNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            if (!room->IsChairAvailable(chairNumber)) {
                room->ReleaseChair(chairNumber);
                std::cout << "Chair " << chairNumber << " has been released\n";
            } else {
                std::cout << "The chair " << chairNumber << " is not reserved\n";
            }
        } else {
            std::cout << "Room " << roomNumber << " not found\n";
        }
    }

    void DisplayRoom(const std::string& roomNumber) {
        Room* room = FindRoom(roomNumber);
        if (room) {
            room->Display();
        } else {
            std::cout << "Room " << roomNumber << " not found\n";
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
        std::cout << "---------- Room Booking System ----------\n";
        std::cout << "1. Add Room\n";
        std::cout << "2. Book Room\n";
        std::cout << "3. Release Room\n";
        std::cout << "4. Display Room\n";
        std::cout << "5. Display All Rooms\n";
        std::cout << "6. Exit\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string roomNumber, host, startTime, endTime, travelerName;
        int chairNumber;

        switch (choice) {
            case 1:
                std::cout << "Enter Room Number: ";
                std::getline(std::cin, roomNumber);

                std::cout << "Enter Host: ";
                std::getline(std::cin, host);

                std::cout << "Enter Start Time: ";
                std::getline(std::cin, startTime);

                std::cout << "Enter End Time: ";
                std::getline(std::cin, endTime);

                bookingSystem.AddRoom(roomNumber, host, startTime, endTime);
                std::cout << "Room " << roomNumber << " added successfully\n";
                break;

            case 2:
                std::cout << "Enter Room Number: ";
                std::getline(std::cin, roomNumber);

                std::cout << "Enter Traveler Name: ";
                std::getline(std::cin, travelerName);

                std::cout << "Enter Chair Number: ";
                std::cin >> chairNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bookingSystem.BookRoom(roomNumber, travelerName, chairNumber);
                break;

            case 3:
                std::cout << "Enter Room Number: ";
                std::getline(std::cin, roomNumber);

                std::cout << "Enter Chair Number: ";
                std::cin >> chairNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bookingSystem.ReleaseRoom(roomNumber, chairNumber);
                break;

            case 4:
                std::cout << "Enter Room Number: ";
                std::getline(std::cin, roomNumber);

                bookingSystem.DisplayRoom(roomNumber);
                break;

            case 5:
                bookingSystem.DisplayAllRooms();
                break;

            case 6:
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "\n";
    }
}


