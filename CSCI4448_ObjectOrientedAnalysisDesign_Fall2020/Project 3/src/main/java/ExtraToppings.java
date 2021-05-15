public class ExtraToppings extends Extras {

    public ExtraToppings(Roll roll){
        this.roll = roll;
    }

    public String getDescription(){
        return roll.getDescription() + ", extra topping";
    }

    public double cost(){
        String type = roll.getType();
        double cost = roll.cost();
        switch (type){
            case "Spring":
                return cost + .20;
            case "Egg":
                return cost + .99;
            case "Sausage":
                return cost + 1.99;
            case "Jelly":
                return cost + 1.49;
            case "Pastry":
                return cost + 2.49;
            default:
                System.out.println("Decorator Type is not working.");
                return 1.00;
        }
    }
}
