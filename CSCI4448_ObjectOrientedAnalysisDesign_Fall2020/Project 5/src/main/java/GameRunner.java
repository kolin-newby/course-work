import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;

public class GameRunner implements Observer {

    //Observer
    //What StoreObserver is observing
    private Player player = null;
    private Murderer m = null;
    private Survivor s = null;
    private int clientId = -1;
    AbstractPlayerFactory producePlayer;
    //Observer Constructor
    public GameRunner(Player newPlayer){
        //this.player = player;
        this.producePlayer = PlayerFactoryProducer.getFactory();
        //https://www.educative.io/edpresso/how-to-generate-random-numbers-in-java
        Random rand = new Random();
        this.clientId = rand.nextInt(99999);

        this.player = newPlayer;

    }

    //Read command line and server interactions
    private PrintWriter SendToServer;
    private BufferedReader ReceiveFromServer;
    private BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

    public void setSendToServer(PrintWriter sendToServer){
        this.SendToServer = sendToServer;
    }
    public void setReceiveFromServer(BufferedReader receiveFromServer){
        this.ReceiveFromServer = receiveFromServer;
    }

    private void createNewPlayer(String inputString){
        String[] input = inputString.split(",");
        if(input[3].equals("true")){
            this.m = producePlayer.createMurderer( input[1],input[2],Integer.parseInt(input[1]));
            this.player = m;
            m.addObserver(this);
        }else{
            this.s = producePlayer.createSurvivor( input[1],input[2],Integer.parseInt(input[1]));
            this.player = s;
            s.addObserver(this);
        }
        //this.player = producePlayer.createPlayer( input[1],false,input[2],Integer.parseInt(input[1]));
        this.player.addObserver(this);
    }
    public void RunGame() throws IOException {
        boolean gameRunning = true;
        String toUser;
        String fromUser;

        //Weird stuff I had to do to get the newPlayer function to work
        System.out.println(ReceiveFromServer.readLine());
        SendToServer.println("NewClient");
        String newPlayerString = ReceiveFromServer.readLine();
        createNewPlayer(newPlayerString);
        this.player.idle();


        while(gameRunning){
            if((toUser = ReceiveFromServer.readLine()) != null){

                System.out.println(toUser);
                //Output map and what player action was
                //https://www.techiedelight.com/read-multi-line-input-console-java/#:~:text=3.-,BufferedReader%20Class,can%20also%20use%20StringTokenizer%20class.
                String line;
                int i = 0;
                try { //Run through size of map
                    while ((line = ReceiveFromServer.readLine()) != null && i < 25) {
                        System.out.println(line);
                        i = i + 1;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                line = ReceiveFromServer.readLine();
                System.out.println(line);
                if(player.role.equals(("Survivor"))) {
                    System.out.println(s.getValidActions());
                }else{
                    System.out.println(m.getValidActions());
                }
                fromUser = stdIn.readLine();


                    //Getting Player Options
                //System.out.println("Server: " + fromUser);
                switch (fromUser){
                    case "Leave":
                        gameRunning = false;
                        break;
                    case "Report":
                        player.report();
                        break;
                    case "Activate":
                        if(player.role.equals(("Survivor"))){
                            s.Activate();
                        }else{
                            System.out.println("You are not a Survivor. Please trying killing.");
                        }
                    case "Idle":
                        player.idle();
                        break;
                    case "w":
                        player.move("Up");
                        break;
                    case "a":
                        player.move("Left");
                        break;
                    case "s":
                        player.move("Down");
                        break;
                    case "d":
                        player.move("Right");
                        break;
                    case "Kill":
                        if(player.role.equals("Murderer")){ //changed to .equals() instead of ==
                            //BUG
                            m.Kill();
                        }else{
                            System.out.println("You are not a Murderer. Choose a different action.");
                        }
                    default:
                        String[] parseString = fromUser.split(" ");
                        if(parseString.length > 1 && player.role.equals("Murderer")){
                            m.Sabotage(parseString[1]);
                        }
                        player.invalidAction();
                }
            }
        }
    }
    @Override
    public void update(Observable obj, Object arg) {
        if(obj == player){
            String state = player.getState();
            switch (state){
                case "Kill":
                    //Send Kill
                    SendToServer.println(player.playerNum+",Kill");
                    break;
                case "Sabotage":
                    SendToServer.println(player.playerNum+",Sabotage");
                case "Report":
                    //Send Report
                    SendToServer.println(player.playerNum+",Report");
                    break;
                case "Activate":
                    //Send Activation
                    SendToServer.println(player.playerNum+",Activate");
                    break;
                //Movements
                case "Up":
                    //Move up
                    SendToServer.println(player.playerNum+",Move,up");
                    break;
                case "Down":
                    //Move Down
                    SendToServer.println(player.playerNum+",Move,down");
                    break;
                case "Left":
                    //Move Left
                    SendToServer.println(player.playerNum+",Move,left");
                    break;
                case "Right":
                    //Move Right
                    SendToServer.println(player.playerNum+",Move,right");
                    break;
                case "Idle":
                    SendToServer.println(player.playerNum+",Idle");
                    break;
                default:
                    System.out.println("Incorrect State");
                    SendToServer.println(player.playerNum+",Invalid State");
            }
        }
    }
}

