public abstract class Extras extends Roll {
    public Roll roll;
    public abstract String getDescription();
    public String getType(){
        return roll.getType();
    }


}