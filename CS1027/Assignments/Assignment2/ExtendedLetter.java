public class ExtendedLetter extends Letter{
    private String content;
    private int family;
    private boolean related;
    private final int SINGLETON = -1;

    public ExtendedLetter(String s){
        super("a");
        this.content = s;
        this.related = false;
        this.family = this.SINGLETON;
    }

    public ExtendedLetter(String s, int fam){
        super("a");
        this.content = s;
        this.related = false;
        this.family = fam;
    }

    public boolean equals(Object other){
        if (other instanceof ExtendedLetter){
            return false;//FINISH THIS FUNCTION
        }
        return false;
    }

}