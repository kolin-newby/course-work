//https://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html - source
import java.net.*;
import java.io.*;


//This is where the cases are handled
public class ServerProtocol {
    private static final int WAITING = 0;
    private static final int INIT = 1;
    private static final int SENTPLAYERUPDATE = 2;
    private static final int SENTINITMAP = 3;

    private Lobby lobby;
    private int state = INIT;
    private int currentTurn = 0;

    public ServerProtocol(Lobby lobby){
        this.lobby = lobby;
    }

    private String handleString(String inputString, Map curMap, Player curPlayer) {
        String outputString = "";

        //Handle client actions here
        String[] input = inputString.split(",");
        if(inputString.equals("NewClient")){
            System.out.println("Recieved new client");
            return lobby.addPlayer();
        }

        int player = Integer.parseInt(input[0]);
        String action = input[1];
        switch (action) {

            case "Report":
                outputString = "Player: "+ player + " is Reporting a body";
                break;
            case "Idle":
                outputString = "Waiting for a valid action";
                break;
            case "Move":
                if(input.length < 2 ){
                    outputString = "Incorrect movement";
                    break;
                }
                outputString = "Player: "+ player + " moved.";
                lobby.movePlayer(player,input[2]);
                break;
            case "Sabotage":
                outputString = "Something has been Sabotaged!";
                break;
            case "Kill":
                outputString = "Someone has been killed!";
                break;
            case "Activate":
                outputString = "Player: "+ player + " is activating their task";
                break;
            default:
                outputString = "Invalid action sent to server: " + inputString;
                break;
        }

        System.out.println(outputString);
        System.out.println("To player " + player + " :");
        outputString = lobby.returnLobbyMap(player) + "\n" + outputString;
        System.out.println(outputString);
        return outputString;
    }

    public String processInput(String inputString, Map curMap, Player curPlayer) {
        String outputString = null;

        switch(state){

            case INIT:
                outputString = "Created map now waiting client response";
                state = WAITING;
                break;
            case WAITING:
                //outputString = "Waiting for user updates"; outputString + "\n" +
                outputString = handleString(inputString, curMap, curPlayer);
                state = WAITING;
                break;

            default:
                outputString = "Invalid State or String";
                state = WAITING;
                break;

        }
        return outputString;
    }


}