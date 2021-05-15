import java.util.*;

public class Order{
    ArrayList<Roll> rollsOrdered = new ArrayList<Roll>();
    ArrayList<Stock> simpleOrder = new ArrayList<Stock>();
    String customerType;
    int day;
    boolean impactedOrder = false;
    double saleCost;

    public Order(Customer c, ArrayList<Roll> r){
       this.rollsOrdered = r;
       this.customerType = c.getType();
    }
    public Order(Customer c){
       this.rollsOrdered = null;
       this.customerType = c.getType();
    }
    public Order(String c, ArrayList<Roll> r){
       this.rollsOrdered = r;
       this.customerType = c;
    }
    public Order(String c){
       this.rollsOrdered = null;
       this.customerType = c;
    }


    //Calculates total cost of sale
    public double runThroughSale(){
        int listSize = rollsOrdered.size();

        int i;
        Roll temp;
        double totalCost = 0;
        for(i = 0; i < listSize; i++){
            temp = rollsOrdered.get(i);
            totalCost = totalCost + temp.cost();
        }

        return totalCost;
    }

    
    //Takes the order and converts it into a stock of unique order sets
    //Ex: 1 Pastry extra filling, 1 Pastry
    public void simplify(ArrayList<Stock> ordersPerRoll){
        int i,k;
        Roll temp;
        int simpleOrderSize = this.simpleOrder.size();
        int orderSize = this.rollsOrdered.size();
        Stock stockAdder;
        boolean checker;
        this.saleCost = runThroughSale();
        for(i = 0; i < orderSize; i++){
            checker = true;
            
            temp = rollsOrdered.get(i);
            //System.out.println(temp.getDescription());
            for(k = 0; k < simpleOrderSize; k++){
                if(simpleOrder.get(k).getRoll().getDescription().equals(temp.getDescription())){
                    //System.out.println(simpleOrder.get(k).lengthyPrint());
                    simpleOrder.get(k).addStock(1);
                    checker = false;
                    break;
                }


            }

            for(k =0; k < ordersPerRoll.size(); k++){
                if(ordersPerRoll.get(k).getRoll().getType().equals(temp.getType())){
                    ordersPerRoll.get(k).addStock(1);
                }
            }
            if(checker){
                //System.out.println("Here");
                stockAdder = new Stock(temp,1);
                simpleOrder.add(stockAdder);
            }

            simpleOrderSize = this.simpleOrder.size();
        }
        //System.out.println(simpleOrderSize);
        
    }
    //Print the order's simplified version
    public String printSimplify(){
        String outputString = "On day " + day + " a " + customerType + " customer ordered: \n";
        int i;
        int simpleOrderSize = this.simpleOrder.size();
        for(i = 0; i < simpleOrderSize; i++){
            outputString = outputString  + simpleOrder.get(i).lengthyPrint() +"  ";
            if(i % 3 == 2 && simpleOrderSize != 3){
                outputString = outputString + "\n";
            }
        }
        if(simpleOrderSize == 0){
            outputString = outputString + "Nothing due to an outtage";
        }else{
            outputString = outputString + "\nFor $"+ (float)Math.round(this.saleCost * 100.0) / 100.0;
        }
        
        return outputString;
    }
    //Output the order as a string for ease of recording data
    public String printOrder(){
        String outputString = customerType + " Customer ordered ";

        int i;
        Roll temp;
        int orderSize = this.rollsOrdered.size();
        for(i = 0; i < orderSize; i++){
            temp = rollsOrdered.get(i);
            outputString = outputString + " A " + temp.getDescription();
        }
        outputString = outputString + "\n";
        System.out.println(outputString);
        return outputString;
    }

    //Getters and Setters
    public ArrayList<Stock> getSimpleOrder(){
        return this.simpleOrder;
    }

    public Roll getRoll(int i){
        return rollsOrdered.get(i);
    }

    public int rollsOrderedSize(){
        return rollsOrdered.size();
    }

    public void orderImpacted(){
        this.impactedOrder = true;
    }

    public void setRollsOrdered(ArrayList<Roll> r){
        this.rollsOrdered = r;
    }

    public double getSaleCost(){
        return this.saleCost;
    }
    public boolean orderWasImpacted(){
        return this.impactedOrder;
    }

    public void setDay(int d){
        this.day = d;
    }

    public String getCustomerType(){
        return this.customerType;
    }
}
