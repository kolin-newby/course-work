public class Animal {
    
    //Encapsulated name variabel
    //Also the identifier for animal
    public String name;
    protected ExerciseBehavior exerciseBehavior;

    //Animal class Constructor
    public Animal(String animalName){
        this.name = animalName;
    }

    //Polmorphic Methods

    //Method: wakeUp
    //returns as string w/ animal name and "is now awake."
    public String wakeUp(){
        return(this.name + " is now awake.");
    }
    
    //Method: sleep
    //returns as string w/ animal name and "is now sleeping."
    public String sleep() {
        return(this.name + " is now sleeping.");
    }

    //Method: roam
    //returns as string w/ animal name and "is now roaming."
    public String roam(){
        return(exerciseBehavior.roam(this.name));
    }
    
    //Method: makeNoise
    //returns as string w/ animal name and "is making noise."
    public String makeNoise(){
        return(this.name + " is making noise.");
    }
    
    //Method: eat
    //returns as string w/ animal name and "is now eating."
    public String eat(){
        return(this.name + " is now eating.");
    }

    public void setExerciseBehavior(ExerciseBehavior eb){
        exerciseBehavior = eb;
    }

}
