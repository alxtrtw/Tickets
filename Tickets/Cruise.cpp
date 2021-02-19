#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Cruise.h"

// ########## CRUISE ###########

Cruise::Cruise(std::string line) : Ticket(line) { // Constructor that uses the parent class constructor	

	std::vector<std::string> args;
	std::stringstream data(line);
	std::string temp;
	while (std::getline(data, temp, ';'))
	{
		args.push_back(temp);
	}

	// Now we fill in all the remaining class-specific data 
	// (1st arg is the ticket type, parent class constructor loads first 8 values after that, hence we start at 9)
	this->ship_seat = args.at(9);
	this->ship_name = args.at(10);
	this->ship_boarding_time = args.at(11);
}

std::string Cruise::pass_ticket_data() { // Fields to text line
	std::vector<std::string> items;
	std::string line = "C";
	items.push_back(this->booked);
	items.push_back(this->id_of_reservation);
	items.push_back(this->name_of_owner);
	items.push_back(this->start_location);
	items.push_back(this->start_time);
	items.push_back(this->end_location);
	items.push_back(this->end_time);
	items.push_back(this->price);
	items.push_back(this->ship_seat);
	items.push_back(this->ship_name);
	items.push_back(this->ship_boarding_time);

	for (const auto& item : items) {
		line += ";";
		line += item;
	}
	return line;
};

std::string Cruise::get_id() { return this->id_of_reservation; };

void Cruise::get_ticket_info() { // Print data
	if (this->booked == "booked") {
		std::cout << this->name_of_owner << "'s  ticket no. " << this->id_of_reservation << "\n";
	}
	std::cout << "Cruise from " << this->start_location << " (" << this->start_time << ") to " << this->end_location << " (" << this->end_time << ")" <<
		"\n  seat no. " << this->ship_seat << " on ship " << this->ship_name << " boarded at " << this->ship_boarding_time <<
		"\n  priced at " << this->price << "\n\n";
};

void Cruise::enter_book_data(std::string name, std::string id) { // Load necessery data into fields when booking
	this->name_of_owner = name;
	this->id_of_reservation = id;
	this->booked = "booked";
};

void Cruise::remove_book_data() { // Nullify fields when canceling reservation
	this->name_of_owner = "NULL";
	this->id_of_reservation = "NULL";
	this->booked = "unbooked";
};