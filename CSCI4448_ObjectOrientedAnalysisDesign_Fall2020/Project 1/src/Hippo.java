public class Hippo extends Pachyderm {
	//Hippo Constructor, just calls Pachyderm's constructor w/ animalName + "The Hippo" and checks if it the provided name has a H
    public Hippo(String name){
    	super(name + " the Hippo");
        if(name.charAt(0) != 'H'){
            throw new Error("The arguement for the name must begin with H");
        }
        
    }
}
