public class Word{
    //fields
    private LinearNode<Letter> firstLetter;

    public Word(Letter[] letters){//constructor takes an array of letters
        LinearNode<Letter> previousLetter = null;
        LinearNode<Letter> currentLetter = null;
        for(int i = 0; i<letters.length; i++){
            currentLetter = new LinearNode<Letter>(letters[i]);
            if(i == 0){
                this.firstLetter = currentLetter;//creating a linked list with the letter array and saving its head as the field firstLetter
                previousLetter = currentLetter;
                continue;
            }
            previousLetter.setNext(currentLetter);
            previousLetter = currentLetter;
        }
    }

    @Override
    public String toString(){//returns content of linked list as a string
        String str = "Word: ";
        LinearNode<Letter> currentNode = firstLetter;
        while(currentNode != null){//looping though linked list
            str += currentNode.getElement().toString() + " ";//adding each element to string
            currentNode = currentNode.getNext();
        }
        return str;
    }

    private boolean contains(LinearNode<Letter> letter){//checks if a certain letter equals any letters in this list
        LinearNode<Letter> currentNode = firstLetter;
        while(currentNode != null){//loops through this linked list
            if(letter.getElement().equals(currentNode.getElement())){//if the letter is in the list then returns true
                return true;
            }
            currentNode = currentNode.getNext();
        }
        return false;
    }

    public boolean labelWord(Word mystery){//labels the letters of each word by comparing them to the mystery word
        LinearNode<Letter> otherNode = mystery.firstLetter;
        LinearNode<Letter> thisNode = this.firstLetter;
        boolean isEqual = true;
        while(thisNode != null){//looping through this word
            if(otherNode == null){//if the other word is shorter than this word then they arenot equal
                isEqual = false;
            }
            else if(thisNode.getElement().equals(otherNode.getElement())){//checks if the other letter at the same index is equal to this word
                    thisNode.getElement().setCorrect();//if they are equal and at the same location then the label of this letter is set to correct
                    thisNode = thisNode.getNext();
                    otherNode = otherNode.getNext();
                    continue;
            }
            isEqual = false;
            if(mystery.contains(thisNode)){//if the two letters at the same index arent equal then check if this letter exists any where else in mystery 
                    thisNode.getElement().setUsed();//if it does then set label as used
                }
                else{
                    thisNode.getElement().setUnused();//else set label as false
                }
            thisNode = thisNode.getNext();//looping through this node
            otherNode = (otherNode == null ? null : otherNode.getNext());//looping through other node unless its equal to null, then we stop looping
        }
        return isEqual;//returning true if the two words have the same letters at the same locations
    }
}