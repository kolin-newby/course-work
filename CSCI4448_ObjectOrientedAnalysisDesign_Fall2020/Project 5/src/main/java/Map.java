import java.io.*;
import java.util.*;

public class Map {
    // Map stored from txt to this variable
    private ArrayList<ArrayList<String>> map = new ArrayList<>(); //Stores entire map
    
    private int[] size = {0, 0}; //the size of the map
    private ArrayList<Player> players = new ArrayList<>();
    private Dictionary< String, int[] > player_pos = new Hashtable <>(); //holds player positions on the map
    private Dictionary<String, Integer > vision = new Hashtable<>(); //holds player vision restrictions

    private static final Dictionary<String, String> colors = new Hashtable<>(); //holds ASCI color values
    
    public Map() { //https://stackoverflow.com/questions/5762491/how-to-print-color-in-console-using-system-out-println
        colors.put("reset", "\u001B[0m");
        colors.put("black", "\u001B[30m");
        colors.put("red",   "\u001B[31m");
        colors.put("green", "\u001B[32m");
        colors.put("yellow","\u001B[33m");
        colors.put("blue",  "\u001B[34m");
        colors.put("purple","\u001B[35m");
        colors.put("cyan",  "\u001B[36m");
        colors.put("white", "\u001B[37m");

        //https://www.w3schools.com/java/java_files_read.asp source for setting up file read with error handling
//        String pathName = "src/main/java/mapDefault.txt";
        String pathName = "mapDefault.txt";
        try
        {
            File map_def = new File(pathName);
            Scanner map_reader = new Scanner(map_def);
            
            while (map_reader.hasNextLine()) {
                String data = map_reader.nextLine();

                // populate the map array with the default map file
                ArrayList<String> tmp = new ArrayList<>();
                for (int j = 0; j < data.length(); j++) {
                    String point = String.valueOf(data.charAt(j));
                    tmp.add(point);
                }
                map.add(tmp);
            }
            // Update map_size after map is populated
            // map_size[0] is number of rows (y)
            // map_size[1] is number of columns (x)
            size[0] = map.size();
            size[1] = map.get(0).size();

//           Map array depiction
//            [
//            [------------------------],
//            [-                      -],
//            [-                      -],
//            [-                      -],
//            [-                      -],
//            [-                      -],
//            [------------------------]
//            ]
//            Origin is upper left
        }
        catch (FileNotFoundException e)
        {
            System.out.println("Map file not found");
            System.exit(1);
        }
    }
    
