public class Murderer extends Player{

    private static Murderer murderer;
    private Murderer() {
        super();
    }

    public static Murderer getInstance(){
        if(murderer == null){
            murderer = new Murderer();
        }

        return murderer;
    }

    public void Kill(){
        //notify server
        String tempName = "Player " + this.name;
        System.out.println(tempName + " Is killing ");
        setState("Kill");
        setChanged();
        notifyObservers(this);
    }
    public void Sabotage(String sabo){
        //change peoples view distance
        String tempName = "Player " + this.name;
        setState("Sabotage");
        switch(sabo) {
            case "Lights":
                System.out.println(tempName + " Is sabotaging the lights");
                setChanged();
                notifyObservers(this);
                break;
            case "Communications":
                System.out.println(tempName + " Is sabotaging the communications");
                setChanged();
                notifyObservers(this);
                break;
            case "Oxygen":
                System.out.println(tempName + " Is sabotaging the oxygen");
                setChanged();
                notifyObservers(this);
                break;
            default:
                setState("");
                System.out.println(tempName + " invalid Sabatoge");
                setChanged();
                notifyObservers(this);
                break;
        }
    }
    public String getValidActions(){

        return super.getValidActions() + "\nMurderer Only: Kill, Sabotage [Lights, Communications, Oxygen]";
    }
}
