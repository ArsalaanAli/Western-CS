import java.util.*;

public class Yahtzee{
    
    private Dice[] dice;

    public Yahtzee() {
        this.dice = new Dice[5];
        for (int i = 0; i<dice.length; i++) {
            dice[i] = new Dice();
            dice[i].roll();
        }
    }
    public Yahtzee(Dice[] dice) {
        this.dice = dice;
    }

    public int[] getValueCount(){
        int[] countValue = new int[6];
        for(int i = 0; i < dice.length; i++){
            countValue[dice[i].getValue()-1]++;
        }
        return countValue;
    }

    private void initializeArray(int[] results){
        for(int i = 6; i<13; i++){
            results[i] = 0;
        }
    }

    private int getArraySum(Dice[] dice){
        int sumOfArray = 0;
        for (int i = 0; i<dice.length; i++){
            sumOfArray += dice[i].getValue();
        }
        return sumOfArray;
    }

    private void calculateDiceShowingSameValue(int[] results, int[] valueCount, int sumOfArray){
        for (int i = 0; i<valueCount.length; i++){
            results[i] = valueCount[i] * (i+1);
            if(valueCount[i]>=3){
                results[6] = sumOfArray;
            }

            if(valueCount[i]>=4){
                results[7] = sumOfArray;
            }
            if(valueCount[i]==5){
                results[11] = 50;
            }
        }
        results[12] = sumOfArray;
    }

    private void calculateFullHouse(int[] results, int[] valueCount){
        if(results[6] != 0){
            for (int i = 0; i<valueCount.length; i++){
                if(valueCount[i] == 2){
                    results[8] = 25;
                    break;
                }
            }
        }        
    }

    private void calculateConsecutive(int[] results, int[] valueCount){
        int consecutive = 0;
        for (int i = 0; i<valueCount.length; i++){
            if(valueCount[i] == 0){
                consecutive = 0;
            }
            else{
                consecutive++;
            }
            if(consecutive==4){
            results[9] = 30;
            }
            if(consecutive==5){
            results[10] = 40;
            }
        }
    }

    public int[] getScoreOptions(){
        int[] results = new int[13];
        Dice[] dice = this.dice;
        int[] valueCount = getValueCount();
        int sumOfArray = getArraySum(dice);
        initializeArray(results);
        calculateDiceShowingSameValue(results, valueCount, sumOfArray);
        calculateFullHouse(results, valueCount);
        calculateConsecutive(results, valueCount);
        return results;
    }

    public int[] score(){
        int[] results = getScoreOptions();
        int maxScore = 0;
        int scoreIndex = 0;
        for(int i = 0;  i<results.length; i++){
            if(results[i]>maxScore){
                maxScore = results[i];
                scoreIndex = i;
            }
        }
        return new int[]{maxScore, scoreIndex};
    }

    public boolean equals(Yahtzee other){
        return Arrays.equals(this.getValueCount(), other.getValueCount());
    }

    public String toString(){
        String str = "Dice: {";
        for(int i = 0; i<dice.length; i++){
            if(i == 4){
                str += dice[i].getValue() + "}";
                break;
            }
            str += dice[i].getValue() + ", ";
        }
        return str;
    }

    public static void main(String[] args){
        Dice[] testArray = new Dice[5];
        testArray[0] = new Dice(4);
        testArray[1] = new Dice(4);
        testArray[2] = new Dice(4);
        testArray[3] = new Dice(4);
        testArray[4] = new Dice(4);
        Yahtzee x = new Yahtzee(testArray);
        int[] results = x.getScoreOptions();
        System.out.println(x.toString());
        System.out.println(Arrays.toString(results));
    }
}