#Project 1: Life of a Zookeeper
###Team: Chandler Garthwaite, Tanner Slemmer, Kolin Knewby

###Build Tree:

- Classes
    - Zoo (Zoo.java)
    - Animal (Animal.java)
        - Pachyderm (Pachyderm.java)
            - Rhino (Rhino.java)
            - Elephant (Elephant.java)
            - Hippo (Hippo.java)
        - Feline (Feline.java)
            - Cat (Cat.java)
            - Lion (Lion.java)
            - Tiger (Tiger.java)
        - Canine
            - Dog (Dog.java)
            - Wolf (Wolf.java)
        - Crustacean
            - Crab (Crab.java)
            - Lobster (Lobster.java)
    - Zookeeper (ZooEmployee.java)

            
- Functions 
    - sleep()
        - Defined in Animal.java
        - Overwritten in Feline.java (30% makeNoise, 30% roam, 40% sleep)
    - wakeUp()
        - Defined in Animal.java
    - roam()
        - Defined in Animal.java
        - Overwritten in Dog.java (25% digging, 75% roam)
        - Overwritten in Pachyderm.java (25% charging, 75% roam)
    - eat()
        - Defined in Animal.java
    - makeNoise()
        - Defined in Animal.java

    - wakeAnimal()
        - Defined in ZooKeeper.java
    - rollCall()
        - Defined in ZooKeeper.java
    - feedAnimal()
        - Defined in ZooKeeper.java
    - exerciseAnimal()
        - Defined in ZooKeeper.java
    - sleepAnimal()
        - Defined in ZooKeeper.java
    - arrive()
        - Defined in ZooKeeper.java
    - leave()
        - Defined in ZooKeeper.java

    - runThroughWeek()
        - Defined in Zoo.java
        
###OOAD Code Examples:
- Abstraction
    - when a class can call methods without knowing how the methods are implemented
    Zoo.Java - line 22
- Encapsulation
    - Animal.java
        - While we don't use encapsulation to protect our information we can access the name variable name in any class.
        - Animal.java line 4
- Polymorphism
    - Animal.java
        - All of our functions are in this file. Which allows all extensions to access it. For example cat can call the function roam.
        - Animal.Java Line 11 is an example of methods that are polmorphic
        - Feline.Java line 12 futher emphasises it being polymorphic by being overwritten
- Abstract Class
    - ZooEmployee.java
- Identity
    - Different animal objects have different names to seperate and make themsleves unique from each other.
    - Animal.Java line 4

###Assumptions:


###How to Run:
No special wayst o run, but Zoo containts the main class and should be used to run the program.

