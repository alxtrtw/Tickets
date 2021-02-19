This project was created for Object-oriented Programming classes at Poznań University of Technology.
The app is a simple console application that can be used by a travel agency to record and store data about available tickets and reservations. 

There are three types of tickets: Cruise, Flight and Mixed (Cruise + Flight). 
Every type of ticket has its own class. The abstract class Ticket is also responsible for storing the data in csv files.
When booking a ticket, client's name and reservation ID needs to be typed into the input.
When deleting, a reservation is referenced by its previously entered ID.

Room for improvement:
     * Replace CSV with JSON
     * Multiple tickets for one trip, seat number generator
     * Reservation ID generator
     * Multiple stops in a Mixed ticket
     * GUI
