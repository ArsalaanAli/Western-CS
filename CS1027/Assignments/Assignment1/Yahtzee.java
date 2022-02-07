//Arsalaan Ali
//CS1027 ASSIGNMENT #1

//importing java util functions
import java.util.*;

//yahtzee class holds array of dice and functions for the dice.
public class Yahtzee{
    
    //instance variable, array of dice.
    private Dice[] dice;

    //constructor for Yahtzee class with no parameters, sets array of dice to 5 dice with random numbers
    public Yahtzee() {
        this.dice = new Dice[5];
        for (int i = 0; i<dice.length; i++) {
            dice[i] = new Dice();
            dice[i].roll();
        }
    }
    //overload constructor for Yahtzee class with array of dice as parameter, sets instance variable to this parameter.
    public Yahtzee(Dice[] dice) {
        this.dice = dice;
    }

    //public function that counts how many dice show each of the possible values from 1-6 and returns all of them in an int array.
    public int[] getValueCount(){
        int[] countValue = new int[6];
        for(int i = 0; i < dice.length; i++){
            countValue[dice[i].getValue()-1]++;
        }
        return countValue;
    }

    //private function for calculating score options, sets the values of array from index 6-12 to 0
    private void initializeArray(int[] results){
        for(int i = 6; i<13; i++){
            results[i] = 0;//setting value of this index to 0
        }
    }

    //private function to get sum of dice array
    private int getArraySum(Dice[] dice){
        int sumOfArray = 0;//int to hold sum of array
        for (int i = 0; i<dice.length; i++){//looping through dice array
            sumOfArray += dice[i].getValue();//adding value of dice to sumOfArray
        }
        return sumOfArray;//returning the sum of the array.
    }

    //private function to calculate the score options of any option that uses value count or sum of array
    //parameters are the results array that holds the score options, the valueCount array that holds the count of each dice value, and the sum of the dice values.
    private void calculateDiceShowingSameValue(int[] results, int[] valueCount, int sumOfArray){
        for (int i = 0; i<valueCount.length; i++){//looping through valueCount gives the amount of each dice value in this array
            results[i] = valueCount[i] * (i+1);//setting the amount of each dice value that exists in this array.
            if(valueCount[i]>=3){
                results[6] = sumOfArray;//if there are 3 or more of the same dice value, then the score at index 6 is set to the sum of all 5 dice.
            }

            if(valueCount[i]>=4){
                results[7] = sumOfArray;//if there are 4 or more of the same dice value, then the score at index 7 is set to the sum of all 5 dice.
            }
            if(valueCount[i]==5){
                results[11] = 50;//if there are 5 of the same dice value, then the score at index 11 is set to 50
            }
        }
        results[12] = sumOfArray;//if there are no patterns in the array of dice then the score option at 12 is the sum of the dice values.
    }

    //private function to calculate the full house score option.
    //parameters are the results array, and the value count array.
    private void calculateFullHouse(int[] results, int[] valueCount){
        if(results[6] != 0){//if the value of results at 6 is not 0, then there are 3 dice of one value.
            for (int i = 0; i<valueCount.length; i++){//looping through valueCount
                if(valueCount[i] == 2){//if there are 2 dice of the same value then there is a full house.
                    results[8] = 25;//if there is a full house, then results at index 8 is set to 25.
                    break;//end the loop if full house is found.
                }
            }
        }        
    }

    //private function to calculate if there are any consecutive values of dice. 
    //parameters are the results array, and the value count array.
    private void calculateConsecutive(int[] results, int[] valueCount){
        int consecutive = 0;//value to hold the amount of consecutive dice so far.
        for (int i = 0; i<valueCount.length; i++){//looping through valueCount
            if(valueCount[i] == 0){//if there are no dice of this value then the consecutive sequence is broken
                consecutive = 0;//thus consecutive is set to 0 again.
            }
            else{
                consecutive++;//if there are dice of this value, then consecutive is incremented by 1.
            }
            if(consecutive==4){//if there have been 4 consecutive dice thus far
            results[9] = 30;//results at index 9 is set to 30.
            }
            if(consecutive==5){//if there have been 5 consecutive dice thus far
            results[10] = 40;//results at index 10 is set to 40.
            }
        }
    }

    //public function that returns an array of scre options for this array of dice in yahtzee.
    //no parameters
    public int[] getScoreOptions(){
        int[] results = new int[13];//declaring the results array
        Dice[] dice = this.dice;//declaring dice as the instance variable dice.
        int[] valueCount = getValueCount();//using the private getValueCount function to declare an array holding the count of each value of dice.
        int sumOfArray = getArraySum(dice);//using the private getArraySum function to declare an int holding the sum of the array of dice.
        initializeArray(results);//using the private initializeArray function to initialize the values of the array to 0
        calculateDiceShowingSameValue(results, valueCount, sumOfArray);//using the private calculateDiceShowingSameValue function to calculate the results at indices 0-7, 11, and 12.
        calculateFullHouse(results, valueCount);//using the private calculateFullHouse function to check if a full house exists.
        calculateConsecutive(results, valueCount);//using the private calculateConsecutive function to check there are 4 or 5 consecutive dice.
        return results;//returning the results array holding the score options.
    }

    //public scoe function returns the max score along with the smallest index it is found at.
    public int[] score(){
        int[] results = getScoreOptions();//using the getScoreOptions function to retrive score options.
        int maxScore = 0;//an int variable to hold the highest score option.
        int scoreIndex = 0;//and int vairable to hold the index of this score option.
        for(int i = 0;  i<results.length; i++){//looping through the score options.
            if(results[i]>maxScore){//if the current score option has a higher score than the recorded highest score option.
                maxScore = results[i];//the highest score option is set to the current score option
                scoreIndex = i;//the index of the score option is set to the scoreIndex variable.
            }
        }
        return new int[]{maxScore, scoreIndex};//returning an array holding the max score and the smallest index its found at.
    }

    //public function that checks if 2 yahtzee dice arrays are equal.
    public boolean equals(Yahtzee other){
        return Arrays.equals(this.getValueCount(), other.getValueCount());//checking if the value count of each array is the same, if it is then the dice arrays are equal.
    }

    //public function that returns a string representation of the yahtzee dice array.
    public String toString(){
        String str = "Dice: {";//string starts with "Dice:"
        for(int i = 0; i<dice.length; i++){//looping through the dice values.
            if(i == 4){//if loop is at the last index, then a closing bracket is added with no space after the value.
                str += dice[i].getValue() + "}";
                break;
            }
            str += dice[i].getValue() + ", ";//if not at the last index, then the dice value is aded with a comma and a space after.
        }
        return str;//after the string value has been calculated, it is returned.
    }
}