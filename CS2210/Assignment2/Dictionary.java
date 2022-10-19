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
                this.numRecords--;//num records is decreased by 1
                return;
            }
            current = current.getNextNode();//if the key wasnt found, we loop to the next node
        }
        throw new InexistentKeyException("This record does not exist in the dictionary");//if the node is not found, this exception is thrown
    }

    public Record get(String key) {//function to retrive a record from the dictionary
        int hash = polynomialHash(key);//getting the hash of the key
        if (this.table[hash] == null) {//if the key is not in the dictionary return null
            return null;
        }
        Node current = this.table[hash];//if there are records in the dictionary at this spot
        while (current != null) {//loop through the linked list at the spot
            if (current.getKey().equals(key)) {//if the key is found in the dictionary, return the record
                return current.getRecord();
            }
            current = current.getNextNode();
        }
        return null;//if the key is not found in the linked
    }

    public int numRecords() {
        return this.numRecords;//returns the number of records in the dictionary
    }

    private int polynomialHash(String key) {//function to return the hash of a string
        int hash = 0;
        int HASHCONSTANT = 33;//a constant used for the polynomial hash function 
        for (int i = 0; i < key.length(); i++) {//looping through characters in the key
            char currentChar = key.charAt(i);
            hash += currentChar * Math.pow(HASHCONSTANT, key.length() - i - 1.0);//calculating the current turn of the hash and adding it to the hash
            hash %= table.length;//modulus the has by the length of the table
        }
        return hash;//return the calculated hash
    }
}



class Node {//custom linked list node class, wrapper for Record class
    //instance variables
    private Record rec;//holds the record value
    private Node nextNode;//points to the next node

    public Node(Record rec) {//constructor sets the value of the instance variables to the parameters
        this.rec = rec;
        this.nextNode = null;
    }
    
    //getter functions for instance variables
    public String getKey() {
        return rec.getKey();
    }

    public Node getNextNode() {
        return this.nextNode;
    }

    public Record getRecord() {
        return this.rec;
    }
    //setter function for nextNode
    public void setNextNode(Node next){
        this.nextNode = next;
    }
}