import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class Shop {
    public static void main(String args[]) throws IOException{
        Roll roll = new SausageRoll();
        roll = new ExtraFilling(roll);
        roll = new ExtraSauce(roll);
        roll = new ExtraToppings(roll);

        System.out.println(roll.getType());
        System.out.println(roll.getDescription());
        System.out.println(roll.cost());

        //Example of factory
        AbstractFactory rollFactory = RollProducer.getFactory();

        //Really just instaniating factory and using it to get roll types.
        Roll roll2 = rollFactory.getRoll("Sausage");
        roll2 = new ExtraFilling(roll2);
        roll2 = new ExtraSauce(roll2);
        roll2 = new ExtraToppings(roll2);

        System.out.println(roll2.getType());
        System.out.println(roll2.getDescription());
        System.out.println(roll2.cost());
        //Other file
        Path s = Path.of("stats.out");
        Files.writeString(s, "");

        //Store, Invetory, and Calendar Creation
        Path fileName = Path.of("output.out");
        Files.writeString(fileName, "");
        Calendar calendar = new Calendar();
        Store robbiesRolls = new Store(calendar, 30);
        StoreObserver obs = new StoreObserver(robbiesRolls, calendar, fileName);

        String outputText = "\n**************\n30 Max Inventory EXAMPLE\n**************\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);
        //Setting Observers
        calendar.addObserver(robbiesRolls);
        calendar.addObserver(obs);
        robbiesRolls.addObserver(obs);
        calendar.runThroughMonth();

        calendar = new Calendar();
        robbiesRolls = new Store(calendar, 45);
        obs = new StoreObserver(robbiesRolls, calendar, fileName);

        outputText = "\n**************\n45 Max Inventory EXAMPLE\n**************\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);

        //Setting Observers
        calendar.addObserver(robbiesRolls);
        calendar.addObserver(obs);
        robbiesRolls.addObserver(obs);
        calendar.runThroughMonth();

        outputText = "\n**************\n60 Max Inventory EXAMPLE\n**************\n";
        Files.writeString(fileName, outputText, StandardOpenOption.APPEND);

        calendar = new Calendar();
        robbiesRolls = new Store(calendar, 60);
        obs = new StoreObserver(robbiesRolls, calendar, fileName);

        //Setting Observers
        calendar.addObserver(robbiesRolls);
        calendar.addObserver(obs);
        robbiesRolls.addObserver(obs);
        calendar.runThroughMonth();

        
//        Stats stats30 = new Stats();
//        for (int i = 0; i < 5; i++) {
//            stats30.data.addValue(i+5,"Sales", "1");
//        }
//        stats30.LineGraph();
//=======
//        // Graph graph = new Graph();
//
//        // sample datapoint format for LineGraph
//        // data.addValue( value(int) , Sales in day , Day );
//
//        // graph.lineGraph(dataset, title, x-axis, y-axis);
//
//        // sample datapoint format for BarGraph
//        // data.addValue( value(int) , 30 or 45 or 60 inventory(String) , Catergory(String) );
//        // ex: data.addValue( 27 , "30 inventory" , "Rolls Sold" );
//
//        // graph.barGraph(dataset, title, x-axis, y-axis);
//>>>>>>> Stashed changes

        //System.out.println("Simplify Testing");
        //System.out.println(robbiesRolls.orderLog.get(0).printSimplify());
        
    }
}
