public class RollProducer {
    public static AbstractFactory getFactory(){
        //Creates a new RollFactory capable of creating any type of roll.
        return new RollFactory();
    }
}
