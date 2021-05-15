public class Wolf extends Canine {
	//Wolf Constructor, just calls Canine's constructor w/ animalName + "The Wolf" and checks if it the provided name has a W
    public Wolf(String name){
    	super(name + " the Wolf");
        if(name.charAt(0) != 'W'){
            throw new Error("The arguement for the name must begin with W");
        }
  
    }
}
