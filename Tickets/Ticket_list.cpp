#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Ticket.h"
#include "Cruise.h"
#include "Flight.h"
#include "Mixed.h"

template <class T> class Ticket_list {	// Generic template class for ticket database

private:
	
	int n_of_tickets;
	std::string filename;
	T ** ticket_list;

	void load_ticket_file(std::string filename) { // Loading a database line by line from a .csv file
		
		std::ifstream file(filename);
		int iter = 0;

		if (file.is_open()) {
			std::string line, n;
			std::getline(file, n);
			this->n_of_tickets = stoi(n);
			ticket_list = new T * [n_of_tickets];
			while (std::getline(file, line)) {
				insert_ticket(iter, line);
				iter++;
			}
			file.close();
		}

	};

	void save_ticket_file(std::string filename) { // Saving database data to a .csv file
		
		std::ofstream file(filename);

		if (file.is_open()) {
			file << std::to_string(this->n_of_tickets) << std::endl;
			for (int i = 0; i < n_of_tickets; i++) {
				file << ticket_list[i]->pass_ticket_data(); // Using type-specific pass_ticket_data() method which turns a ticket into a string
				file << std::endl;
			}
		}
		file.close();
	};

public:

	Ticket_list(std::string filename) { // Constructor which takes the name of the .csv file as an argument
		
		this->filename = filename;
		load_ticket_file(filename);
	}

	void insert_ticket(int position, std::string line) { // Method for inserting/replacing data to an already existing ticket in the base

		if (line[0] == 'C') { // First letter of a ticket line in the file is the type of the ticket (C -> Cruise etc.)
			Cruise* ticket = new Cruise(line);
			ticket_list[position] = ticket;
		}
		else if (line[0] == 'F') {
			Flight* ticket = new Flight(line);
			ticket_list[position] = ticket;
		}
		else if (line[0] == 'M') {
			Mixed* ticket = new Mixed(line);
			ticket_list[position] = ticket;
		}
		else {
			std::cout << "Wrong ticket format";
		}

	};
	
	
	void operator+=(std::string line) { // adding a new ticket entry to the database by passing a line from the .csv file
	
		int n = this->n_of_tickets;

		T** new_array = new T * [this->n_of_tickets+1];
		std::copy(this->ticket_list, this->ticket_list + this->n_of_tickets + 1, new_array);

		delete[] this->ticket_list;
		this->ticket_list = new_array;
		this->insert_ticket(this->n_of_tickets, line);
		this->n_of_tickets++;

		save_ticket_file(filename);

	};

	void operator-=(std::string id) { // removing a ticket entry from the database by it's ID
		
		int n = this->n_of_tickets;

		T** new_array = new T * [this->n_of_tickets];
		std::copy(this->ticket_list, this->ticket_list + this->n_of_tickets + 1, new_array);

		for (int i = 0; i < n; i++){
			if (this->ticket_list[i]->get_id() == id){

				T** temp_array = new T * [this->n_of_tickets-1];
				std::copy(this->ticket_list, this->ticket_list + i, temp_array);
				std::copy(this->ticket_list + i + 1, this->ticket_list + this->n_of_tickets, temp_array + i);
				delete[] new_array;
				new_array = temp_array;
				this->n_of_tickets--;
			}
		}
		delete[] this->ticket_list;
		this->ticket_list = new_array;

		save_ticket_file(filename);
	};

	int get_n_of_tickets() { return this->n_of_tickets; }; // Returns storet number of tickets

	std::string get_ticket_data(int position) { // Returns the data of a ticket at given position in form of the .csv file line
		return this->ticket_list[position]->pass_ticket_data();
	}

	int find_pos_by_id(std::string id) { // Returns the position (index) of a ticket with given ID
		for (int i = 0; i < this->n_of_tickets; i++) {
			if (this->ticket_list[i]->get_id() == id) {
				return i;
			}
		}
		return -1;
	}

	bool is_same_id(std::string id) { // Checks if any ticket in the database has a matching id
		for (int i = 0; i < this->n_of_tickets; i++) {
			if (this->ticket_list[i]->get_id() == id) {
				return true;
			}
		}
		return false;
	}

	void book(int position, std::string name, std::string id) { // Enters the booking data (name, ID) into a ticket object
		this->ticket_list[position]->enter_book_data(name, id);
	}

	void unbook(int position) { // removes the booking data (name, ID) from a ticket object (turns the strings into "NULL")
		this->ticket_list[position]->remove_book_data();
		save_ticket_file(filename); // Has to be saved because of the implementation in the main menu() function
	}

	void show_ticket_list(bool enumerate) { // Neatly prints out the database, if enumerate==true then also prints the indexes 
		if (this->n_of_tickets <= 0) {
			std::cout << "Sorry, looks like there are no tickets here\n\n";
		}
		else {
			for (int i = 0; i < n_of_tickets; i++) {
				if (enumerate) { std::cout << i + 1 << ".\n"; } // Database is indexed from 0, so we add 1 for printing out
				this->ticket_list[i]->get_ticket_info(); // Class-specific printing of ticket data
			}
		}
	};



};