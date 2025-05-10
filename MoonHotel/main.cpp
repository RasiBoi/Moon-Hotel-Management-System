#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAX_ROOMS = 24; // Maximum number of rooms
const int MAX_BOOKINGS = 100; // Maximum number of bookings

// Struct to store admin information
struct Admin {
    string username;
    string password;
    string birthdate;
};

// Struct to store user information
struct User {
    string username;
    string password;
    string birthdate;
};

struct Room {
    string type;
    string id;
    int quantity;
    double price;
    bool available;
};

struct Booking {
    string name;
    string NIC;
    string phoneNumber;
    string checkInDate;
    string checkOutDate;
    string roomId;
};

Admin admins[] = {
    {"Admin", "Admin123", "2004.08.11"}
};

User users[] = {
    {"User", "User123", "2004.08.11"}
};

// Initialize bookings array and counter
Booking bookings[MAX_BOOKINGS];
int numBookings = 0;

// Initialize rooms array
Room rooms[MAX_ROOMS];

// Function prototypes
int loading();
void Login();
void adminlogin();
void userlogin();
void adminMenu();
void userMenu();
void adminRooms();
int viewRooms();
void searchRooms();
void bookRoom(string username);
void initializeRooms();
string generateRoomID(string type, int number);
void bookingDetails();
void manageorders();
void prepareBill();
void updateRoom();

int main()
{
    loading();
    system("cls");
    // Populate the rooms array with initial room information
    initializeRooms();
    Login();
    return 0;
}

void initializeRooms()
{
    // Define room types
    string roomTypes[] = {
        "Single Room", "Double Room", "Twin Room", "Family Room",
        "Standard Room", "Deluxe Room", "AC_Room", "Non-AC Room"
    };

    // Populate rooms array
    int roomCount = 1;
    for (const auto& type : roomTypes) {
        // Create rooms for each type
        for (int i = 0; i < 3; ++i) { // 3 rooms of each type
            Room room;
            room.type = type;
            room.id = generateRoomID(type, roomCount);
            room.quantity = 1; // Assuming each room type has one unit initially
            room.price = 100.0; // Set default price
            room.available = true; // Initially all rooms are available
            rooms[roomCount - 1] = room; // Assign room to the array
            roomCount++;
        }
    }
}

int loading()
{
    string hotelName = "Moon Hotel";
    system("COLOR 09");
    system("cls");

    cout << "\n\n\n\t\t\t  ********************";
    cout << "\n\t\t\t  *                  *";
    cout << "\n\t\t\t  *    " << hotelName << "    *";
    cout << "\n\t\t\t  *                  *";
    cout << "\n\t\t\t  ********************" ;

    int bar1 = 177, bar2 = 219;
    cout << "\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\n\t\t\t";

    for (int i = 0; i < 25; i++)
    {
        cout << (char)bar1;
    }
    cout << "\r";
    cout << "\t\t\t";

    for (int i = 0; i < 25; i++)
    {
        cout << (char)bar2;
        Sleep(150);
    }
    cout << endl;
    cout << "\n\t\t\t";
    cout << "\n\n\t\tPress Enter to continue to login.......";
    _getch(); // Wait for user to press Enter
    return 0;
}

void Login()
{
    system("cls");
    int login;
    cout << "\n\n\t\tChoose your login type:\n";
    cout << "\n\n\n\t\t\t1. Admin Login\n";
    cout << "\n\t\t\t2. User Login\n";
    cout << "\n\t\t\t3. Exit\n";
    cout << "\n\t\t\tEnter your choice: ";
    cin >> login;

    switch (login)
    {
    case 1:
        adminlogin();
        break;
    case 2:
        userlogin();
        break;
    case 3:
        cout << "Exit";
        system("cls");
        cout << "\n\t\tPress enter to exit" << endl;
        exit(0);
    default:
        cout << "\n\t\tInvalid choice";
    }
}

