public class  ReversibleArray<T>{
    private T[] array;
    private int count;

    public ReversibleArray(T[] array){
        this.array = array;
        count = array.length;
    }

    public String toString(){
        String str = "";
        for(int i = 0; i<count; i++){
            if (i == count-1){
                str += array[i] + "";
                break;
            }
            str += array[i] + ", ";
        }
        return str;
    }

    public void reverse(){
        for(int i = 0; i<(count/2); i++){
            T temp = array[i];
            array[i] = array[count-1-i];
            array[count-1-i] = temp;
        }
    }
}