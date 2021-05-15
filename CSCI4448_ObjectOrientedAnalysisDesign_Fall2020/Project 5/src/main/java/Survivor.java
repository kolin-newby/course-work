public class Survivor extends Player {
    public Survivor() {
        super();
    }

    public void Activate(){
        //activate a task
        String tempName = "Player " + this.name;
        System.out.println(tempName + " Is activating");
        setState("Activate");
        setChanged();
        notifyObservers(this);
    }

    public String getValidActions(){

        return super.getValidActions() + "\nSurvivor Only: Activate";
    }
}
