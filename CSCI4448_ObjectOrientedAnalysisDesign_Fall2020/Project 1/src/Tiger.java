public class Tiger extends Feline {
	//Tiger Constructor, just calls Feline's constructor w/ animalName + "The Tiger" and checks if it the provided name has a T
    public Tiger(String name){
    	super(name + " the Tiger");
        if(name.charAt(0) != 'T'){
            throw new Error("The arguement for the name must begin with T");
        }
        
    }
}
