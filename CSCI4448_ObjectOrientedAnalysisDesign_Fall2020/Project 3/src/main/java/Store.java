import java.util.Observable;
import java.util.Observer;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.*;

public class Store extends Observable implements Observer {

	ArrayList<Order> orderLog = new ArrayList<Order>();
	int outages = 0;
	double currentSales = 0;
	int inventoryLevel = 30;
	ArrayList<Stock> inventory = new ArrayList<Stock>();
	ArrayList<Stock> inventoryOrdersDone = new ArrayList<Stock>();
	ArrayList<Stock> ordersPerRoll = new ArrayList<Stock>();
	int day;
	int[] dailyOuttages = new int[30];
	double totalMoneyMade = 0.0;
	double dailyMoneyMade = 0.0;
	double cateringDailyMade = 0.0;
	double businessDailyMade = 0.0;
	double casualDailyMade = 0.0;
	int cateringOuttages = 0;
	int businessOuttages = 0;
	int casualOuttages = 0;
	String status = "";
	int dailyDisruptions = 0;
	int totalDisruptions = 0;
	int lastOrderOfThePreviousDay = 0;
	boolean noInventoryClosure = false;
	private Calendar calOv = null;

	public Store(Calendar calObs, int iL){
		inventoryLevel = iL;
		this.calOv = calObs;
		Roll sRoll = new SpringRoll();
		Roll eRoll = new EggRoll();
		Roll pRoll = new PastryRoll();
		Roll saRoll = new SausageRoll();
		Roll jRoll = new JellyRoll();

		Stock sStock = new Stock(sRoll, inventoryLevel);
		Stock eStock = new Stock(eRoll, inventoryLevel);
		Stock pStock = new Stock(pRoll, inventoryLevel);
		Stock saStock = new Stock(saRoll, inventoryLevel);
		Stock jStock = new Stock(jRoll, inventoryLevel);

		//Current inventory
		this.inventory.add(sStock);
		this.inventory.add(eStock);
		this.inventory.add(pStock);
		this.inventory.add(saStock);
		this.inventory.add(jStock);

		//Stock struct multi purposed to keep track of how many times we have ran out of stock of the given roll
		sStock = new Stock(sRoll, 0);
		eStock = new Stock(eRoll, 0);
		pStock = new Stock(pRoll, 0);
		saStock = new Stock(saRoll, 0);
		jStock = new Stock(jRoll, 0);
		this.inventoryOrdersDone.add(sStock);
		this.inventoryOrdersDone.add(eStock);
		this.inventoryOrdersDone.add(pStock);
		this.inventoryOrdersDone.add(saStock);
		this.inventoryOrdersDone.add(jStock);
		//Stock struct multi purposed to keep track of how many of each type of rolls were sold overall
		sStock = new Stock(sRoll, 0);
		eStock = new Stock(eRoll, 0);
		pStock = new Stock(pRoll, 0);
		saStock = new Stock(saRoll, 0);
		jStock = new Stock(jRoll, 0);
		this.ordersPerRoll.add(sStock);
		this.ordersPerRoll.add(eStock);
		this.ordersPerRoll.add(pStock);
		this.ordersPerRoll.add(saStock);
		this.ordersPerRoll.add(jStock);
	}

	//Takes a list of customers and creates all of their orders
	public void runThroughCustomers(ArrayList<Customer> customers){
		int cSize = customers.size();
		int i;
		Order tempOrder;
		Customer tempCustomer;
		for(i = 0; i < cSize; i++){
			if(checkStock()){
				tempCustomer = customers.get(i);
				//printInventory();
				tempOrder = tempCustomer.placeOrder(inventory);
				//System.out.println("Day order: " + i);
				//tempOrder.printOrder();
				handleOrder(tempOrder);
				
			}else{
				//System.out.println();
				noInventoryClosure = true;
				return;
			}
		}
	}


