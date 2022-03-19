public class DLStack<T> implements DLStackADT<T> {
    private DoubleLinkedNode<T> top;//private instance variables
    private int numItems;
    
    public DLStack(){//constructor
        this.top = null;//sets top to null
        this.numItems = 0;//sets num items to 0
    }

    public void push(T dataItem){//adds item of type T to stack
        if(isEmpty()){
            top = new DoubleLinkedNode<T>(dataItem);//the the stack is empty the new item is the top of the stack
        }
        else{//if the stack isnt empty
            top.setNext(new DoubleLinkedNode<T>(dataItem));//the item is set as next for the top of the stack
            top.getNext().setPrevious(top);//the top is linked to the previous of item
            top = top.getNext();//the new item is set as top
        }
        numItems++;//the number of items incremented by one
    }

    public T pop() throws EmptyStackException{//removes an item from the stack
        if(isEmpty()){
            throw new EmptyStackException("Stack is empty");//if the stack is empty an item can't be removed, so an exception is thrown
        }
        T tmp = top.getElement();//gets the item in the Node at the top of the stack
        top = top.getPrevious();//set top to previous element
        if (top != null) {
            top.setNext(null);//the original top is removed from the stack
        }
        numItems--;//item counter is decreased
        return tmp;//returning the item that was removed from top
    }
    
    public T pop(int k) throws InvalidItemException{//popping the Kth item
        if(k <= 0 || k > numItems){//if k is too big or too small an exception is thrown
            throw new InvalidItemException("Index is out of range");
        }
        if(k == 1){
            return pop();//if k is 1, then it's just the pop function
        }
        else{
            DoubleLinkedNode<T> cur = top;
            for(int i = 0; i<k-1; i++){//looping through the stack to get to the Kth node
                cur = cur.getPrevious();
            }
            T tmp = cur.getElement();//getting the element inside the node
            removeNode(cur);//removing the node from the stack
            return tmp;//returning the element inside the removed node
        }
    }

    public T peek()throws EmptyStackException{
        if(isEmpty()){
            throw new EmptyStackException("Stack is empty");//throwing exception if the stack is empty
        }
        return top.getElement();//retuning the element inside the top node
    }
    
    public boolean isEmpty(){
        return top==null;//if there is no top, the stack is empty
    }

    public int size(){
        return numItems;//returns the size of the stack
    }

    public DoubleLinkedNode<T> getTop(){
        return top;//returns the top node of the stack
    }

    public String toString(){//returns a string representation of the stack
        String str = "[";//opening bracket
        DoubleLinkedNode<T> cur = top;
        while (cur != null) {
            str += " " + cur.getElement().toString();//adding each element from the stack to the string
            cur=cur.getPrevious();
        }
        str += "]";//adding a closing bracket
        return str;//returning the string
    }

    private void removeNode(DoubleLinkedNode<T> cur){//private helper function to move a node from the stack
        if(cur.getPrevious() != null){//if the node has a previous node
            cur.getPrevious().setNext(cur.getNext());//the current node is removed as the next node for the previous node
        }
        if (cur.getNext() != null) {//if the node has a next node
            cur.getNext().setPrevious(cur.getPrevious());//the current node is removed as the prvious node for the next node
        }
        numItems--;//the amount of items is decreased by 1
    }
}