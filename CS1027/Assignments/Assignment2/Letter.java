public class Letter{
    //fields
    private char letter;
    private int label;
    private static final int UNSET = 0, UNUSED = 1, USED = 2, CORRECT = 3; //global constants
    
    public Letter(char c){//constructor takes a character and sets the field to it
        label = UNSET;
        letter = c;
    }

    @Override
    public boolean equals(Object otherObject){//equals function checks if two letter objects have the same contents
        if(otherObject instanceof Letter){
            Letter object = (Letter) otherObject;//if both objects are letter type objects
            if (this.letter == object.letter){//checking if content is the same
                return true;
            }
            return false;
        }
        return false;//else returning false
    }

    public String decorator() {//returns a decorator based on the label of the function
        if(label == UNSET){
            return " ";
        }
        if(label == UNUSED){
            return "-";
        }
        if(label == USED){
            return "+";
        }
        if(label == CORRECT){
            return "!";
        }
        return "";
    }

    @Override
    public String toString(){//returns letter content as a string
        return decorator() + letter + decorator();//returns the decorator along with the content of the letter
    }

    //setter functions for label
    public void setUnused(){
        label = UNUSED;
    }

    public void setUsed(){
        label = USED;
    }

    public void setCorrect(){
        label = CORRECT;
    }
    
    public boolean isUnused(){
        return label == UNUSED;//function to check if the letter is unused
    }

    public static Letter[] fromString(String s){//static function that returns a list of letters formed from the characters in a string
        Letter[] array = new Letter[s.length()];
        for(int i = 0; i <s.length(); i++){
            array[i] = new Letter(s.charAt(i));//creating a letter with each char in string and adding it to array
        }
        return array;
    }

}