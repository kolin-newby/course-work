import java.util.Observable;
import java.util.Observer;
import java.io.IOException;
import java.nio.file.Path;
public class ZooFoodServer extends ZooEmployee implements Observer{

	//Clock Oberservable value
    private ZooClock clockOv;
    //Class Constructor
    //Updates the employeeName in zooEmployee
	public ZooFoodServer(String name, Path filepath, ZooClock clock){
		this.employeeName = name + " The Food Server";
		this.fileName = filepath;
		this.clockOv = clock;
	}

    public void clean() throws IOException {
    	String outputText = this.employeeName + " is now cleaning.";
    	System.out.println(outputText);
    	writeToFile(outputText);

    	this.setStatus("cleaning");
    }

    public void serveFood(String time) throws IOException {
    	String outputText = this.employeeName + " is now serving food.";
    	System.out.println(outputText);
    	writeToFile(outputText);

    	if(time.equals("12 PM")){
    		this.setStatus("servingLunch");
    	}else{
    		this.setStatus("servingDinner");
    	}
    	
    }

    public void makeFood() throws IOException {
    	String outputText = this.employeeName + " is now making food.";
    	System.out.println(outputText);
    	writeToFile(outputText);

    	this.setStatus("making");
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
		    		case "10 AM":
		    			makeFood();
		    			break;
		    		case "12 PM":
		    			serveFood("12 PM");
		    			break;
		    		case "2 PM":
		    			clean();
		    			break;
		    		case "4 PM":
		    			makeFood();
		    			break;
		    		case "5 PM":
		    			serveFood("5 PM");
		    			break;
		    		case "6 PM":
		    			clean();
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
