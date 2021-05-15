import java.util.*;

public class BusinessCustomer extends Customer{
    public BusinessCustomer(){
        this.customerType = "Business";
    }
    // Orders 10 rolls, 2 of each type.
    // Only makes order if it can be filled exactly to specifications.
    public Order placeOrder(ArrayList<Stock> avalStock) {
        Order returnOrder = new Order(customerType);

        ArrayList<Roll> order = new ArrayList<Roll>();
        Set<Roll> out = new HashSet<Roll>();

        int qty = (int)Math.ceil(Math.random() * 3);
        int rollsOrdered = 0;

        ArrayList<Integer> randomList = randomOfCurrentStock(avalStock,11);
        boolean inStock = true;
        int rollType;
        int i, k;
        for(i =0; i <5; i++){
            if(avalStock.get(i).getStock() < 10){
                inStock = false;
            }
        }
        
        if(inStock){
            for(i = 0; i < 5; i++){
                Stock tmp = avalStock.get(i);
                for(k = 0; k < 10; k++){
                    order.add(addExtras(tmp.getRoll()));
                    avalStock.get(i).reduceStock(1);

                }

            }
        }else{
            returnOrder.orderImpacted();
        }

        returnOrder.setRollsOrdered(order);
        return returnOrder;
    }
}
