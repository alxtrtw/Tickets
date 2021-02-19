#pragma once
#include <iostream>

// ########## TICKET ###########

class Ticket {
protected:
	std::string booked;
	std::string id_of_reservation;
	std::string name_of_owner;
	std::string start_location;
	std::string start_time;
	std::string end_location;
	std::string end_time;
	std::string price;
	
public:
	// Pure virtual methods
	virtual std::string pass_ticket_data() = 0;
	virtual std::string get_id() = 0;
	virtual void get_ticket_info() = 0;
	virtual void enter_book_data(std::string name, std::string id) = 0;
	virtual void remove_book_data() = 0;

	Ticket(std::string line);

};