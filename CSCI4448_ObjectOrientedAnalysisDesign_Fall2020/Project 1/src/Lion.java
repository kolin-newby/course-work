public class Lion extends Feline {
	//Lion Constructor, just calls Feline's constructor w/ animalName + "The Lion" and checks if it the provided name has a L
    public Lion(String name){
    	super(name + " the Lion");
        if(name.charAt(0) != 'L'){
            throw new Error("The arguement for the name must begin with L");
        }
        
    }
}
