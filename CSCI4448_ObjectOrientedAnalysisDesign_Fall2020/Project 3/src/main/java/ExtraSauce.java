public class ExtraSauce extends Extras {

    public ExtraSauce(Roll roll){
        this.roll = roll;
    }

    public String getDescription(){
        return roll.getDescription() + ", extra sauce";
    }

    public double cost(){
        String type = roll.getType();
        double cost = roll.cost();
        switch (type){
            case "Spring":
                return cost + .20;
            case "Egg":
                return cost + .25;
            case "Sausage":
                return cost + .55;
            case "Jelly":
                return cost + .50;
            case "Pastry":
                return cost + 1.00;
            default:
                System.out.println("Decorator Type is not working.");
                return 1.00;
        }
    }
}
