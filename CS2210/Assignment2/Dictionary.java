public class Dictionary implements DictionaryADT {
    //instance variables
    private Node[] table;//array that holds the contents of the dictionary
    private int numRecords;//variable to keep track of the number of records in the dictionary

    public Dictionary(int size) {
        this.table = new Node[size];//intializing the dictionary
        this.numRecords = 0;//number of records set to 0
    }

    public int put(Record rec) throws DuplicatedKeyException {//function to put a record into the dictionary
        String key = rec.getKey();
        int hash = polynomialHash(key);//hashing the key of the record

        if (this.table[hash] == null) {//checking if dict[hash] has a record already
            this.table[hash] = new Node(rec);//adding a record with a node wrapper to this spot in the dictionary
            this.numRecords++;//increasing the number of records by 1
            return 0;//returing 0 because there's no collision
        }
        Node current = this.table[hash];//if there is a record already in the dictionary at this spot
        while (true) {
            if (current.getKey().equals(key)) {
                throw new DuplicatedKeyException("this record already exists in the dictionary");//checking to see if the record already exists in the dict
            }
            if (current.getNextNode() != null) {
                current = current.getNextNode();//if the key doesn't already exist, loop to the end of the linked list
            } else {
                break;
            }
        }
        current.setNextNode(new Node(rec));//add the current node to the end of the linked list
        this.numRecords++;//increase num records by 1
        return 1;//returning 1 because there was a collision
    }

    public void remove(String key) throws InexistentKeyException {//function to remove a record from the dictionary
        int hash = polynomialHash(key);//getting the hash of the key
        if (this.table[hash] == null) {
            throw new InexistentKeyException("This record does not exist in the dictionary");//if the key doesn't exist, throw an exception
        }
        Node current = this.table[hash];//if the key exists, we get its spot in the dictionary
        if (current.getKey().equals(key)) {//checking if the current node in the linked list is the right record
            this.table[hash] = current.getNextNode();//if it is, then the record is removed from the linked list
            this.numRecords--;//num records is decreased by 1
            return;
        }

        while (current.getNextNode() != null) {//searching through linked list for the key
            if (current.getNextNode().getKey().equals(key)) {//if the node after the current node has the right key
                current.setNextNode(current.getNextNode().getNextNode());//the node is removed from the linked list
                this.numRecords--;
                return;
            }
            current = current.getNextNode();
        }
        throw new InexistentKeyException("This record does not exist in the dictionary");
    }

    public Record get(String key) {
        int hash = polynomialHash(key);
        if (this.table[hash] == null) {
            return null;
        }
        Node current = this.table[hash];
        while (current != null) {
            if (current.getKey().equals(key)) {
                return current.getRecord();
            }
            current = current.getNextNode();
        }
        return null;
    }

    public int numRecords() {
        return this.numRecords;
    }

    private int polynomialHash(String key) {
        int hash = 0;
        int HASHCONSTANT = 33;
        for (int i = 0; i < key.length(); i++) {
            char currentChar = key.charAt(i);
            hash += currentChar * Math.pow(HASHCONSTANT, key.length() - i - 1.0);
            hash %= table.length;
        }
        return hash;
    }
}

class Record {
    private String key;
    private int score, level;

    public Record(String key, int score, int level) {
        this.key = key;
        this.score = score;
        this.level = level;
    }

    public String getKey() {
        return this.key;
    }

    public int getScore() {
        return this.score;
    }

    public int getLevel() {
        return this.level;
    }    
}

class Node {
    private Record rec;
    private Node nextNode;

    public Node(Record rec) {
        this.rec = rec;
        this.nextNode = null;
    }
    
    public String getKey() {
        return rec.getKey();
    }

    public Node getNextNode() {
        return this.nextNode;
    }

    public Record getRecord() {
        return this.rec;
    }

    public void setNextNode(Node next){
        this.nextNode = next;
    }
}