public class Dictionary implements DictionaryADT {
    private Node[] table;
    private int numRecords;

    public Dictionary(int size) {
        this.table = new Node[size];
        this.numRecords = 0;
    }
    
    public int put(Record rec) throws DuplicatedKeyException {
        String key = rec.getKey();
        int hash = polynomialHash(key);

        if (this.table[hash] == null) {
            this.table[hash] = new Node(rec);
            this.numRecords++;
            return 0;
        }
        Node current = this.table[hash];
        while (true) {
            if (current.getKey().equals(key)) {
                throw new DuplicatedKeyException("this record already exists in the dictionary");
            }
            if (current.getNextNode() != null) {
                current = current.getNextNode();
            } else {
                break;
            }
        }
        current.setNextNode(new Node(rec));
        this.numRecords++;
        return 1;
    }

    public void remove(String key) throws InexistentKeyException {
        int hash = polynomialHash(key);
        if (this.table[hash] == null) {
            throw new InexistentKeyException("This record does not exist in the dictionary");
        }
        Node current = this.table[hash];
        if (current.getKey().equals(key)) {
            this.table[hash] = current.getNextNode();
            this.numRecords--;
            return;
        }

        while (current.getNextNode() != null) {
            if (current.getNextNode().getKey().equals(key)) {
                current.setNextNode(current.getNextNode().getNextNode());
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







