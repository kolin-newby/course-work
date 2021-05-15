import java.util.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

import java.nio.file.StandardOpenOption;
//This is the driving file for all the classes

public class Zoo{

    //Method to create the array list for the ZooKeeper
    private static ArrayList<Animal> createAnimals(){
        ArrayList<Animal> zooAnimals = new ArrayList<Animal>();
        //ExerciseBehaviorOptions
        ExerciseBehavior roamer =  new ExerciseBehavior(0);
        ExerciseBehavior charger = new ExerciseBehavior(1);

        //Animal creation

        //Canines
        Dog dave = new Dog("Dave");
        Dog davis = new Dog("Davis");
        Wolf willy = new Wolf("Willy");
        Wolf walter = new Wolf("Walter");

        zooAnimals.add(dave);
        zooAnimals.add(davis);
        zooAnimals.add(willy);
        zooAnimals.add(walter);

        //Felines
        Cat charlie = new Cat("Charlie");
        Cat chuck = new Cat("Chuck");
        Lion leo = new Lion("Leo");
        Lion lenard = new Lion("Lenard");
        Tiger tabitha = new Tiger("Tabitha");
        Tiger tucker = new Tiger("Tucker");


        zooAnimals.add(charlie);
        zooAnimals.add(chuck);
        zooAnimals.add(leo);
        zooAnimals.add(lenard);
        zooAnimals.add(tabitha);
        zooAnimals.add(tucker);

        //Crustaceans
        Crab carter = new Crab("Carter");
        Crab carry = new Crab("Carry");
        Lobster larry = new Lobster("Larry");
        Lobster lexi = new Lobster("Lexi");

        zooAnimals.add(carter);
        zooAnimals.add(carry);
        zooAnimals.add(larry);
        zooAnimals.add(lexi);

        leo.setExerciseBehavior(roamer);

        int listSize = zooAnimals.size();
        Animal currentAnimal;
        int i;
        //Setting the roam values for the strategy pattern before Pachyderms are added
        //Example of the Strategy Pattern being used during runtime
        for(i = 0; i < listSize; i++){
            currentAnimal = zooAnimals.get(i);
            currentAnimal.setExerciseBehavior(roamer);
            zooAnimals.set(i,currentAnimal);
        }

        //Pachyderm
        Elephant ellie = new Elephant("Ellie");
        Elephant edward = new Elephant("Edward");
        Hippo harry = new Hippo("Harry");
        Hippo harriet = new Hippo("Harriet");
        Rhino renald = new Rhino("Renald");
        Rhino reginal = new Rhino("Reginal");

        zooAnimals.add(ellie);
        zooAnimals.add(edward);
        zooAnimals.add(harry);
        zooAnimals.add(harriet);
        zooAnimals.add(renald);
        zooAnimals.add(reginal);

        listSize = zooAnimals.size();
        

        //Setting the roam values for the strategy pattern
        //Example of the Strategy Pattern being used during runtime
        for(int k = i; k < listSize; k++){
            currentAnimal = zooAnimals.get(k);
            currentAnimal.setExerciseBehavior(charger);
            zooAnimals.set(k,currentAnimal);
        }
        return zooAnimals;
    }

    public static void main(String args[])  throws IOException
    { 
        

        ArrayList<Animal> animalList = new ArrayList<Animal>();
        animalList = createAnimals();
        /*Comment out above line and comment in this line for comprehensive version
        //ExerciseBehaviorOptions
        ExerciseBehavior roamer =  new ExerciseBehavior(0);
        ExerciseBehavior charger = new ExerciseBehavior(1);
        Elephant ellie = new Elephant("Ellie");
        ellie.setExerciseBehavior(charger);
        animalList.add(ellie);*/

        //File path value to path and cleaning the file
        Path fileName = Path.of("dayatthezoo.out");
        Files.writeString(fileName, "");

        //Zoo Objects
        ZooClock clock = new ZooClock(fileName);
        ZooKeeper keeper = new ZooKeeper("Amy", fileName, animalList,clock);
        ZooFoodServer server = new ZooFoodServer("William",fileName,clock);
        ZooAnnouncer announcer = new ZooAnnouncer("Beccy",keeper,server,fileName,clock);
       
        //Setting announcers
        server.addObserver(announcer);
        keeper.addObserver(announcer);
        clock.addObserver(announcer);
        clock.addObserver(server);
        clock.addObserver(keeper);
        //Run through the zoo week
        clock.runThroughWeek();

    } 

}