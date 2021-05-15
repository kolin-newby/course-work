import java.util.Observable;
import java.util.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public abstract class ZooEmployee extends Observable{
    //Common tasks for all ZooEmployees
    String employeeName;
    protected String status = "";
    Path fileName;
    //Abstrast Methods for inheritted classes

    //Method: arrive
    //Returns a string with that the employee has arrived at the zoo
    public String arrive(){

    	return this.employeeName + " arrives at the Zoo.";
    	
    }
    
	//Method: arrive
    //Returns a string that the employee has left the zoo
    public String leave(){
    	return this.employeeName + " leaves the Zoo.";
    }

    //Triggers the observer (ZooAnnouncer)
    public void setStatus(String newStatus){
        this.status = newStatus;
        setChanged();
        notifyObservers();
        //System.out.println("Status: " + status);
    }

    //Getter for status
    public String getStatus(){
        return status;
    }

    //Write to file inheritted method
    protected void writeToFile(String outputText) throws IOException {
        outputText = outputText + "\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);
    }

    
}   