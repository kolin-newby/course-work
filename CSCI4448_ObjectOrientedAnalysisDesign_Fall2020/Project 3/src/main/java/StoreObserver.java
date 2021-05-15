import java.util.Observable;
import java.util.Observer;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
public class StoreObserver implements Observer {
	//What StoreObserver is observing
    private Store storeOv = null;
    private Calendar calOv = null;
    private Path fileName = null;
    //Observer Constructor
    public StoreObserver(Store storeObv, Calendar calObv, Path filepath){
    	this.storeOv = storeObv;
    	this.calOv = calObv;
    	this.fileName = filepath;
    }

    //Overwritten Obseverer method that is triggered by a Calendar or Store
    public void update(Observable obs, Object obj){
    	String outputText = "";

    	//Store Observable
	    if(obs == this.storeOv){
	    	outputText = this.storeOv.getStatus();
	    //Calendar Observable
	    }else if(obs == this.calOv){
	    	if(this.calOv.getStartOfDay() == false){
	    		return;
	    	}
	    	else if(this.calOv.status.equals("open") || this.calOv.status.equals("lastDay")){
	    		return;
	    	}
	    	outputText ="\n" + this.calOv.getStatus() + "\n";
	    }
	    

	    //System.out.println(outputText);
	    //Work around for method being unable to be extended with throws IOException
	    //https://stackoverflow.com/questions/8707906/error-message-unreported-exception-java-io-ioexception-must-be-caught-or-decla
	    try{
	    	writeToFile(outputText);
	    }catch(IOException e) {
		  e.printStackTrace();
		}
	    
		
    }

    //Write to file inheritted method
    private void writeToFile(String outputText) throws IOException {
        outputText = outputText + "\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);
    }
}