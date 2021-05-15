import java.util.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
//This is the driving file for all the classes

public class Zoo{

    //Methods: runThroughTheWeek
    //Takes a kepper, an arrayList of animals, and path to output strings to
    //Runs through each day of the week and then runs through each animal in the list
    //Does not return anything
    public static void runThroughTheWeek(ZooKeeper keeper, ArrayList<Animal> zooAnimals, Path fileName) throws IOException{//This method needs to eventually take a filename to export to a .txt
        int listSize = zooAnimals.size();
        Animal currentAnimal;
        String textForFile = "";

        //Week forLoop
        for(int i = 1; i <= 7; i++ ){

            //Arrival Section
            //This uses abstraction as keeper uses arrive which is inheritted from its superclass, the abstract class zooEmployee, without it being defined in ZooKeeper.
            System.out.println(keeper.arrive(i));
            textForFile = textForFile + keeper.arrive(i) + "\n"; 

            //Runs through each item in zooAnimals then has the keeper action, then calls their corresponding action
            for(int k = 0; k < listSize; k++){
                currentAnimal = zooAnimals.get(k);


                //Wakeup
                System.out.println(keeper.wakeAnimal(currentAnimal));
                System.out.println(currentAnimal.wakeUp());
                textForFile = textForFile + keeper.wakeAnimal(currentAnimal) + "\n";
                textForFile = textForFile + currentAnimal.wakeUp() + "\n";

                //Rollcall
                System.out.println(keeper.rollCall(currentAnimal));
                System.out.println(currentAnimal.makeNoise());
                textForFile = textForFile + keeper.rollCall(currentAnimal) + "\n";
                textForFile = textForFile + currentAnimal.makeNoise() + "\n";

                //Feed Animals
                System.out.println(keeper.feedAnimal(currentAnimal));
                System.out.println(currentAnimal.eat());
                textForFile = textForFile + keeper.feedAnimal(currentAnimal) + "\n";
                textForFile = textForFile + currentAnimal.eat() + "\n";

                //Excerise
                System.out.println(keeper.exerciseAnimal(currentAnimal));
                System.out.println(currentAnimal.roam());
                textForFile = textForFile + keeper.exerciseAnimal(currentAnimal) + "\n";
                textForFile = textForFile + currentAnimal.roam() + "\n";

                //Sleep
                System.out.println(keeper.sleepAnimal(currentAnimal));
                System.out.println(currentAnimal.sleep());
                textForFile = textForFile + keeper.sleepAnimal(currentAnimal) + "\n";
                textForFile = textForFile + currentAnimal.sleep() + "\n";

                //textForFile = textForFile + content);

            }
            //Calls keeper to leave, then adds asterisks to the text for the file for easier seperation of days
            System.out.println(keeper.leave(i)); 
            textForFile = textForFile + keeper.leave(i) + "\n"; 
            textForFile = textForFile + "**************\n";
        }
        Files.writeString(fileName, textForFile);
    }



    public static void main(String args[])  throws IOException
    { 
        ArrayList<Animal> zooAnimals = new ArrayList<Animal>();

        ZooKeeper amy = new ZooKeeper("Amy");

        //Animal creation

        //Canines
        Dog dave = new Dog("Dave");
        Wolf willy = new Wolf("Willy");
        zooAnimals.add(dave);
        zooAnimals.add(willy);

        //Felines
        Cat charlie = new Cat("Charlie");
        Lion leo = new Lion("Leo");
        Tiger tabitha = new Tiger("Tabitha");
        zooAnimals.add(charlie);
        zooAnimals.add(leo);
        zooAnimals.add(tabitha);

        //Crustaceans
        Crab carter = new Crab("Carter");
        Lobster larry = new Lobster("Larry");
        zooAnimals.add(carter);
        zooAnimals.add(larry);

        //Pachyderm
        Elephant ellie = new Elephant("Ellie");
        Hippo harry = new Hippo("Harry");
        Rhino renald = new Rhino("Renald");
        zooAnimals.add(ellie);
        zooAnimals.add(harry);
        zooAnimals.add(renald);

     


        //File IO Output and Weekly Walkthrough
        Path fileName = Path.of("dayatthezoo.out");
        runThroughTheWeek(amy, zooAnimals,  fileName);

    } 

}