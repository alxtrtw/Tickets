#pragma once
#include <iostream>
#include "Ticket.h"

// ########## CRUISE ###########

class Cruise : public Ticket {
private:
	std::string ship_seat;
	std::string ship_name;
	std::string ship_boarding_time;

public:

	Cruise(std::string line);

	void get_ticket_info() override;

	std::string get_id() override;

	std::string pass_ticket_data() override;

	void enter_book_data(std::string name, std::string id) override;

	void remove_book_data() override;

};