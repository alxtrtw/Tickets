#include <iostream>
#include <fstream>
#include <windows.h>
#include "Ticket.h"
#include "Cruise.h"
#include "Flight.h"
#include "Mixed.h"
#include "Ticket_list.cpp"

//////////////////////////// Alex T /////////////////////////////
////////////// Object-oriented Programming project //////////////
//////////////////// Trip reservation system ////////////////////

// This project was created for Object-oriented Programming classes at Poznań University of Technology.
// The app is a simple console application that can be used by a travel agency to record and store 
// data about available tickets and reservations. There are three types of tickets: Cruise, Flight and Mixed (Cruise + Flight). 
// Every type of ticket has it's own class. The abstract class Ticket is also responsible for storing the data in text files.
// When booking a ticket, client's name and reservation ID needs to be typed into the input.
// Room for improvement:
//      * JSON instead of CSV
//      * Multiple tickets for one trip, seat number generator
//      * Reservation ID generator
//      * Multiple stops in a Mixed ticket
//      * GUI


bool is_quit(std::string input) { // For quitting the program
    if (input == "quit") { return true; }
    else { return false; }
}

void menu() { // Main function

    std::string choice; // User's menu input
    bool error_flag = false;
    int pos;
    bool quit = false;
    Ticket_list<Ticket> available_tickets("available.csv"); // Declare dbase of available tickets
    Ticket_list<Ticket> reservations("reservations.csv"); //  Declare dbase of reservations

    std::cout << "Welcome, what would you like to do?\n";
    while (true) { 
        if (error_flag == 1) { 
            std::cout << "Wrong input value, try again\n";
        }

        std::cout << "Your options:\n";
        std::cout << "  1. Book a trip\n  2. Cancel a trip\n  3. Show available trips\n  4. Show reservations\n  Write \"quit\" anywhere in the program to exit\n";
        std::cin >> choice;
        if (is_quit(choice)) { break; }; // A reoccuring if statement that allows exiting the program at every input

        system("cls");


        if (choice == "1") { // The menu should probably be a switch-case, the nested ifs are apologizing to your eyes
            std::cout << "Here's the available tickets:\n";
            available_tickets.show_ticket_list(true); // Print tickets, if argument is true then the tickets are indexed
            std::string number, name, surname, id;

            if (available_tickets.get_n_of_tickets() <= 0) { // You can't book a ticket if there aren't any available
                std::cout << "New ticket offers must be added first in order to book a trip\n\n";
            }
            else {

                std::cout << "Please enter the number of the ticket you want to book\n";
                std::cin >> number;
                if (is_quit(number)) { break; };
                if (stoi(number) > available_tickets.get_n_of_tickets() || stoi(number) < 1) { // Check if input in range
                    error_flag = true;
                    continue;
                }

                std::cout << "Now enter the owner's (divided by space) name, surname, and ID for the new reservation\n";
                std::cin >> name >> surname >> id;
                if (is_quit(name) || is_quit(surname) || is_quit(id)) { break; };

                if (reservations.is_same_id(id)) { // Can't have duplicate IDs in reservations
                    system("cls");
                    std::cout << "\nCan't book, a reservation with the same id already exists!!\n\n";
                }
                else { // All tests passed, now adding the ticket to reservation dbase and removing it from the available_tickets

                    available_tickets.book(stoi(number) - 1, name + " " + surname, id); // Enter the data from input to the ticket object
                    reservations += available_tickets.get_ticket_data(stoi(number) - 1);
                    available_tickets -= id;
                    system("cls");
                }
            }
        }
        else if (choice == "2") { // Remove reservation = transport it from reservations to available_tickets
            std::string id;
            std::cout << "Please enter the ID of the reservation you want to cancel\n";
            std::cin >> id;
            if (is_quit(id)) { break; };

            pos = reservations.find_pos_by_id(id); // Find the position of a ticket with such id, if not found returns -1
            if (pos >= 0) { // If ticket with this id exists then position is positive
                available_tickets += reservations.get_ticket_data(pos); // Move ticket to available_tickets dbase
                reservations -= id; // Remove ticket from the reservations dbase
                pos = available_tickets.find_pos_by_id(id); // Notice that the id wasn't deleted, so we're searching for ticket's position in available_tickets
                available_tickets.unbook(pos); // remove the name and id
            }
            else {
                std::cout << "There are no tickets with this ID\n\n";
            }
        }
        else if (choice == "3") { // Print available tickets
            available_tickets.show_ticket_list(false);  // argument is false because we don't need the tickets indexed
            
        }
        else if (choice == "4") { // Print reservations
            reservations.show_ticket_list(false); // Same as above
        }
        else{ // Wrong input
            error_flag = true;
        }
    }
    std::cout << "\nBye!\n"; // End of program

}

int main()
{
    menu();
}
