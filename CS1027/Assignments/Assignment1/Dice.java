//Dice class: holds a dice value and allows you to roll the dice to change the value.
public class Dice{
    //value instance variable holds the number of the dice.
    private int value;
    
    //constructor with no parameters, sets the value to -1.
    public Dice(){
        this.value = -1;
    }

    //overload constructor with value as a parameter, sets the value insatnce variable to parameter.
    public Dice(int value){
        this.value = value;
    }

    //roll function, sets the value to a random number.
    public void roll(){
        this.value = RandomNumber.getRandomNumber(1, 6);
    }

    //getter for value instance variable, returns value
    public int getValue(){
        return this.value;
    }

}