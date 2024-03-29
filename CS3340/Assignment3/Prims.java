import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Prims {
    static int numVerts;
    static ArrayList<ArrayList<Integer[]>> adjacencyList;
    static int[] parents;

    public static void main(String[] args) {
        adjacencyList = new ArrayList<ArrayList<Integer[]>>();
        
        //Input from txt
        readFile();

        //Input Graph
        printList();

        //Running MST Algo
        runPrims();

    }

    private static void runPrims() {
        int[] initList = new int[adjacencyList.size()];
        initList[0] = 0;
        for (int i = 1; i < adjacencyList.size(); i++) {
            initList[i] = Integer.MAX_VALUE;
        }
        Heap heap = new Heap(initList, initList.length);
        int weight = 0;
        while (!heap.is_empty()) {
            int curId = heap.min_id();
            int curKey = heap.min_key();
            heap.delete_min();
            System.out.println("(" + parents[curId] + "," + curId + "): " + curKey);
            weight += curKey;
            for (Integer[] neighbour : adjacencyList.get(curId)) {
                if (heap.decrease_key(neighbour[0], neighbour[1])) {
                    parents[neighbour[0]] = curId;
                }
            }
        }
        System.out.println();
        System.out.println("Weight of MST: " + weight);

    }
    
    private static void readFile() {
        String fileName = "mst_graph.txt";

        try {
            Scanner scanner = new Scanner(new File(fileName));
            scanner.useDelimiter("\\s+");
            numVerts = Integer.parseInt(scanner.next());
            parents = new int[numVerts + 1];
            parents[1] = 1;
            for (int i = 0; i < numVerts + 1; i++) {
                adjacencyList.add(new ArrayList<Integer[]>());
            }
            while (scanner.hasNext()) {
                int i = Integer.parseInt(scanner.next());
                int j = Integer.parseInt(scanner.next());
                int w = Integer.parseInt(scanner.next());

                adjacencyList.get(i).add(new Integer[] { j, w });
                adjacencyList.get(j).add(new Integer[] { i, w });
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
    
    private static void printList() {
        for (int i = 0; i < adjacencyList.size(); i++) {
            System.out.print(i + " ");
            for (Integer[] a : adjacencyList.get(i)) {
                System.out.print(Arrays.toString(a) + " ");
            }
            System.out.println();
        }
    }
}
