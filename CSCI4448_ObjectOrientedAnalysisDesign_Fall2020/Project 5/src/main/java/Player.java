import java.util.Observable;

public class Player extends Observable {
    public String name;
    public int playerNum;
    public String role;
    public String color;
    public String state;
    public int viewDistance;
    public String validActionList = "Movement: w,a,s,d\nReport,Idle,Leave";
    private boolean canBeSeen = true;

    public void Player(String color){
        this.color = color;
    }
    public void setState(String newState){
        this.state = newState;
    }
    public String getState(){
        return state;
    }

    public void move(String direction){
        //notify server of moving
        System.out.println(this.name + " Is moving " + direction);
        setState(direction);
        setChanged();
        notifyObservers(this);
    }
    public void report(){
        //notify server
        System.out.println(this.name + " Is reporting a body");
        setState("Report");
        setChanged();
        notifyObservers(this);
    }

    public void invalidAction(){
        setState("Invalid Action");
        setChanged();
        notifyObservers(this);
    }
    public void idle(){
        setState("Idle");
        setChanged();
        notifyObservers(this);
    }
    public int getViewDistance(){
        return viewDistance;
    }

    public void setViewDistance(int setDistance){
        this.viewDistance = setDistance;
    }

    public void setCanBeSeen(boolean value){
        this.canBeSeen = value;
    }

    public String getValidActions(){

        return validActionList;
    }

}
