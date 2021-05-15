public class PlayerFactory extends AbstractPlayerFactory {
    @Override
    public Murderer createMurderer(String name, String color,int PlayerNum){

        //Creation of Killer
        Murderer player = Murderer.getInstance();
        player.role = "Murderer";
        player.playerNum = PlayerNum;
        player.name = name;
        player.color = color;
        player.setViewDistance(15);
        return player;
    }
    @Override
    public Survivor createSurvivor(String name, String color,int PlayerNum){

        //Creation of normal Player
        Survivor player = new Survivor();
        player.role = "Survivor";
        player.playerNum = PlayerNum;
        player.name = name;
        player.color = color;
        player.setViewDistance(7);
        return player;
    }
}