void userlogin()
{
    int attempts = 0;
    string uname;
    string upass;
    string birthdate;

    while (true)
    {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> User Login <<<<<<<<<<<<<<<<" << endl;

        cout << "\n\n\n\t\tEnter User Name : ";
        cin >> uname;
        cout << "\n\t\tEnter User Password : ";
        cin >> upass;

        // Find the user by name
        for (int i = 0; i < MAX_BOOKINGS; ++i) {
            if (users[i].username == uname) {
                birthdate = users[i].birthdate;
                break;
            }
        }

        if (uname == users[0].username && upass == "User123")
        {
            cout << "\n\t\t!Login Successful" << endl;
            userMenu();
            break;
        }
        else
        {
            cout << "\n\t\t!Login Unsuccessful. Please Try Again..!" << endl;
            attempts++;
            if (attempts > 3)
            {
                cout << "\n\n\t\tYou Have Entered User Name or Password 3 times Incorrectly" << endl;
                cout << "\n\n\t\tForgot Password? Press 'F' to reset your password.";
                char choice;
                cin >> choice;
                if (choice == 'F' || choice == 'f') {
                    string new_pass;
                    cout << "\n\t\tEnter your birthdate (YYYY.MM.DD): ";
                    string input_birthdate;
                    cin >> input_birthdate;
                    if (input_birthdate == birthdate) {
                        cout << "\n\t\tEnter your new password: ";
                        cin >> new_pass;
                        users[0].password = new_pass;
                        cout << "\n\t\tPassword reset successful!" << endl;
                        attempts = 0; // Reset attempts after successful password reset
                    }
                    else {
                        cout << "\n\t\tIncorrect birthdate. Password reset failed!" << endl;
                    }
                }
                else {
                    exit(0);
                }
            }
            cout << "\n\n\t\tPress any key to continue..." << endl;
            cin.ignore();
            cin.get();
        }
    }
}

void adminlogin()
{
    int attempts = 0;
    string aname;
    string apass;
    string birthdate;

    while (true)
    {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> Admin Login <<<<<<<<<<<<<<<<" << endl;

        cout << "\n\n\n\t\tEnter Admin Name : ";
        cin >> aname;
        cout << "\n\t\tEnter Admin Password : ";
        cin >> apass;

        // Find the admin by name
        for (int i = 0; i < MAX_BOOKINGS; ++i) {
            if (admins[i].username == aname) {
                birthdate = admins[i].birthdate;
                break;
            }
        }

        if (aname == admins[0].username && apass == "Admin123")
        {
            cout << "\n\n\t\t!Login Successful" << endl;
            adminMenu(); // If login successful, proceed to admin menu
            break;
        }
        else
        {
            cout << "\n\n\t\t!Login Unsuccessful. Please Try Again..!" << endl;
            attempts++;
            if (attempts > 3)
            {
                cout << "\n\t\n\t\tYou Have Entered Admin Name or Password 3 times Incorrectly" << endl;
                cout << "\n\t\t\n\tForgot Password? Press 'F' to reset your password." << endl;
                char choice;
                cin >> choice;
                if (choice == 'F' || choice == 'f')
                {
                    string new_pass;
                    cout << "\n\t\tEnter your birthdate (YYYY.MM.DD): ";
                    string input_birthdate;
                    cin >> input_birthdate;
                    if (input_birthdate == birthdate) {
                        cout << "\n\t\tEnter your new password: ";
                        cin >> new_pass;
                        admins[0].password = new_pass;
                        cout << "\n\t\tPassword reset successful!" << endl;
                        attempts = 0; // Reset attempts after successful password reset
                    }
                    else {
                        cout << "\n\t\tIncorrect birthdate. Password reset failed!" << endl;
                    }
                }
                else
                {
                    exit(0);
                }
            }
            cout << "\n\t\t\n\tPress any key to continue..." << endl;
            cin.ignore();
            cin.get();
        }
    }
}

void adminMenu()
{
    int choice;

    do {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> Admin Menu <<<<<<<<<<<<<<<<" << endl;
        cout << "\n\n\n\t\t1. Manage Orders" << endl;
        cout << "\n\t\t2. Manage Rooms" << endl;
        cout << "\n\t\t3. Exit" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // adminorder(); // Implement manage orders function
            manageorders();
            break;
        case 2:
            adminRooms(); // Proceed to manage rooms
            break;
        case 3:
            cout << "\n\t\tExiting admin menu...";
            _getch();
            Login();
            break;
        default:
            cout << "\n\t\tInvalid choice. Please enter again." << endl;
            _getch();
            break;
        }
    } while (choice != 3);
}

