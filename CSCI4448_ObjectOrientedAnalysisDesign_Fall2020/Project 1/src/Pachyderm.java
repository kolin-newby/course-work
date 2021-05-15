public class Pachyderm extends Animal{

    //Pachyderm Constructor, just calls animal's constructor w/ animalName
	public Pachyderm(String animalName){
        super(animalName);
    }
    

    //Method:Roam
    //Runs a random number to see what action the Pachyderm does
    //Returns a string of the action it is doing
    public String roam(){
        double randNum = Math.random(); //Math.random returns a double that is in the range: 0 < x <= 1
        if(randNum > 0 && randNum <= 0.25){ //25% chance of charge
            return(this.name + " is now charging");
        }
        else{ //75% chance of roam
            return(this.name + " is now roaming");
        }
    }

}
