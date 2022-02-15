public class Word{
    private LinearNode<Letter> firstLetter;

    public Word(Letter[] letters){
        LinearNode<Letter> previousLetter = null;
        LinearNode<Letter> currentLetter = null;
        for(int i = 0; i<letters.length; i++){
            currentLetter = new LinearNode(letters[i]);
            if(i == 0){
                this.firstLetter = currentLetter;
                previousLetter = currentLetter;
                continue;
            }
            previousLetter.setNext(currentLetter);
            previousLetter = currentLetter;
        }
    }

    @Override
    public String toString(){
        String str = "Word: ";
        LinearNode<Letter> currentNode = firstLetter;
        while(currentNode != null){
            if(currentNode.getNext() == null){
                str += currentNode.getElement().toString();
                break;
            }
            str += currentNode.getElement().toString() + " ";
            currentNode = currentNode.getNext();
        }
        return str;
    }

    private boolean contains(LinearNode<Letter> letter){
        LinearNode<Letter> currentNode = firstLetter;
        while(currentNode != null){
            if(currentNode.getElement().equals(letter.getElement())){
                return true;
            }
            currentNode = currentNode.getNext();
        }
        return false;
    }

    public boolean labelWord(Word mystery){
        LinearNode<Letter> otherNode = mystery.firstLetter;
        LinearNode<Letter> thisNode = this.firstLetter;
        boolean isEqual = true;
        while(true){
            if(thisNode == null || otherNode == null){
                if(thisNode == null && otherNode == null){
                    break;
                }
                isEqual = false;
                break;
            }
            if(thisNode.getElement().equals(otherNode.getElement())){
                thisNode.getElement().setCorrect();
            }
            else{
                if(mystery.contains(thisNode)){
                    thisNode.getElement().setUsed();
                }
                else{
                    thisNode.getElement().setUnused();
                }
                isEqual = false;
            }
            thisNode = thisNode.getNext();
            otherNode = otherNode.getNext();
        }
        return isEqual;
    }
}