import java.util.*;

public abstract class Customer{
    String customerType;

    public abstract Order placeOrder(ArrayList<Stock> avalStock);
    public String getType(){
        return this.customerType;
    }

    //Checks the avalStock list and returns a list of integers of indexes that meet the minimum stock required to buy
    protected ArrayList<Integer> randomOfCurrentStock(ArrayList<Stock> avalStock, int min){
        ArrayList<Integer> rando = new ArrayList<Integer>();
        int i;
        int stockSize = avalStock.size();
        for(i = 0; i < stockSize; i++){
            if(avalStock.get(i).getStock() > min){
                rando.add(i);
            }
        }
        return rando;


    }

    //Inheritted method to give a random chance of adding extras to a roll
    //Chance of up to 3 sauces, 1 filling and 
    protected Roll addExtras(Roll roll){
        int randRoll = (int)Math.floor(Math.random() * 3);
        int i;

        //Add extra Sauce
        for(i = 0; i < randRoll; i++){
            roll = new ExtraSauce(roll);
        }

        randRoll = (int)Math.floor(Math.random() * 1);
        for(i = 0; i < randRoll; i++){
            roll = new ExtraFilling(roll);
        }

        randRoll = (int)Math.floor(Math.random() * 2);
        for(i = 0; i < randRoll; i++){
            roll = new ExtraToppings(roll);
        }
        return roll;
    }
}
