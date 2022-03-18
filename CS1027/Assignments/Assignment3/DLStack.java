public class DLStack<T> implements DLStackADT<T> {
    private DoubleLinkedNode<T> top;
    private int numItems;
    
    public DLStack(){
        this.top = null;
        this.numItems = 0;
    }

    public void push(T dataItem){
        if(isEmpty()){
            top = new DoubleLinkedNode<T>(dataItem);
        }
        else{
            top.setNext(new DoubleLinkedNode<T>(dataItem));
            top.getNext().setPrevious(top);
            top = top.getNext();
        }
        numItems++;
    }

    public T pop() throws EmptyStackException{
        if(isEmpty()){
            throw new EmptyStackException("Stack is empty");
        }
        T tmp = top.getElement();
        top = top.getPrevious();
        numItems--;
        return tmp;
    }
    
    public T pop(int k) throws InvalidItemException{
        if(k <= 0 || k > numItems){
            throw new InvalidItemException("Index is out of range");
        }
        if(k == 1){
            return pop();
        }
        else{
            DoubleLinkedNode<T> cur = top;
            for(int i = 0; i<k-1; i++){
                cur = cur.getPrevious();
            }
            T tmp = cur.getElement();
            removeNode(cur);
            return tmp;
        }
    }

    public T peek()throws EmptyStackException{
        if(isEmpty()){
            throw new EmptyStackException("Stack is empty");
        }
        return top.getElement();
    }
    
    public boolean isEmpty(){
        return top==null;
    }

    public int size(){
        return numItems;
    }

    public DoubleLinkedNode<T> getTop(){
        return top;
    }

    public String toString(){
        String str = "[";
        DoubleLinkedNode cur = top;
        while (cur != null) {
            str += " " + cur.getElement().toString();
            cur=cur.getPrevious();
        }
        str += "]";
        return str;
    }

    private void removeNode(DoubleLinkedNode<T> cur){
        if(cur.getPrevious() != null){
            cur.getPrevious().setNext(cur.getNext());
        }
        if (cur.getNext() != null) {
            cur.getNext().setPrevious(cur.getPrevious());
        }
        numItems--;
    }
}