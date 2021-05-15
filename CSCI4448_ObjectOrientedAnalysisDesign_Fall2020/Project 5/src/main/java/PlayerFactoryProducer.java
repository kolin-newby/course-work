public class PlayerFactoryProducer {
    public static AbstractPlayerFactory getFactory(){
        //Creates a player factory that allows easy instantiation.
        return new PlayerFactory();
    }
}
