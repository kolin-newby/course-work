public class Crab extends Crustacean {
	//Crab Constructor, just calls feline's constructor w/ animalName + "The Crab" and checks if it the provided name has a C
	public Crab(String name){
		super(name + " the Crab");
        if(name.charAt(0) != 'C'){
            throw new Error("The arguement for the name must begin with C");
        }
        
    }
}
