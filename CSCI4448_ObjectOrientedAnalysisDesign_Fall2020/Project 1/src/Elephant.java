public class Elephant extends Pachyderm {
	//Elephant Constructor, just calls Pachyderm's constructor w/ animalName + "The Elephant" and checks if it the provided name has a E
    public Elephant(String name){
    	super(name + " the Elephant");
        if(name.charAt(0) != 'E'){
            throw new Error("The arguement for the name must begin with E");
        }
        
    }
}
