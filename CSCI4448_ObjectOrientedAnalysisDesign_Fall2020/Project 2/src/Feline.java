public class Feline extends Animal{

    //Felines Constructor, just calls animal's constructor w/ animalName
    public Feline(String animalName){
        super(animalName);
        //name = animalName;
    }

    //Method:Sleep
    //Runs a random number to see what action the feline does
    //Returns a string of the action it is doing
    public String sleep(){
        double randNum = Math.random(); //Math.random returns a double that is in the range: 0 < x <= 1
        //System.out.print(randNum);

        if(randNum > 0 && randNum <= 0.30){ //30% chance of makeNoise
            return(this.makeNoise());
        }
        else if(randNum > 0.30 && randNum <= 0.60) { //30% chance of roam
            return(this.roam());
        }
        else{ //40% chance of sleep
            return(this.name + " is now sleeping");
        }

    }
}
