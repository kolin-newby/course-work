public class Lobster extends Crustacean{
	//Lobster Constructor, just calls Crustacean's constructor w/ animalName + "The Lobster" and checks if it the provided name has a L
	public Lobster(String name){
		super(name + " the Lobster");
	        if(name.charAt(0) != 'L'){
	            throw new Error("The arguement for the name must begin with L");
	        }
	      
	    }
}
