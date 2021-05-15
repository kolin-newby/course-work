public abstract class Roll {
    String description = "Unknown Roll";
    String type = "unknown";

    public String getDescription(){
        return description;
    }

    public String getType(){
        return type;
    }
    public abstract double cost();
}