    public void displayMap(Player player) { //currently just prints map without player locations

        int[] pos = (player_pos.get(player.name));
        int vis = player.viewDistance;

        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                boolean printed = false;
                double dist = Math.sqrt(Math.pow((j - pos[1]), 2) + Math.pow((i - pos[0]), 2)); //Distance formula: d=(sqrt(j2-j1)^2 + (i2-i1)^2) | player pos=(j1,i1) and print pos=(j2,i2)
                if ((!map.get(i).get(j).equals("-")) && (dist > vis))
                {
                    System.out.print(" ");
                    continue;
                }
                for (int k = 0; k < players.size(); k++)
                {
                    char icon = players.get(k).name.charAt(0);
                    if (i == player_pos.get(players.get(k).name)[0] && j == player_pos.get(players.get(k).name)[1])
                    {
                        System.out.print(colors.get(players.get(k).color) + icon + colors.get("reset")); //Change color to green, print, reset color.
                        printed = true;
                        break;
                    }
                }
                if (printed)
                {
                    continue;
                }

                System.out.print(map.get(i).get(j));
            }
            System.out.print("\n");
        }
    }
    public String returnMap(Player player){
        int[] pos = (player_pos.get(player.name));
        int vis = player.viewDistance;
        String returnString = "";
        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                boolean printed = false;
                double dist = Math.sqrt(Math.pow((j - pos[1]), 2) + Math.pow((i - pos[0]), 2)); //Distance formula: d=(sqrt(j2-j1)^2 + (i2-i1)^2) | player pos=(j1,i1) and print pos=(j2,i2)
                if ((!map.get(i).get(j).equals("-")) && (dist > vis))
                {
                    returnString = returnString + " ";
                    continue;
                }
                for (int k = 0; k < players.size(); k++)
                {
                    char icon = players.get(k).name.charAt(0);
                    if (i == player_pos.get(players.get(k).name)[0] && j == player_pos.get(players.get(k).name)[1])
                    {
                        returnString = returnString + colors.get(players.get(k).color) + icon + colors.get("reset");
                        //System.out.print(colors.get(player.color) + icon + colors.get("reset")); //Change color to green, print, reset color.
                        printed = true;
                        break;
                    }
                }
                if (printed)
                {
                    continue;
                }
                returnString = returnString + map.get(i).get(j);
            }
            returnString = returnString + "\n";
        }
        return returnString;
    }
    public void addPlayer(Player player, int[] start_pos) {
        vision.put(player.name, player.getViewDistance());
        player_pos.put(player.name, start_pos);
        players.add(player);
    }

    public boolean playerMove(Player player, String dir) { //returns true if player was able to make given move, false otherwise
        int[] pos = (player_pos.get(player.name));
        switch (dir) {
            case "up":
                if (!(map.get(pos[0] - 1).get(pos[1])).equals(" ")) {
                    return false;
                }
                pos[0] = pos[0] - 1;
                player_pos.put(player.name, pos);
                return true;
            case "down":
                if (!(map.get(pos[0] + 1).get(pos[1])).equals(" ")) {
                    return false;
                }
                pos[0]++;
                player_pos.put(player.name, pos);
                return true;
            case "left":
                if (!(map.get(pos[0]).get(pos[1] - 1)).equals(" ")) {
                    return false;
                }
                pos[1] = pos[1] - 1;
                player_pos.put(player.name, pos);
                return true;
            case "right":
                if (!(map.get(pos[0]).get(pos[1] + 1)).equals(" ")) {
                    return false;
                }
                pos[1]++;
                player_pos.put(player.name, pos);
                return true;
            default:
                System.out.println("Invalid selection!");
                return false;
        }
    }

    public static void main(String[] args) {

        Map test = new Map();

        Player p1 = new Player();
        p1.name = "Green";
        p1.role = "Survivor";
        p1.color = "green";
        p1.viewDistance = 10;

        Player p2 = new Player();
        p2.name = "Blue";
        p2.role = "Survivor";
        p2.color = "blue";
        p2.viewDistance = 10;

        Player p3 = new Player();
        p3.name = "Red";
        p3.role = "Survivor";
        p3.color = "red";
        p3.viewDistance = 10;

        Player p4 = new Player();
        p4.name = "Purple";
        p4.role = "Survivor";
        p4.color = "purple";
        p4.viewDistance = 10;

        Player p5 = new Player();
        p5.name = "Yellow";
        p5.role = "Murderer";
        p5.color = "yellow";
        p5.viewDistance = 15;


        int[] start_pos1 = {1,1};
        int[] start_pos2 = {2,2};
        int[] start_pos3 = {3,3};
        int[] start_pos4 = {4,4};
        int[] start_pos5 = {5,5};
        test.addPlayer(p1, start_pos1);
        test.addPlayer(p2, start_pos2);
        test.addPlayer(p3, start_pos3);
        test.addPlayer(p4, start_pos4);
        test.addPlayer(p5, start_pos5);


        Scanner in = new Scanner(System.in);
        while(true)
        {
            System.out.println("Use 'w', 'a', 's', and 'd' keys to move player.");
            test.displayMap(p1);
            String tmp = in.nextLine();
            switch(tmp)
            {
                case "q":
                    return;
                case "w":
                    System.out.println(test.playerMove(p1, "up"));
                    test.displayMap(p1);
                    continue;
                case "s":
                    System.out.println(test.playerMove(p1, "down"));
                    test.displayMap(p1);
                    continue;
                case "a":
                    System.out.println(test.playerMove(p1, "left"));
                    test.displayMap(p1);
                    continue;
                case "d":
                    System.out.println(test.playerMove(p1, "right"));
                    test.displayMap(p1);
                    continue;
                default:
                    System.out.println("Invalid key press!");
            }
        }
    }
}