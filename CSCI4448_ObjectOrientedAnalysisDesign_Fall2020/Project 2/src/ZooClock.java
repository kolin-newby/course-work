import java.util.Observable;
import java.util.Observer;
import java.util.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class ZooClock extends Observable{

	//Current increment tracker
    private int currentIncrement = 0;
    //Hour string array
    private String hourList[] = {"8 AM","9 AM","10 AM","11 AM",
    							 "12 PM","1 PM","2 PM","3 PM","4 PM",
    							 "5 PM","6 PM","7 PM","8 PM"
    							};
    //Max length of the array to prevent overflow
    private static int maxIncrement = 13;
    //Current status
    private String currentHour;
    //Filename to write to
    private Path fileName;

    //Constructor
    public ZooClock(Path filePath){
        this.currentIncrement = 0;
    	this.fileName = filePath;
    }

    //Method to increment the hour
    private void incrementHour(){
        setCurrentHour(hourList[currentIncrement]);
        this.currentIncrement = this.currentIncrement + 1;
        

    }

    //Calls runThroughDay for every day of the week
    public void runThroughWeek(){
    	for(int i = 1; i <= 7; i++ ){

    		runThroughDay(i+"");
    		this.currentIncrement = 0;
    	}
    	

    }
    //Format and calls the correct methods to run through a day
    public void runThroughDay(String day){
    	String outputText;
    	outputText = "It is now Day " + day;
    	System.out.println(outputText);
    	try{
    		writeToFile("*****************");
	    	writeToFile(outputText);
	    }catch(IOException e) {
		  e.printStackTrace();
		}
    	for(int i = 0; i < maxIncrement; i++){

    		incrementHour();

    	}
    }
    //Method that triggers observers on hour upddate
    public void setCurrentHour(String newStatus){
        this.currentHour = newStatus;
        String outputText = "It is now " + currentHour;
        System.out.println(outputText);
        try{
	    	writeToFile(outputText);
	    }catch(IOException e) {
		  e.printStackTrace();
		}
        setChanged();
        notifyObservers();
    }
    //Getter
    public String getCurrentHour(){
        return this.currentHour;
    }

    private void writeToFile(String outputText) throws IOException {
        outputText = outputText + "\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);
    }

}