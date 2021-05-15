public abstract class AbstractPlayerFactory {
    abstract Murderer createMurderer(String name, String color, int PlayerNum);
    abstract Survivor createSurvivor(String name, String color, int PlayerNum);
}
