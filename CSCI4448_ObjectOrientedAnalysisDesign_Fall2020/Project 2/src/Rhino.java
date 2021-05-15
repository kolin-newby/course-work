public class Rhino extends Pachyderm {
	//Rhino Constructor, just calls Pachyderm's constructor w/ animalName + "The Rhino" and checks if it the provided name has a R
    public Rhino(String name){
    	super(name + " the Rhino");
        if(name.charAt(0) != 'R'){
            throw new Error("The arguement for the name must begin with R");
        }
    }
}
