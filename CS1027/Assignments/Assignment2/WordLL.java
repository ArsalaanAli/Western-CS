public class WordLL{
    //field
    private Word mysteryWord;
    private LinearNode<Word> history;

    //constructor takes a mystery word
    public WordLL(Word mystery){
        history = null;
        this.mysteryWord = mystery;
    }

    public boolean tryWord(Word guess){//tries a word as a guess
        boolean correct = guess.labelWord(mysteryWord);//checks if the guess is correct and labels the letters in the guess
        LinearNode<Word> guessNode = new LinearNode<Word>(guess);//creates a node holding the guess
        guessNode.setNext(history);//adds the current guess to the history of guesses
        history = guessNode;//setting the current guess as the head of the history
        return correct;//returning true if the guess was correct
    }

    public String toString(){//returns a string of the history of guesses
        LinearNode<Word> current = history;
        String str = "";//string that holds the history
        while(current != null){//looping through history
            str += current.getElement().toString() + "\n";//adding current element to the string
            current = current.getNext();
        }
        return str;//returning string
    }
}