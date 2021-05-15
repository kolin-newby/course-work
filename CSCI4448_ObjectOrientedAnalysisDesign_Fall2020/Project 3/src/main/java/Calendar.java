import java.util.Observable;
import java.util.Observer;
import java.util.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class Calendar extends Observable{

    //Current status
    private int day;
    boolean startOfDay;
    String status = "";
    private int lastDay = 30;
    private ArrayList<Customer> dailyCust = new ArrayList<Customer>();
    //Constructor
    public Calendar(){
        this.day = 1;
    }

    //Calls runThroughDay for every day of the month
    public void runThroughMonth(){
    	for(int i = 1; i <= lastDay; i++ ){
            this.day = i;
    		startDay();

            generateDailyCustomers();
            status = "open";
            setChanged();
            notifyObservers();


            endDay();
            System.out.println();
    	}

        status = "lastDay";
    	setChanged();
        notifyObservers();

    }

    //Start of the day methods
    private void startDay(){
        this.status = "Day " + this.day;
        this.startOfDay = true;
        System.out.println(status);
        setChanged();
        notifyObservers();
    }

    //End of the day methods
    private void endDay(){
        this.startOfDay = false;
        this.status = "Day " + this.day;
        //System.out.println(status);
        setChanged();
        notifyObservers();
    }



    //Generates a daily set of random set of customers
    private void generateDailyCustomers(){

        dailyCust = new ArrayList<Customer>();

        int casual = (int)Math.ceil(Math.random() * 12); //1 to 12 casual cust.
        int business = (int)Math.ceil(Math.random() * 3); //1 to 3 business cust.
        int catering = (int)Math.ceil(Math.random() * 3); //1 to 3 catering cust.

        for (int i = 0; i < casual; i++) { //add 1 to 12 casual customers to the daily customers list
            Customer tmp = new CasualCustomer();
            this.dailyCust.add(tmp);
        }
        for (int i = 0; i < business; i++) { //add 1 to 3 business customers to the daily customers list
            Customer tmp = new BusinessCustomer();
            this.dailyCust.add(tmp);
        }
        for (int i = 0; i < catering; i++) { //add 1 to 3 catering customers to the daily customers list
            Customer tmp = new CateringCustomer();
            this.dailyCust.add(tmp);
        }
        //https://www.geeksforgeeks.org/shuffle-or-randomize-a-list-in-java/
        Collections.shuffle(dailyCust);
    }

    //Getters
    public int getDay(){
        return this.day;
    }

    public String getStatus(){
        return this.status;
    }

    public boolean getStartOfDay(){
        return this.startOfDay;
    }

    public ArrayList<Customer> getDailyCust(){
        return this.dailyCust;
    }

}