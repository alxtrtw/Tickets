#include <iostream>
#include <vector>
#include <sstream>
#include "Ticket.h"

// ########## TICKET ###########

// An abstract parent class for the tickets

void Ticket::get_ticket_info() {};
void Ticket::enter_book_data(std::string name, std::string id) {};
void Ticket::remove_book_data() {};
std::string Ticket::pass_ticket_data() { return ""; };	// The return is there because of the error "function has to return something" 
std::string get_id() { return "";  };					// which appears even though the declaration in .h file makes it pure virtual

Ticket::Ticket(std::string line) { // Constructor, fills object data with the arguments from a .csv file line

	std::vector<std::string> args;
	std::stringstream  data(line);
	std::string temp;
	while (std::getline(data, temp, ';')) // A ';' appears between every text field in the line
	{
		args.push_back(temp);
	}

	this->booked = args.at(1);
	this->id_of_reservation = args.at(2);
	this->name_of_owner = args.at(3);
	this->start_location = args.at(4);
	this->start_time = args.at(5);
	this->end_location = args.at(6);
	this->end_time = args.at(7);
	this->price = args.at(8);

}