	//Parses the order of a customer
	private void handleOrder(Order order){
		
		order.simplify(ordersPerRoll);
		order.setDay(day);
		salesPerRoll();
		double orderSaleCost = order.getSaleCost();
		dailyMoneyMade = dailyMoneyMade + orderSaleCost;
		totalMoneyMade = totalMoneyMade + orderSaleCost;
		if(order.orderWasImpacted()){
			dailyDisruptions = dailyDisruptions + 1;
		}
		orderLog.add(order);

		switch(order.getCustomerType()){
			case "Casual":
				casualDailyMade = casualDailyMade + orderSaleCost;
				if(order.orderWasImpacted()){
					casualOuttages = cateringOuttages + 1;
				}
			break;
			case "Catering":
				cateringDailyMade = cateringDailyMade + orderSaleCost;
				if(order.orderWasImpacted()){
					cateringOuttages = cateringOuttages + 1;
				}
			break;
			case "Business":
				businessDailyMade = businessDailyMade + orderSaleCost;
				if(order.orderWasImpacted()){
					businessOuttages = businessOuttages + 1;
				}
			break;
		}
	}

	//Get what rolls can be bought
	public ArrayList<Stock> getAvaiableStock (){
		return inventory;
	}
	
	//Checks if the store can stay open
	private boolean checkStock(){
        int i;
        int inventorySize = inventory.size();
        int count = 0;
        for(i = 0; i < inventorySize; i++){
            count = count + inventory.get(i).getStock();

        }
        //System.out.println("Count was: " + count);
        if(count < 1){
            return false;
        }else{
            return true;
        }
    }

	//Used to print the inventory and send the inventory to the observer
	public void printInventory(){
		int i;
		int listSize = inventory.size();
		Roll temp;
		String outputText;
		outputText = "Inventory Stocks Per Roll: ";
		//outputText = inventory.get(0).getRoll().getType() + " Roll Current stock: " + inventory.get(0).getStock();
		for(i = 0; i < listSize; i++){
			if(i % 3 == 0){
				outputText = outputText + "\n";
			}
			outputText = outputText + inventory.get(i).getRoll().getType() + " : " + inventory.get(i).getStock() + " ";
		}
		System.out.println(outputText);
		this.status = outputText;
		setChanged();
        notifyObservers();
	}

	//Used to print the inventory and send the inventory to the observer
	public String salesPerRoll(){
		int i;
		int listSize = ordersPerRoll.size();
		Roll temp;
		String outputText;
		outputText = "Sales Per Roll: ";
		//outputText = inventory.get(0).getRoll().getType() + " Roll Current stock: " + inventory.get(0).getStock();
		for(i = 0; i < listSize; i++){
			if(i % 3 == 0){
				outputText = outputText + "\n";
			}
			outputText = outputText + ordersPerRoll.get(i).getRoll().getType() + "s : " + ordersPerRoll.get(i).getStock() + " ";
		}
		//System.out.println(outputText);
		return outputText;
	}

	//Used to print the stocks that have had to be restocked and send the inventory to the observer
	public void printRestocks(){
		int i;
		int listSize = inventoryOrdersDone.size();
		Roll temp;
		String outputText;
		outputText = "\nInventory Restock Orders Per Roll: ";
		//outputText = inventoryOrdersDone.get(0).getRoll().getType() + " Roll Current stock: " + inventoryOrdersDone.get(0).getStock();

		for(i = 0; i < listSize; i++){
			if(i % 3 == 0){
				outputText = outputText + "\n";
			}
			outputText = outputText  + inventoryOrdersDone.get(i).getRoll().getType() + ": " + inventoryOrdersDone.get(i).getStock() + " ";

		}

		System.out.println(outputText);
		this.status = outputText;
		setChanged();
        notifyObservers();
	}

	//Used to print daily orders
	public void dailyOrders(){
		int i;
		int listSize = orderLog.size();
		Roll temp;
		String outputText;
		outputText = "Daily Customer Orders: ";
		for(i = lastOrderOfThePreviousDay; i < listSize; i++){
			outputText = outputText + "\n" + orderLog.get(i).printSimplify();
		}

		System.out.println(outputText);
		this.status = outputText;
		setChanged();
        notifyObservers();
	}

	//Used to print the daily overall stats
	public void dailyStats(){
		String outputString = "\nTotal Money Made Today: $" + (float)Math.round(dailyMoneyMade * 100.0) / 100.0 + " \n";
		outputString = outputString + "Catering Sales: $" + (float)Math.round(cateringDailyMade * 100.0) / 100.0 + "   Business Sales: $" 
		+ (float)Math.round(businessDailyMade * 100.0) / 100.0  +"   Casual Sales: $" + (float)Math.round(casualDailyMade * 100.0) / 100.0 +"\n";
		

		outputString = outputString  + "\nTotal Outages Today: " + dailyDisruptions + " \n";
		outputString = outputString + "Catering Outages: " + cateringOuttages + "   Business Outages: " + businessOuttages  +"   Casual Outages: " + casualOuttages +"\n";

		System.out.println(outputString);
		this.status = outputString;
		setChanged();
        notifyObservers();
	}