void adminRooms()
{
    int choice;
    bool returnToAdminMenu = false; // Flag to control returning to admin menu
    do {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> Manage Rooms <<<<<<<<<<<<<<<<" << endl;
        cout << "\n\n\n\t\t1. View Rooms" << endl;
        cout << "\n\t\t2. Search Rooms" << endl;
        cout << "\n\t\t3. Exit" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewRooms(); // Call viewRooms function
            break;
        case 2:
            searchRooms(); // Call searchRooms function
            break;
        case 3:
            cout << "\n\t\tReturning to admin menu..." << endl;
            _getch();
            returnToAdminMenu = true; // Set flag to return to admin menu
            break;
        default:
            cout << "\n\t\tInvalid choice. Please enter again." << endl;
            _getch();
            break;
        }
    } while (!returnToAdminMenu);
}

string generateRoomID(string type, int number) {
    string id = type.substr(0, 3); // Get first three characters of type
    id += to_string(number); // Append number
    return id;
}

int viewRooms()
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> View Rooms <<<<<<<<<<<<<<<<" << endl;

    // Print table header
    cout << left << setw(20) << "\nRoom Type" << setw(20) << "Room ID" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Availability" << endl;

    // Print room information
    for (int i = 0; i < MAX_ROOMS; ++i) {
        cout << left << setw(20) << rooms[i].type << setw(20) << rooms[i].id << setw(20) << rooms[i].quantity << setw(20) << rooms[i].price;
        if (rooms[i].available)
            cout << "Available";
        else
            cout << "Not available";
        cout << endl;
    }

    // Wait for user input before returning
    _getch();
    return 0;
}

void searchRooms()
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> Search Room <<<<<<<<<<<<<<<<" << endl;

    cout << "\n\t\tEnter Room ID: ";
    string targetRoomId;
    cin >> targetRoomId;

    bool roomFound = false;
    for (int i = 0; i < MAX_ROOMS; ++i) {
        if (rooms[i].id == targetRoomId) {
            // Print details of the found room
            cout << left << setw(20) << "\nRoom Type" << setw(20) << "Room ID" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Availability" << endl;
            cout << left << setw(20) << rooms[i].type << setw(20) << rooms[i].id << setw(20) << rooms[i].quantity << setw(20) << rooms[i].price;
            if (rooms[i].available)
                cout << "Available";
            else
                cout << "Not available";
            cout << endl;

            roomFound = true;
            break; // Room found, no need to search further
        }
    }

    if (!roomFound) {
        cout << "\n\t\tRoom with ID " << targetRoomId << " not found." << endl;
    }

    _getch();
}

void bookRoom(string username)
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> Book Room <<<<<<<<<<<<<<<<" << endl;

    string name, NIC, phoneNumber, checkInDate, checkOutDate, roomId;

    cout << "\n\n\n\t\tEnter Name: ";
    cin >> name;
    cout << "\n\t\tEnter NIC: ";
    cin >> NIC;
    cout << "\n\t\tEnter Phone Number: ";
    cin >> phoneNumber;
    cout << "\n\t\tEnter Check-in Date (YYYY.MM.DD): ";
    cin >> checkInDate;
    cout << "\n\t\tEnter Check-out Date (YYYY.MM.DD): ";
    cin >> checkOutDate;
    cout << "\n\t\tEnter Room ID: ";
    cin >> roomId;

    bool roomFound = false;
    // Update the availability status of the booked room and add booking details
    for (int i = 0; i < MAX_ROOMS; ++i) {
        if (rooms[i].id == roomId) {
            if (rooms[i].available) {
                rooms[i].available = false; // Mark room as unavailable if it was available
                cout << "\n\t\tBooking Confirmed" << endl;
                _getch();
                // Add booking details to the bookings array
                if (numBookings < MAX_BOOKINGS) {
                    bookings[numBookings].name = name;
                    bookings[numBookings].NIC = NIC;
                    bookings[numBookings].phoneNumber = phoneNumber;
                    bookings[numBookings].checkInDate = checkInDate;
                    bookings[numBookings].checkOutDate = checkOutDate;
                    bookings[numBookings].roomId = roomId;
                    numBookings++; // Increment the number of bookings
                } else {
                    cout << "\n\t\tMaximum number of bookings reached." << endl;
                }
            } else {
                cout << "\n\t\tRoom with ID " << roomId << " is already booked." << endl;
            }
            roomFound = true;
            break;
        }
    }

    if (!roomFound) {
        cout << "\n\t\tRoom with ID " << roomId << " not found." << endl;
    }

    // Call viewRooms to display updated room information
    viewRooms();

    _getch();
}

