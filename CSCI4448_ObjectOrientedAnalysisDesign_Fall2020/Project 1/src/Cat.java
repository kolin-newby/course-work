public class Cat extends Feline {

	//Cat Constructor, just calls feline's constructor w/ animalName + "The Cat" and checks if it the provided name has a C
    public Cat(String name){
    	super(name + " the Cat");
        if(name.charAt(0) != 'C'){
            throw new Error("The arguement for the name must begin with C");
        }
        
    }

}
