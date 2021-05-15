import java.util.*;

public class CasualCustomer extends Customer{


	public CasualCustomer(){
		this.customerType = "Casual";
	}
    // Orders 1 to 3 rolls of random type.
    // Will attempt to select different roll if initial roll ordered is out of stock for the day.
    public Order placeOrder(ArrayList<Stock> avalStock) {
    	Order returnOrder = new Order(customerType);

        ArrayList<Roll> order = new ArrayList<Roll>();
        Set<Roll> out = new HashSet<Roll>();

        int qty = (int)Math.ceil(Math.random() * 3);
        int rollsOrdered = 0;

        ArrayList<Integer> randomList = randomOfCurrentStock(avalStock,0);
        int randomSize = randomList.size();
        int rollType;
        while (rollsOrdered < qty && randomSize != 0) {

            int randRoll = (int)Math.floor(Math.random() * randomSize);
            rollType = randomList.get(randRoll);

            Stock tmp = avalStock.get(rollType);
            order.add(addExtras(tmp.getRoll()));
            //tmp.instock--; //sets the ordered roll's instock down by 1.
            avalStock.get(rollType).reduceStock(1);//(rollType, tmp); //replaces stock in avalStock list with tmp stock (this is to make sure the instock variable is up to date each iteration of the loop)
            rollsOrdered++;
        	randomList = randomOfCurrentStock(avalStock,0);
        	randomSize = randomList.size();
        }
        if(randomSize != 5){
        	returnOrder.orderImpacted();
        }
        returnOrder.setRollsOrdered(order);
        return returnOrder;
    }
    
}