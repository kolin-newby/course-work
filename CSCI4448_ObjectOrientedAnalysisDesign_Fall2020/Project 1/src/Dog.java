public class Dog extends Canine {

    //Dog Constructor, just calls feline's Canine w/ animalName + "The Dog" and checks if it the provided name has a D
    public Dog(String name){
        super(name + " the Dog");
        if(name.charAt(0) != 'D'){
            throw new Error("The arguement for the name must begin with D");
        }
    
    }
    
    //Method:Roam
    //Runs a random number to see what action the Dog does
    //Returns a string of the action it is doing
    public String roam(){
        double randNum = Math.random(); //Math.random returns a double that is in the range: 0 < x <= 1
        if(randNum > 0 && randNum <= 0.25){ //25% chance of digging
            return(this.name + "is now digging");
        }
        else{ //75% chance of roam
            return(this.name + "is now roaming");
        }
    }
}
