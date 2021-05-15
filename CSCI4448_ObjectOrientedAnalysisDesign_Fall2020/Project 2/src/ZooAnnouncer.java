import java.util.Observable;
import java.util.Observer;
import java.io.IOException;
import java.nio.file.Path;
public class ZooAnnouncer extends ZooEmployee implements Observer {
	//What announcer is observing
    private ZooKeeper keepOv = null;
    private ZooClock clockOv;
    private ZooFoodServer foodOv = null;
    //Announcer Constructor
    public ZooAnnouncer(String name, ZooKeeper keepObs, ZooFoodServer foodObs, Path filepath, ZooClock clock){
    	this.employeeName = name + " The Zoo Announcer";
        this.keepOv = keepObs;
        this.foodOv = foodObs;
        this.fileName = filepath;
        this.clockOv = clock;
    }

    //Overwritten Obseverer method that is triggered by a ZooEmployee SetStatus Method
    public void update(Observable obs, Object obj){
		String outputText = "Hi this is " + employeeName + ". ";
		//Keeper Responses
	    if(obs == this.keepOv){
	    	String keeperStatus = this.keepOv.getStatus();
	    	switch(keeperStatus){
	    		case "wakingAnimals":
		    			outputText = outputText + this.keepOv.employeeName + " is about to wake up the animals!";
		    			break;
	    		case "callingAnimals":
		    			outputText = outputText + this.keepOv.employeeName + " is about to roll call the animals!";
		    			break;
		    	case "feedingAnimals":
		    			outputText = outputText + this.keepOv.employeeName + " is about to feed the animals!";
		    			break;
		    	case "exercisingAnimals":
		    			outputText = outputText + this.keepOv.employeeName + " is about to exercise the animals!";
		    			break;
		    	case "sleepingAnimals":
		    			outputText = outputText + this.keepOv.employeeName + " is about to put the animals to bed!";
		    			break;
	    	}
	    //FoodServer responses
	    }else if(obs == this.foodOv){
	    	//System.out.println(foodOv.getStatus());
	    	if(foodOv.getStatus().equals("servingLunch")){
	    		outputText = outputText + "Lunch is now being served.";
	    	}else if(foodOv.getStatus().equals("servingDinner")){
	    		outputText = outputText + "Dinner is now being served.";
	    	}  else{
	    		return;
	    	}
	    //Clock Responses
	    }else if(obs == this.clockOv){
	    	String currentHour = clockOv.getCurrentHour();
	    	switch(currentHour){
		    		case "8 AM":
		    			outputText = this.arrive();
		    			break;
		    		case "8 PM":
		    			outputText = this.leave();
		    			break;
		    		}
		    	
	    }
	    //Blanket Response statement

	    System.out.println(outputText);
	    //Work around for method being unable to be extended with throws IOException
	    //https://stackoverflow.com/questions/8707906/error-message-unreported-exception-java-io-ioexception-must-be-caught-or-decla
	    try{
	    	writeToFile(outputText);
	    }catch(IOException e) {
		  e.printStackTrace();
		}
	    
		
    }
}