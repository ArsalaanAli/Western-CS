
public class BuildDLL {
	
	DoubleLinkedNode<Character> front, rear;
	private static char[] letters = new char[] {'K', 'T', 'E', 'N', 'P', 'A', 'L'};

	public BuildDLL () {
		build();
	}
	
	

	public void remove (Character elem) {
		// Add code in here to remove the node with the given value.
		DoubleLinkedNode<Character> current = front;
		while(true){
			if(current.getElement() == elem){
				if(current == front){
					front = front.getNext();
					front.setPrevious(null);
					return;
				}
				if(current == rear){
					rear = rear.getPrevious();
					rear.setNext(null);
					return;
				}
				current.getPrevious().setNext(current.getNext());
				current.getNext().setPrevious(current.getPrevious());
				return;
			}
			current = current.getNext();
		}
	}
	
	
	private void build () {
		DoubleLinkedNode<Character> pnode, node;
		
		node = new DoubleLinkedNode<Character>(letters[0]);
		pnode = front = node;
		for (int i = 1; i < 7; i++) {
			node = new DoubleLinkedNode<Character>(letters[i]);
			pnode.setNext(node);
			node.setPrevious(pnode);
			pnode = node;
		}
		rear = node;
	}
	
	public DoubleLinkedNode<Character> getFront () {
		return front;
	}
	
	public DoubleLinkedNode<Character> getRear () {
		return rear;
	}
	
	public void printF (DoubleLinkedNode<Character> node) {
		
		DoubleLinkedNode<Character> curr = front;
		while (curr != null) {
			System.out.print(curr.getElement() + " ");
			curr = curr.getNext();
		}
		System.out.print("\n");
	}
	
	
	public static void main (String[] args) {
		BuildDLL dll = new BuildDLL();

		System.out.println("Original List:");
		dll.printF(dll.getFront());
		System.out.println("***");
		
		System.out.println("Removing an internal node:");
		dll.remove('N');
		dll.printF(dll.getFront());
		System.out.println("***");
		
		System.out.println("Removing the front node:");
		dll.remove('K');
		dll.printF(dll.getFront());
		System.out.println("***");
		
		System.out.println("Removing the rear node:");
		dll.remove('L');
		dll.printF(dll.getFront());
		System.out.println("***");
	}

}
