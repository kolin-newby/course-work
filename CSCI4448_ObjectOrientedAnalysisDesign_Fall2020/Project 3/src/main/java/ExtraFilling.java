public class ExtraFilling extends Extras {

    public ExtraFilling(Roll roll){
        this.roll = roll;
    }
 
    public String getDescription(){
        return roll.getDescription() + ", extra filling";
    }

    public double cost(){
        String type = roll.getType();
        double cost = roll.cost();
        switch (type){
            case "Spring":
                return cost + .15;
            case "Egg":
                return cost + .75;
            case "Sausage":
                return cost + 1.00;
            case "Jelly":
                return cost + .50;
            case "Pastry":
                return cost + .80;
            default:
                System.out.println("Decorator Type is not working.");
                return 1.00;
        }
    }
}