void userMenu()
{
    int choice;
    do {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> User Menu <<<<<<<<<<<<<<<<" << endl;
        cout << "\n\n\n\t\t1. View Rooms" << endl;
        cout << "\n\t\t2. Book Rooms" << endl;
        cout << "\n\t\t3. Booking Details" << endl;
        cout << "\n\t\t4. View Bill" << endl;
        cout << "\n\t\t5. Exit" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            viewRooms(); // Call the existing viewRooms function
            break;
        case 2:
            bookRoom(users[0].username); // Call bookRoom function
            _getch();
            break;
        case 3:
            bookingDetails();
            _getch();
            break;
        case 4:
            // viewBill();  // Implement the viewBill function later
            prepareBill();
            _getch();
            break;
        case 5:
            cout << "\n\t\tExiting user menu...";
            _getch();
            Login();
            break;
        default:
            cout << "\n\t\tInvalid choice. Please enter again." << endl;
            _getch();
            break;
        }
    } while (choice != 5);
}

void bookingDetails()
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> Booking Details <<<<<<<<<<<<<<<<" << endl;

    // Print table header
    cout << left << setw(20) << "\nName" << setw(15) << "NIC" << setw(15) << "Phone Number" << setw(15) << "Check-in Date" << setw(15) << "Check-out Date" << setw(15) << "Room ID" << endl;

    // Print booking details
    for (int i = 0; i < numBookings; ++i) {
        cout << left << setw(20) << bookings[i].name << setw(15) << bookings[i].NIC << setw(15) << bookings[i].phoneNumber << setw(15) << bookings[i].checkInDate << setw(15) << bookings[i].checkOutDate << setw(15) << bookings[i].roomId << endl;
    }

    _getch();
}


void manageorders()
{
    int choice;
    bool returnToAdminMenu = false; // Flag to control returning to admin menu
    do {
        system("cls");
        cout << "\n\t\t>>>>>>>>>>>>>>>> Manage Orders <<<<<<<<<<<<<<<<" << endl;
        cout << "\n\n\n\t\t1. Book Room" << endl;
        cout << "\n\t\t2. View Bookings" << endl;
        cout << "\n\t\t3. Prepare Bill" << endl;
        cout << "\n\t\t4. Update Room Info" << endl;
        cout << "\n\t\t5. Exit" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bookRoom(users[0].username);// Call bookRoom function with admin username
            break;
        case 2:
            bookingDetails(); // Call bookingDetails function to view bookings
            break;
        case 3:
            // prepareBill(); // Implement prepareBill function
            prepareBill();
            _getch();
            break;
        case 4:
            // updateRoomInfo(); // Implement updateRoomInfo function
            updateRoom();
            _getch();
            break;
        case 5:
            cout << "\n\t\tReturning to admin menu..." << endl;
            _getch();
            returnToAdminMenu = true; // Set flag to return to admin menu
            break;
        default:
            cout << "\n\t\tInvalid choice. Please enter again." << endl;
            _getch();
            break;
        }

    } while (!returnToAdminMenu);
}

