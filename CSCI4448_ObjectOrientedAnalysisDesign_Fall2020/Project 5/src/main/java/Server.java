//https://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html - source
import java.net.*;
import java.io.*;

public class Server {
    public static void main(String[] args) throws IOException {

        int portNumber = 4444;

        Map test = new Map();
        Lobby lobby = new Lobby();
        Player p1 = new Player();
        p1.name = "Green";
        p1.role = "Survivor";
        p1.color = "cyan";
        p1.viewDistance = 1;

        int[] start_pos = {1,1};
        test.addPlayer(p1, start_pos);

        test.playerMove(p1, "down");

        test.displayMap(p1);
        boolean listening = true;

        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            String outputLine;

            while (listening) {
                new ServerThread(serverSocket.accept(), test, p1,lobby).start();
            }
        } catch (IOException e) {
            System.err.println("Could not listen on port " + portNumber);
            System.exit(-1);
        }
        /*
        try ( //Try block - all the instantiation
                ServerSocket serverSocket = new ServerSocket(portNumber);
                Socket clientSocket = serverSocket.accept();

                BufferedReader in = new BufferedReader(
                        new InputStreamReader(clientSocket.getInputStream()));
        ) {

            String inputLine, outputLine;

            // Initiate conversation with client
            //KnockKnockProtocol kkp = new KnockKnockProtocol(); //Will need to be updated with ServerProtocol - current KKP to show functionality


            //While loop that keeps the server alive
            while ((inputLine = in.readLine()) != null) {
                outputLine = kkp.processInput(inputLine, test, p1);
                out.println(outputLine);
                if (outputLine.equals("Bye."))
                    break;
            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port "
                    + portNumber + " or listening for a connection");
            System.out.println(e.getMessage());
        }
         */
    }
}
