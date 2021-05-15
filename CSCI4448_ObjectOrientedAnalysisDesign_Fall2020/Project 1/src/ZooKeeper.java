public class ZooKeeper extends ZooEmployee{

    //Class Constructor
    //Updates the employeeName in zooEmployee
	public ZooKeeper(String name){
		employeeName = "Zookeeper " + name;
	}

    //Method: wakeAnimal
    //Takes an animal object, get its name then returns a string formatted with zooKeeper name, "wakes up", and animalName
    public String wakeAnimal(Animal a){



    	return this.employeeName + " wakes up " + a.name + ".";
    }

    //Method: rollCall
    //Takes an animal object, get its name then returns a string formatted with zooKeeper name, "roll calls", and animalName
    public String rollCall(Animal a){



        return this.employeeName + " roll calls " + a.name + ".";
    }

    //Method: feedAnimal
    //Takes an animal object, get its name then returns a string formatted with zooKeeper name, "feeds", and animalName
    public String feedAnimal(Animal a){



        return this.employeeName + " feeds " + a.name + ".";
    }

    //Method: exerciseAnimal
    //Takes an animal object, get its name then returns a string formatted with zooKeeper name, "excersies, and animalName
    public String exerciseAnimal(Animal a){



        return this.employeeName + " exercises " + a.name + ".";
    }

    //Method: sleepAnimal
    //Takes an animal object, get its name then returns a string formatted with zooKeeper name, "puts", animalName, " to bed".
    public String sleepAnimal(Animal a){
        return this.employeeName + " puts " + a.name + " to bed.";
    }


}