void prepareBill()
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> Prepare Bill <<<<<<<<<<<<<<<<" << endl;

    // Prompt admin to enter relevant NIC
    string adminNIC;
    cout << "\n\t\tEnter relevant NIC: ";
    cin >> adminNIC;

    // Open the file for writing
    ofstream outputFile("HOTEL.txt");

    // Check if the file is successfully opened
    if (outputFile.is_open()) {
        // Write the bill details
        outputFile << "\nBill Details for NIC: " << adminNIC << endl;
        outputFile << "===================================" << endl;

        for (const auto& booking : bookings) {
            if (booking.NIC == adminNIC) {
                outputFile << "Name: " << booking.name << endl;
                outputFile << "NIC: " << booking.NIC << endl;
                outputFile << "Phone Number: " << booking.phoneNumber << endl;
                outputFile << "Check-in Date: " << booking.checkInDate << endl;
                outputFile << "Check-out Date: " << booking.checkOutDate << endl;
                // Calculate the number of nights stayed
                // Assuming date format is YYYY.MM.DD
                int checkInYear = stoi(booking.checkInDate.substr(0, 4));
                int checkInMonth = stoi(booking.checkInDate.substr(5, 2));
                int checkInDay = stoi(booking.checkInDate.substr(8, 2));
                int checkOutYear = stoi(booking.checkOutDate.substr(0, 4));
                int checkOutMonth = stoi(booking.checkOutDate.substr(5, 2));
                int checkOutDay = stoi(booking.checkOutDate.substr(8, 2));
                // Using C-style time functions to calculate difference in days
                tm checkInTime = { 0, 0, 0, checkInDay, checkInMonth - 1, checkInYear - 1900 };
                tm checkOutTime = { 0, 0, 0, checkOutDay, checkOutMonth - 1, checkOutYear - 1900 };
                time_t checkInTimestamp = mktime(&checkInTime);
                time_t checkOutTimestamp = mktime(&checkOutTime);
                double difference = difftime(checkOutTimestamp, checkInTimestamp);
                int nightsStayed = static_cast<int>(difference) / (60 * 60 * 24);

                // Get the room type for the given roomId
                string roomType;
                for (const auto& room : rooms) {
                    if (room.id == booking.roomId) {
                        roomType = room.type;
                        break;
                    }
                }

                // Find the price per night for the room type
                double pricePerNight = 0.0; // Default price
                for (const auto& room : rooms) {
                    if (room.type == roomType) {
                        pricePerNight = room.price;
                        break;
                    }
                }

                double totalCost = nightsStayed * pricePerNight;

                outputFile << "Room Type: " << roomType << endl;
                outputFile << "Number of Nights Stayed: " << nightsStayed << endl;
                outputFile << "Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
                outputFile << "-----------------------------------" << endl;
            }
        }

        // Close the file
        outputFile.close();
        cout << "\n\t\tBill has been prepared and saved to HOTEL.txt" << endl;
    }
    else {
        cout << "\n\t\tError opening the file." << endl;
    }

    _getch();
}

void updateRoom()
{
    system("cls");
    cout << "\n\t\t>>>>>>>>>>>>>>>> Update Room <<<<<<<<<<<<<<<<" << endl;

    string roomId;
    cout << "\n\t\tEnter Room ID: ";
    cin >> roomId;

    bool roomFound = false;
    for (auto& room : rooms) {
        if (room.id == roomId) {
            roomFound = true;

            int choice;
            cout << "\n\n\t\tWhat do you want to update for Room ID " << roomId << "?" << endl;
            cout << "\n\t\t1. Change Room Price" << endl;
            cout << "\n\t\t2. Change Room Availability" << endl;
            cout << "\n\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double newPrice;
                    cout << "\n\t\tEnter new price for the room: ";
                    cin >> newPrice;
                    room.price = newPrice;
                    cout << "\n\t\tRoom price updated successfully!" << endl;
                    break;
                }
                case 2: {
                    char availabilityChoice;
                    cout << "\n\t\tIs the room available? (Y/N): ";
                    cin >> availabilityChoice;
                    if (availabilityChoice == 'Y' || availabilityChoice == 'y')
                        room.available = true;
                    else if (availabilityChoice == 'N' || availabilityChoice == 'n')
                        room.available = false;
                    else {
                        cout << "\n\t\tInvalid choice. Availability not updated." << endl;
                        break;
                    }
                    cout << "\n\t\tRoom availability updated successfully!" << endl;
                    break;
                }
                default:
                    cout << "\n\t\tInvalid choice. No changes made." << endl;
            }
            break;
        }
    }

    if (!roomFound) {
        cout << "\n\t\tRoom with ID " << roomId << " not found." << endl;
    }

    _getch();
}

