import org.junit.jupiter.api.Test;

import java.nio.channels.ScatteringByteChannel;
import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

public class tester {
    AbstractFactory rollFactory = RollProducer.getFactory();

    Roll rollSpring = rollFactory.getRoll("Spring");
    Roll rollSausage = rollFactory.getRoll("Sausage");
    Roll rollPastry = rollFactory.getRoll("Pastry");
    Roll rollEgg = rollFactory.getRoll("Egg");
    Roll rollJelly = rollFactory.getRoll("Jelly");

    CasualCustomer custCasual = new CasualCustomer();
    BusinessCustomer custBusiness = new BusinessCustomer();
    CateringCustomer custCatering = new CateringCustomer();


    @Test
    void factoryCheck(){
        //Testing to make sure the factory implementation correctly works
        AbstractFactory rollFactory = RollProducer.getFactory();

        Roll roll1 = rollFactory.getRoll("Spring");
        Roll roll2 = new SpringRoll();

        assertEquals(roll1.getType(),roll2.getType());
    }

    @Test
    void basicDecoratorCheck(){
        //Double checking to make sure that factories are producing the correct objects
        AbstractFactory rollFactory = RollProducer.getFactory();

        Roll roll1 = rollFactory.getRoll("Sausage");
        Roll roll2 = new SausageRoll();

        assert(roll1.getType() == roll2.getType() && roll1.getDescription() == roll2.getDescription());
    }

    @Test
    void advancedDecoratorCheck(){
        //Testing to make sure decorators correctly add price dynamnically based off types
        AbstractFactory rollFactory = RollProducer.getFactory();

        Roll roll1 = rollFactory.getRoll("Sausage");
        roll1 = new ExtraToppings(roll1);
        roll1 = new ExtraSauce(roll1);
        roll1 = new ExtraFilling(roll1);

        assertEquals(roll1.cost(),5.53);
    }

    @Test
    void casualFullStock(){
        //Checking on how the casual customer functions

        ArrayList<Stock> inventory = new ArrayList<>();

        inventory.add(new Stock(rollSpring,20));
        inventory.add(new Stock(rollSausage,20));
        inventory.add(new Stock(rollPastry,20));
        inventory.add(new Stock(rollEgg,20));
        inventory.add(new Stock(rollJelly,20));

        Order order = new Order(custCasual);
        order = custCasual.placeOrder(inventory);

        assert(order.rollsOrderedSize() > 0);
    }

    @Test
    void casualEmptyStock(){
        //Checking on how the casual customer functions

        ArrayList<Stock> inventory = new ArrayList<>();

        inventory.add(new Stock(rollSpring,0));
        inventory.add(new Stock(rollSausage,0));
        inventory.add(new Stock(rollPastry,0));
        inventory.add(new Stock(rollEgg,0));
        inventory.add(new Stock(rollJelly,0));

        Order order = new Order(custCasual);

        order = custCasual.placeOrder(inventory);

        assert(order.orderWasImpacted()== true);
    }

    @Test
    void businessMoreThan2(){
        //Checking on how the casual customer functions

        ArrayList<Stock> inventory = new ArrayList<>();

        inventory.add(new Stock(rollSpring,20));
        inventory.add(new Stock(rollSausage,20));
        inventory.add(new Stock(rollPastry,20));
        inventory.add(new Stock(rollEgg,20));
        inventory.add(new Stock(rollJelly,20));

        Order order = new Order(custBusiness);
        order = custBusiness.placeOrder(inventory);

        assert(order.rollsOrderedSize() > 0);

    }

    @Test
    void businessLessThan2(){
        //Negative case
        ArrayList<Stock> inventory2 = new ArrayList<>();

        inventory2.add(new Stock(rollSpring,1));
        inventory2.add(new Stock(rollSausage,2));
        inventory2.add(new Stock(rollPastry,2));
        inventory2.add(new Stock(rollEgg,2));
        inventory2.add(new Stock(rollJelly,2));

        Order order2 = new Order(custBusiness);
        order2 = custBusiness.placeOrder(inventory2);

        assert(order2.orderWasImpacted() == true);
    }

    @Test
    void cateringMoreThan15(){
        //Checking on how the casual customer functions

        ArrayList<Stock> inventory = new ArrayList<>();

        inventory.add(new Stock(rollSpring,20));
        inventory.add(new Stock(rollSausage,20));
        inventory.add(new Stock(rollPastry,20));
        inventory.add(new Stock(rollEgg,20));
        inventory.add(new Stock(rollJelly,20));

        Order order = new Order(custCatering);
        order = custCatering.placeOrder(inventory);

        assert(order.rollsOrderedSize() > 0);

    }

    @Test
    void cateringLessThan15(){
        //Checking to make sure they grab all 15 or up to 15 no matter the roll
        ArrayList<Stock> inventory2 = new ArrayList<>();

        inventory2.add(new Stock(rollSpring,7));
        inventory2.add(new Stock(rollSausage,1));
        inventory2.add(new Stock(rollPastry,2));
        inventory2.add(new Stock(rollEgg,1));
        inventory2.add(new Stock(rollJelly,1));

        Order order2 = new Order(custCatering);
        order2 = custCatering.placeOrder(inventory2);

        assertEquals(order2.rollsOrderedSize(), 12);
    }

    @Test
    void calendarObserver(){
        Calendar testCalendar = new Calendar();
        assert(testCalendar.getDay() == 1);
        Store testStore = new Store(testCalendar,30);
        testCalendar.addObserver(testStore);

        testCalendar.runThroughMonth();

        assert(testStore.getStatus() != "");
    }

}
