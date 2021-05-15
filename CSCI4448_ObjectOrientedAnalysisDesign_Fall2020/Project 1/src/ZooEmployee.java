public abstract class ZooEmployee {
    //Common tasks for all ZooEmployees
    String employeeName;

    //Abstrast Methods for inheritted classes
    //Method: arrive
    //Takes a int for what day it is
    //Returns a string with employeename, " arrives at the zoo day", day int, and then returns the string
    public String arrive(int day){
    	return this.employeeName + " arrives at the zoo Day " + day + ".";
    	
    }
    
	//Method: arrive
    //Takes a int for what day it is
    //Returns a string with employeename, " leaves the zoo day", day int, and then returns the string
    public String leave(int day){
    	return this.employeeName + " left the zoo Day " + day + ".";
    }
    
}   