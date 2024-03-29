import java.util.Arrays;

public class Heap {
    private int[] array;
    private int[] heap;
    private int n;

    public Heap(int[] keys, int n) {
        this.n = n;
        array = new int[n + 1];
        array[0] = Integer.MAX_VALUE;
        heap = new int[2 * n];
        for (int i = 0; i < n; i++) {
            array[i + 1] = keys[i];
        }
        heapify();
    }
    
    private void heapify() {
        for (int i = 1; i <= n; i++) {
            heap[i + n - 1] = i;
        }
        for (int i = n - 1; i >= 1; i--) {
            int left = i * 2;
            int right = i * 2 + 1;
            heap[i] = array[heap[left]] < array[heap[right]] ? heap[left] : heap[right];
        }
    }

    public boolean in_heap(int i) {
        return heap[i + n - 1] != 0;
    }

    public boolean is_empty() {
        return n == 0 ? true : heap[1] == 0;
    }

    public int min_key() {
        return array[heap[1]];
    }

    public int min_id() {
        return heap[1];
    }

    public int key(int id) {
        return array[id];
    }

    public void delete_min() {
        if (array[heap[1]] == Integer.MAX_VALUE) {
            return;
        }
        heap[heap[1] + n - 1] = 0;
        int i = (heap[1] + n - 1) / 2;
        while (i >= 1) {
            if (array[heap[2 * i]] < array[heap[2 * i + 1]]) {
                heap[i] = heap[2 * i];
            } else {
                heap[i] = heap[2 * i + 1];
            }
            i /= 2;
        }
    }

    public boolean decrease_key(int id, int new_key) {
        if (array[id] <= new_key) {
            return false;
        }
        array[id] = new_key;
        int i = (id + n - 1) / 2;
        while (i >= 1) {
            if (array[heap[2 * i]] < array[heap[2 * i + 1]]) {
                heap[i] = heap[2 * i];
            } else {
                heap[i] = heap[2 * i + 1];
            }
            i /= 2;
        }
        return true;
    }
}