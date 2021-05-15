public class Stock{
    Roll roll;
    int instock;

    public Stock(Roll rollType, int curStock) {
        this.roll = rollType;
        this.instock = curStock;
    }

    public int getStock(){
        return this.instock;
    }
    public Roll getRoll(){
        return this.roll;
    }

    public void reduceStock(int i){
        this.instock = instock - i;
    }

    public void setStock(int i){
        this.instock = i;
    }

    public void addStock(int i){
        this.instock = this.instock+i;
    }
    public void printStock(){
        System.out.println(roll.getType() + ": " + instock);
    }

    public String lengthyPrint(){
        String returnString;
        returnString = this.instock + " " + this.roll.getDescription();

        return returnString;
    }
}
