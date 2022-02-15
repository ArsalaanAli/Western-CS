public class ExtendedLetter extends Letter{
    private String content;
    private int family;
    private boolean related;
    private final int SINGLETON = -1;

    public ExtendedLetter(String s){
        super('a');
        this.content = s;
        this.related = false;
        this.family = this.SINGLETON;
    }

    public ExtendedLetter(String s, int fam){
        super('a');
        this.content = s;
        this.related = false;
        this.family = fam;
    }

    public boolean equals(Object other){
        if (other instanceof ExtendedLetter){
            ExtendedLetter otherExtendedLetter = (ExtendedLetter) other;
            if(this.family == otherExtendedLetter.family){
                this.related = true;
            }
            if(this.content == otherExtendedLetter.content){
                return true;
            }
        }
        return false;
    }

    public String toString(){
        if(decorator() == "-" && this.related){
            return "." + this.content + ".";
        }
        return decorator() + this.content + decorator();
    }

    public static Letter[] fromStrings(String[] content, int[] codes){
        Letter[] letters = new Letter[content.length];
        if(codes == null){
            for(int i = 0; i < content.length; i++){
                letters[i] = new ExtendedLetter(content[i]);
            }
        }
        else{
            for(int i = 0; i  < content.length; i++){
                letters[i] = new ExtendedLetter(content[i], codes[i]);
            }
        }
        return letters;
    }

}