	//Used to reset a roll for when an outage occurs
	private void resetAvailable(Roll roll){
		Stock replacementStock = new Stock(roll, inventoryLevel);

		int i;
		int listSize = inventory.size();
		Roll temp;
		String rollType = roll.getType();
		for(i = 0; i < listSize; i++){
			if(inventory.get(i).getRoll().getType().equals(rollType)){
				inventory.set(i,replacementStock);
			}
		}
	}


	//Different version of resetAvailable
	public void dailyInventoryCheck(){

		int i;
		Stock tempStock, tempRestockTracker;
		int listSizeInventory = this.inventory.size();
		for(i = 0; i < listSizeInventory; i++){

				if(this.inventory.get(i).getStock() == 0){
					//If stock is 0 add 1 to the out of stock counnter then reset it to the inventory level
					this.inventory.get(i).setStock(inventoryLevel);
					this.inventoryOrdersDone.get(i).addStock(1);
					//inventoryOrdersDone.set(i,tempRestockTracker);
					//tempStock.setStock(inventoryLevel);
					//this.inventory.set(i,tempStock);
				}
			}

	}



	//Used to print the overall stats after the 30 days
	private String endStats(){
        String outputString = "End of 30 days Stats";


        outputString = outputString + "\n" + salesPerRoll();
        outputString = outputString + "\n" + "Total Money Made: $" + (float)Math.round(totalMoneyMade * 100.0) / 100.0;
        outputString = outputString + "\n" + "Total Number of Orders Impacted by Outtages: " + totalDisruptions;
        return outputString;
    }

	//Return status
	public String getStatus(){
		return this.status;
	}


	//Used to write to an extra textfile for graphing
	public void writeToTxtStats() throws IOException{
		Path fileName = Path.of("stats.out");
        
		String outputText = "Day " + day + ", Spring " + inventory.get(0).getStock() + ", Egg " + inventory.get(1).getStock() 
      + ", Sausage " + inventory.get(2).getStock() + ", Jelly " + inventory.get(3).getStock()
	+   ", Pastry " + inventory.get(4).getStock() + ", Outages " + dailyDisruptions+   "";
		outputText = outputText + "\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);
		//Day x, Spring x, Egg x, Sausage x, Jelly x, Pastry x, Outages x \n
	}

	// public DefaultCategoryDataset addPoint(DefaultCategoryDataset data) {
	// 	data.addValue(dailyMoneyMade,"Sales in Day","Day");
	// 	return data;
	// }


	//Called when days change in Calendar
	public void update(Observable obs, Object obj){
		if(obs == this.calOv){
				//Daily open routine
				if(this.calOv.status.equals("open")){
					day = this.calOv.getDay();
					runThroughCustomers(this.calOv.getDailyCust());
				//Done on the last day
				}else if (this.calOv.status.equals("lastDay")){
					this.status = endStats();
					System.out.println(this.status);
					setChanged();
        			notifyObservers();
				}
				//Day start notice
				else if(this.calOv.getStartOfDay()){
					cateringDailyMade = 0.0;
					businessDailyMade = 0.0;
					casualDailyMade = 0.0;
					dailyDisruptions = 0;
					cateringOuttages = 0;
	 				businessOuttages = 0;
	 				casualOuttages = 0;
	 				lastOrderOfThePreviousDay = orderLog.size();
					this.status = "Start of Day Inventory";
					System.out.println(status);
					setChanged();
        			notifyObservers();
        			dailyInventoryCheck();
					printInventory();
				//Day End Notice
				}else{
					this.status = "End of Day";
					totalDisruptions = dailyDisruptions + totalDisruptions;
					System.out.println(status);
					setChanged();
        			notifyObservers();
        			dailyOrders();
        			dailyStats();
        			printInventory();
        			printRestocks();
        			if(noInventoryClosure){
        				this.status = "Closed due to no inventory.";
        				setChanged();
        				notifyObservers();
        			}

        			//For stats
        			try{
				    	writeToTxtStats();
				    }catch(IOException e) {
					  e.printStackTrace();
					}
				    
				}

				
				

				
			}
		}



}
