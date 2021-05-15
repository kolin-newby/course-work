//https://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html - source
import java.io.*;
import java.net.*;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Random;
public class ServerClient {
    public static void main(String[] args) throws IOException {

        //https://crunchify.com/how-to-get-server-ip-address-and-hostname-in-java/ - source to get local host setup
        InetAddress ip;
        ip = InetAddress.getLocalHost();
        String hostName = ip.getHostName();
        int portNumber = 4444;

        //Random number for custom ID


        AbstractPlayerFactory producePlayer = PlayerFactoryProducer.getFactory();
        Player one = producePlayer.createSurvivor( "I Am Not The Imposter","Green",1);
        GameRunner game = new GameRunner(one);
        one.addObserver(game);

        //Instantiation block

        System.out.println("Current Options: 'Proof of Concept' 'Display Map'(Server side)");
        try (
                Socket kkSocket = new Socket(hostName, portNumber);
                PrintWriter out = new PrintWriter(kkSocket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(kkSocket.getInputStream()));
        ) {
            game.setReceiveFromServer(in);
            game.setSendToServer(out);
            game.RunGame();

        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " +
                    hostName);
            System.exit(1);
        }
    }

}