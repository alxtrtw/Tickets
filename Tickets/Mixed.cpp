#include <iostream>
#include <vector>
#include <sstream>
#include "Mixed.h"

// ########## MIXED ###########

Mixed::Mixed(std::string line) : Ticket(line) { // Constructor that uses the parent class constructor	

	std::vector<std::string> args;
	std::stringstream  data(line);
	std::string temp;
	while (std::getline(data, temp, ';'))
	{
		args.push_back(temp);
	}

	// Now we fill in all the remaining class-specific data 
	// (1st arg is the ticket type, parent class constructor loads first 8 values after that, hence we start at 9)
	this->plane_seat = args.at(9);
	this->seat_location = args.at(10);
	this->cabin_class = args.at(11);
	this->gate = args.at(12);
	this->flight_boarding_time = args.at(13);
	this->ship_seat = args.at(14);
	this->ship_name = args.at(15);
	this->ship_boarding_time = args.at(16);
	this->change_location = args.at(17);
	this->change_start = args.at(18);
	this->change_stop = args.at(19);

}

std::string Mixed::pass_ticket_data() { // Fields to text line
	std::vector<std::string> items;
	std::string line ="M";
	items.push_back(this->booked);
	items.push_back(this->id_of_reservation);
	items.push_back(this->name_of_owner);
	items.push_back(this->start_location);
	items.push_back(this->start_time);
	items.push_back(this->end_location);
	items.push_back(this->end_time);
	items.push_back(this->price);
	items.push_back(this->plane_seat);
	items.push_back(this->seat_location);
	items.push_back(this->cabin_class);
	items.push_back(this->gate);
	items.push_back(this->flight_boarding_time);
	items.push_back(this->ship_seat);
	items.push_back(this->ship_name);
	items.push_back(this->ship_boarding_time);
	items.push_back(this->change_location);
	items.push_back(this->change_start);
	items.push_back(this->change_stop);

	for (const auto& item : items) {
		line += ";";
		line += item;
	}
	return line;
};

std::string Mixed::get_id() { return this->id_of_reservation; };

void Mixed::get_ticket_info() { // Print data
	if (this->booked == "booked") {
		std::cout << this->name_of_owner << "'s  ticket no. " << this->id_of_reservation << "\n";
	}
	std::cout << "Trip from " << this->start_location << " (" << this->start_time << ") to " << this->end_location << " (" << this->end_time << ")" <<
		"\n  flight: seat no. " << this->plane_seat << " (" << this->seat_location << " in " << this->cabin_class << " class) at gate " << this->gate << " boarded at " << this->flight_boarding_time <<
		"\n  cruise: seat no. " << this->ship_seat << " on ship " << this->ship_name << " boarded at " << this->ship_boarding_time <<
		"\n  change in " << this->change_location << " between " << this->change_start << " and " << change_stop <<
		"\n  priced at " << this->price << "\n\n";
}

void Mixed::enter_book_data(std::string name, std::string id) { // Load necessery data into fields when booking
	this->name_of_owner = name;
	this->id_of_reservation = id;
	this->booked = "booked";
}

void Mixed::remove_book_data() { // Nullify fields when canceling reservation
	this->name_of_owner = "NULL";
	this->id_of_reservation = "NULL";
	this->booked = "unbooked";
};
