import java.util.*;
import java.util.Observable;
import java.util.Observer;
import java.io.IOException;
import java.nio.file.Path;
public class ZooKeeper extends ZooEmployee implements Observer{

    //Local list of all the zoo animals
    private ArrayList<Animal> zooAnimals;
    //Clock Oberservable value
    private ZooClock clockOv;
    //Class Constructor
    //Updates the employeeName in zooEmployee
	public ZooKeeper(String name, Path filepath, ArrayList<Animal> animalsList, ZooClock clock){
		this.employeeName = "Zookeeper " + name;
        this.zooAnimals = animalsList;
        this.fileName = filepath;
        this.clockOv = clock;
	}

    //Method: wakeAnimal
    //Goes through the animal list and does the method action, writes to the file and outputs it to the command line
    public void wakeAnimals() throws IOException {
        String outputText = "";
        Animal currentAnimal;
        int listSize = zooAnimals.size();
        setStatus("wakingAnimals");
        for(int i = 0; i < listSize; i++){
                currentAnimal = zooAnimals.get(i);
                outputText = this.employeeName + " wakes up " + currentAnimal.name + ".";
                System.out.println(outputText);
                writeToFile(outputText);
                
                outputText = currentAnimal.wakeUp();
                System.out.println(outputText);
                writeToFile(outputText);
            }
        

    }

    //Method: rollCall
    //Goes through the animal list and does the method action, writes to the file and outputs it to the command line
    public void rollCall() throws IOException {
        String outputText = "";
        Animal currentAnimal;
        int listSize = zooAnimals.size();
        setStatus("callingAnimals");
        for(int i = 0; i < listSize; i++){
                currentAnimal = zooAnimals.get(i);
                outputText = this.employeeName + " roll calls " + currentAnimal.name + ".";
                System.out.println(outputText);
                writeToFile(outputText);
                
                outputText = currentAnimal.makeNoise();
                System.out.println(outputText);
                writeToFile(outputText);
            }


    }

    //Method: feedAnimal
    //Goes through the animal list and does the method action, writes to the file and outputs it to the command line
    public void feedAnimals() throws IOException {
        String outputText = "";
        Animal currentAnimal;
        int listSize = zooAnimals.size();
        setStatus("feedingAnimals");
        for(int i = 0; i < listSize; i++){
                currentAnimal = zooAnimals.get(i);
                outputText = this.employeeName + " feeds " + currentAnimal.name + ".";
                System.out.println(outputText);
                writeToFile(outputText);
                
                outputText = currentAnimal.eat();
                System.out.println(outputText);
                writeToFile(outputText);
            }

    }

    //Method: exerciseAnimal
    //Goes through the animal list and does the method action, writes to the file and outputs it to the command line
    public void exerciseAnimals() throws IOException {
        String outputText = "";
        Animal currentAnimal;
        int listSize = zooAnimals.size();
        setStatus("exercisingAnimals");
        for(int i = 0; i < listSize; i++){
                currentAnimal = zooAnimals.get(i);
                outputText = this.employeeName + " exercises " + currentAnimal.name + ".";
                System.out.println(outputText);
                writeToFile(outputText);
                
                outputText = currentAnimal.roam();
                System.out.println(outputText);
                writeToFile(outputText);
            }

    }

    //Method: sleepAnimal
    //Goes through the animal list and does the method action, writes to the file and outputs it to the command line
    public void sleepAnimals() throws IOException {
        String outputText = "";
        Animal currentAnimal;
        int listSize = zooAnimals.size();
        setStatus("sleepingAnimals");
        for(int i = 0; i < listSize; i++){
                currentAnimal = zooAnimals.get(i);
                outputText = this.employeeName + " puts " + currentAnimal.name + " to bed.";
                System.out.println(outputText);
                writeToFile(outputText);
                
                outputText = currentAnimal.sleep();
                System.out.println(outputText);
                writeToFile(outputText);
            }
    }
    //Observer overwritten update method
    //Triggered by ZooClock setCurrentHour
    public void update(Observable obs, Object obj){
        String currentHour;
        String outputText;
        try{
            if(obs == this.clockOv){
                currentHour = clockOv.getCurrentHour();
                //Actions with their approrpiate time
                switch(currentHour){
                    case "8 AM":
                        outputText = this.arrive();
                        System.out.println(outputText);
                        writeToFile(outputText);
                        break;
                    case "9 AM":
                        wakeAnimals();
                        break;
                    case "10 AM":
                        rollCall();
                        break;
                    case "1 PM":
                        feedAnimals();
                        break;
                    case "3 PM":
                        exerciseAnimals();
                        break;
                    case "7 PM":
                        sleepAnimals();
                        break;
                    case "8 PM":
                        outputText = this.leave();
                        System.out.println(outputText);
                        writeToFile(outputText);
                        break;

                }
            }

        }catch(IOException e) {
          e.printStackTrace();
        }
    }
}