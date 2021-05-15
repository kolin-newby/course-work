public class RollFactory extends AbstractFactory{
    @Override
    public Roll getRoll(String rollType){
        switch(rollType){
            case("Spring"):
                return new SpringRoll();
            case("Jelly"):
                return new JellyRoll();
            case("Sausage"):
                return new SausageRoll();
            case("Pastry"):
                return new PastryRoll();
            case("Egg"):
                return new EggRoll();
            case("Out"):
                return new OutRoll();
            default:
                return new OutRoll();
        }
    }
}
