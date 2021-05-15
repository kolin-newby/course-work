import java.util.ArrayList;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.Random;

public class Lobby {
    private int playerCount;

    private ArrayList<Player> playerList = new ArrayList<>();
    private ArrayList<String> colors = new ArrayList<>();
    private Map map;
    AbstractPlayerFactory producePlayer;
    //private Dictionary<String, Boolean > playerList = new Hashtable<>(); //holds player vision restrictions

    public Lobby(){
        playerCount = 0;
        colors.add("black");
        colors.add("red");
        colors.add("green");
        colors.add("yellow");
        colors.add("blue");
        colors.add("purple");
        colors.add("cyan");
        colors.add("white");
        this.producePlayer = PlayerFactoryProducer.getFactory();
        this.map = new Map();
    }

    public void startGame(){

    }

    public int getPlayerCount(){
        return playerCount;
    }

    public Player getPlayer(int i){
        return playerList.get(i-1);
    }

    public void movePlayer(int player, String direction){
        map.playerMove(getPlayer(player), direction);
    }

    public void displayLobbyMap(int i){
        //map.displayMap(playerList.get(0));
        System.out.println(map.returnMap(playerList.get(i-1)));
    }


    public String returnLobbyMap(int player){
        return map.returnMap(playerList.get(player-1));
    }

    public String addPlayer(){
        String returnString = "";
        Random rand = new Random();
        String color = colors.remove(rand.nextInt(colors.size()));
        Player temp;
        String murderBool = "false";
        if(playerList.size() == 0){
            murderBool = "true";
            temp = producePlayer.createMurderer("" + (playerList.size() + 1),  color, (playerList.size() + 1));
        }else{
            temp = producePlayer.createSurvivor("" + (playerList.size() + 1), color, (playerList.size() + 1));
        }
        playerList.add(temp);

        int[] pos = {10,0+playerList.size()};
        map.addPlayer(temp,pos);
        returnString = "New," + playerList.size() + "," + color + "," + murderBool;
        System.out.println(returnString);
        return returnString;
    }

}
