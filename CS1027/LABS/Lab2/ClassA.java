public class ClassA {
	private final int SIZE_ARRAY = 5;
	public int numItems;
	public int[] arrItems;

	public ClassA(int n, int[] arr) {
		this.numItems = n;
		this.arrItems = arr;
	}

	public ClassA() {
		this.numItems = 0;
		this.arrItems = new int[SIZE_ARRAY];
	}

	public boolean equals(ClassA other){
		if (numItems == other.numItems){
			if((this.arrItems == other.arrItems) && (this.arrItems == null)){
				return true;
			}
			if(this.arrItems == null || other.arrItems == null){
				return false;
			}
			if(arrItems.length == other.arrItems.length){
				for(int i = 0; i< arrItems.length; i++){
					if(this.arrItems[i] != other.arrItems[i]){
						return false;
				}
				return true;
			}
			return false;
		}
	}
	return false;
}
}
