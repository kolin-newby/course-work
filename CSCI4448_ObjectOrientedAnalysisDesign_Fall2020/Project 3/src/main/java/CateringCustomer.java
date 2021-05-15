import java.util.*;

public class CateringCustomer extends Customer{
	public CateringCustomer(){
		this.customerType = "Catering";
	}
    // Orders 15 rolls, 3 sets of 5 rolls of random types.
    // Will take any number of rolls of any available type up to 15 if original order cannot be placed.
    public Order placeOrder(ArrayList<Stock> avalStock) {
    	Order returnOrder = new Order(customerType);

        ArrayList<Roll> order = new ArrayList<Roll>();
        

        int qty = 15;
        int completeGroups = 3;
        int rollsOrdered = 0;
        int rollGroups = 0;

        ArrayList<Integer> randomList = randomOfCurrentStock(avalStock,5);
        ArrayList<Integer> choices = new ArrayList<Integer>();
        int randomSize = randomList.size();
        int rollType;
        int i;
        boolean checker = true;
        int newStock;

        //3 Random sets of 5 
        Collections.shuffle(randomList);
        if(randomSize >= 3){
        	for(i = 0; i <3; i++){
        		order.addAll(setOf5(avalStock,randomList.get(i)));
        	}
        	returnOrder.setRollsOrdered(order);
        	return returnOrder;
        	 
        }//2 Random sets of 5  
        else if(randomSize > 1){
        	Collections.shuffle(randomList);
        	for(i = 0; i <2; i++){
        		order.addAll(setOf5(avalStock,randomList.get(i)));

        	}
        	rollsOrdered = 10;
        	checker = false;
        }//1 Random sets of 5  
        else if(randomSize > 0 && checker){
        	Collections.shuffle(randomList);
        	for(i = 0; i <1; i++){
        		order.addAll(setOf5(avalStock,randomList.get(i)));
        	}
        	rollsOrdered = 5; 
        }

        returnOrder.orderImpacted();

        randomList = randomOfCurrentStock(avalStock,0);
        randomSize = randomList.size();

        //Extra solos
        while (rollsOrdered < qty && randomSize != 0) {

            int randRoll = (int)Math.floor(Math.random() * randomSize);
            rollType = randomList.get(randRoll);

            Stock tmp = avalStock.get(rollType);
            order.add(addExtras(tmp.getRoll()));
            
            avalStock.get(rollType).reduceStock(1);//(rollType, tmp); //replaces stock in avalStock list with tmp stock (this is to make sure the instock variable is up to date each iteration of the loop)
            rollsOrdered++;

        	randomList = randomOfCurrentStock(avalStock,0);
        	randomSize = randomList.size();
        }
        returnOrder.setRollsOrdered(order);
        return returnOrder;

    }


    private ArrayList<Roll> setOf5(ArrayList<Stock> avalStock, int rollType){
    	ArrayList<Roll> order = new ArrayList<Roll>();
    	int i;
        for( i = 0; i <5; i++){
            Stock tmp = avalStock.get(rollType);
            order.add(addExtras(tmp.getRoll()));
            avalStock.get(rollType).reduceStock(1);
            //(rollType, tmp); //replaces stock in avalStock list with tmp stock (this is to make sure the instock variable is up to date each iteration of the loop)

        }

        return order;
    }
}
