public class ExtendedLetter extends Letter{
    //fields
    private String content;
    private int family;
    private boolean related;
    private final int SINGLETON = -1;

    //constructor
    public ExtendedLetter(String s){
        super('a');
        this.content = s;
        this.related = false;
        this.family = this.SINGLETON;
    }

    //overloaded constructor takes a family integer
    public ExtendedLetter(String s, int fam){
        super('a');
        this.content = s;
        this.related = false;
        this.family = fam;
    }

    @Override
    public boolean equals(Object other){//checks if other object is equal to this extended letter object
        if (other instanceof ExtendedLetter){
            ExtendedLetter otherExtendedLetter = (ExtendedLetter) other;//if the other object is an extendedletter object
            if(this.family == otherExtendedLetter.family){
                this.related = true;//if the familes of the two objects are the same, then are related
            }
            if(this.content == otherExtendedLetter.content){
                return true;//if the content of both objects is equal then returns true
            }
        }
        return false;//else returns false
    }

    public String toString(){//turns the content of this extended letter as a string
        if(decorator() == "-" && this.related){
            return "." + this.content + ".";//if the objects are related and the letter is unused then returning with the '.' decorator
        }
        return decorator() + this.content + decorator();//else returning with the existing decorator
    }

    public static Letter[] fromStrings(String[] content, int[] codes){//creating a letter array from an array of strings and codes
        Letter[] letters = new Letter[content.length];
        if(codes == null){
            for(int i = 0; i < content.length; i++){
                letters[i] = new ExtendedLetter(content[i]);//if there are no codes then creating extended letters with no codes and storing them in the letter array
            }
        }
        else{
            for(int i = 0; i  < content.length; i++){
                letters[i] = new ExtendedLetter(content[i], codes[i]);//else creating extended letters with codes and storing them in the letter array
            }
        }
        return letters;//returning the letter array
    }

}