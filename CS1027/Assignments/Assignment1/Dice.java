public class Dice{
    private int value;
    
    public Dice(){
        this.value = -1;
    }

    public Dice(int value){
        this.value = value;
    }

    public void roll(){
        this.value = RandomNumber.getRandomNumber(1, 6);
    }

    public int getValue(){
        return this.value;
    }

}