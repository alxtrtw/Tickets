#pragma once
#include <iostream>
#include "Ticket.h"

// ########## MIXED ###########

class Mixed : public Ticket {
private:
	std::string plane_seat;
	std::string seat_location;
	std::string cabin_class;
	std::string gate;
	std::string flight_boarding_time;
	std::string ship_seat;
	std::string ship_name;
	std::string ship_boarding_time;
	std::string change_location;
	std::string change_start;
	std::string change_stop;

public:

	Mixed(std::string line);

	std::string pass_ticket_data() override;

	std::string get_id() override;

	void get_ticket_info() override;

	void enter_book_data(std::string name, std::string id) override;

	void remove_book_data() override;

};
