public class ExerciseBehavior{

    private int charger;//if it is a charger make this 1, if this is not make this 0

    //ExerciseBehavior Constructor, used to determine what exercise animals do
    //This class is an example of the Strategy Pattern as it brings the behavior away from the class to be able to be set at run time
	public ExerciseBehavior(int chargerValue){
        charger = chargerValue;
    }
    

    //Method:Roam
    //
    //Returns a string of the action it is doing based on if it was a charger or not, then if the charger condition was met
    public String roam(String name){
        //Math.random returns a double that is in the range: 0 < x <= 1
        //If it is a charger it keeps the rand, otherwise it sets it to 0
        double randNum = Math.random() * charger; 
        if(randNum > 0.75){ //25% chance of charge
            return(name + " is now charging");
        }
        else{ //75% chance of roam if it is a charger, otherwise it always roams
            return(name + " is now roaming");
        }
    }

}
