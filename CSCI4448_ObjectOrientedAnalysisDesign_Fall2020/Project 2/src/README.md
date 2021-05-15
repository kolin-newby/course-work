#Project 2:
###Team: Chandler Garthwaite, Tanner Slemmer, Kolin Knewby

###Build Tree:

        
###Pattern Code Examples:
- Observer Pattern
    The observer pattern is used multiple times
    First: The ZooClock is being Observed by ZooFoodServer, ZooKeeper, and ZooAnnouncer
           These recieved a notifcation whenever the time is changed, then they check if it is their time to perform the task, then perform the tasks.
    Second: ZooKeeper and ZooFoodServer are being observed by ZooAnnouncer
            Both of these have a status object that is updated when they begin a new task. The announcer then checks the status and can inform the zoo if it's an important task.
- Strategy Pattern
    The Strategy Pattern is accomplished by creating an exercise behavior object to help the Animals determine what they roam type is outside of overwriting methods
    This is done by setting their ExcerciseBehavior after being created
    (ExerciseBehavior.java is where )


###Assumptions:
- That it is okay to write to the same file mutliple files

###Citations:
- Any use of the Observables and Observers is based on the lecture 12 slides


###How to Run:
- No special wayst to run, but Zoo containts the main class and should be used to run the program.
To compile from terminal run 'javac \*.java" then java Zoo


