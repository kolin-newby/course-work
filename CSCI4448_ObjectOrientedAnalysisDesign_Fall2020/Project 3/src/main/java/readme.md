#Project 3:
###Team: Chandler Garthwaite, Tanner Slemmer, Kolin Knewby

###Build Tree:
	./src
		main/
			- Includes all of our class files and implementations
		test/
			- Includes the tester file which runs our 8 unit level tests as well as 2 integration tests between observers
        
###Object Oriented Pattern Examples:
- Factory
    This is implemented for the rolls. And allows us to create rolls through the factories and makes it super easy. ALthough after implementing it and hearing in class this is probably not the best implemenation because standard instantiation would make the same amount of sense.
- Decorators
    This is accomplished by extending the extras class into all 3 extras and using the decorator pattern used in the lecture slides. This allows us to instantiate a roll type and add any types of extras at runtime. Instead of having to predetermine all the options. Which is 15 different options which simplifies our code
- Observers
	This is accomplished through the calendar, store, and store observer. When updates of days and inventory occur. The store observes this event and prints out the all the information being printed as well as stored in the out file.


###Assumptions:
- We used a simple factory for the rolls since it didn't specify which type. Although implementing the factory to include extras would be a nice way to make it really shine.

###Citations:
- Any use of the Observables and Observers is based on the lecture 12 slides
- Other citations have been mentioned in code comments above functions


###How to Run:
- Running the shop class file where the main function is. The tests can be run from the tester file in the test folder

