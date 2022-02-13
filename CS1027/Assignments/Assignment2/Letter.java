public class Letter{
    private char letter;
    private int label;
    private static final int UNSET = 0, UNUSED = 1, USED = 2, CORRECT = 3;
    
    public Letter(char c){
        label = UNSET;
        letter = c;
    }

    public boolean equals(Object otherObject){
        if(otherObject instanceof Letter){
            Letter object = (Letter) otherObject;
            if (this.letter == object.letter){
                return true;
            }
            return false;
        }
        return false;
    }

    public String decorator() {
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
    public String toString(){
        return decorator() + letter + decorator();
    }

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
        return label == UNUSED;
    }

    public static Letter[] fromString(String s){
        Letter[] array = new Letter[s.length()];
        for(int i = 0; i <s.length(); i++){
            array[i] = new Letter(s.charAt(i));
        }
        return array;
    }

}