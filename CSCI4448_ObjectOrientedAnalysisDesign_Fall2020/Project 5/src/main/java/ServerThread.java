//https://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html - source
import java.net.*;
import java.io.*;


//This is where the cases are handled
public class ServerThread extends Thread {
    private Socket socket = null;
    Map mapCopy;
    Player playerTemp;
    Lobby lobby;

    private int currentTurn = 0;
    public ServerThread(Socket socket, Map map, Player player, Lobby lobby){
        super("Server Thread");
        this.socket = socket;
        this.mapCopy = map;
        this.playerTemp = player;
        this.lobby = lobby;
    }

    public void run() {

        try (
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(
                                socket.getInputStream()));
        ) {
            String inputLine, outputLine;
            ServerProtocol kkp = new ServerProtocol(this.lobby);
            outputLine = kkp.processInput(null, mapCopy, playerTemp);
            out.println(outputLine);

            //While loop that keeps the server alive
            while ((inputLine = in.readLine()) != null) {
                //System.out.println(inputLine);
                outputLine = kkp.processInput(inputLine, mapCopy, playerTemp);
                System.out.println("************************************************");
                System.out.println(outputLine);
                out.println(outputLine);
                if (outputLine.equals("Bye."))
                    break;
            }
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}