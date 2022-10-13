public interface DictionaryADT {

    public int put (Record rec) throws DuplicatedKeyException;

    public void remove (String key) throws InexistentKeyException;

    public Record get (String key);

    public int numRecords();
}