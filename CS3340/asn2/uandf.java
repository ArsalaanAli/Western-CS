import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

class uandf{
    private int[] parents;
    private int[] rank;
    private boolean finalized;
    private int no_sets = 0;

    public uandf(int n){
        parents = new int[n + 1];
        rank = new int[n+1];
        for (int i = 1; i <= n; i++) {
            parents[i] = 0;
            rank[i] = 1;
        }
    }

    public void make_set(int i) {
        if (finalized) {
            return;
        }
        parents[i] = i;
    }

    public int find_set(int i) {
        if(parents[i] == i){
            return i;
        }
        int rep = find_set(parents[i]);

        parents[i] = rep;
        return rep;
    }

    public void union_sets(int i, int j) {

        if (finalized) {
            return;
        }
        int ipar = find_set(i);
        int jpar = find_set(j);

        if (ipar == jpar) {
            return;
        }

        if (ipar == 0) {
            parents[i] = jpar;
            return;
        }
        if (jpar == 0) {
            parents[j] = ipar;
            return;
        }

        if(rank[ipar] >= rank[jpar]){
            parents[jpar] = ipar;
        }
        else{
            parents[ipar] = jpar;
        }
        if (rank[ipar] == rank[jpar]) {
            rank[ipar] += 1;
        }
    }

    public int final_sets() {
        if (finalized) {
            return no_sets;
        }
        
        int curSet = 1;
        HashMap<Integer, Integer> setMap = new HashMap<>();
        for (int i = 1; i < parents.length; i++) {
            find_set(i);
            if (setMap.containsKey(parents[i]) || parents[i] == 0) {
                continue;
            }
            setMap.put(parents[i], curSet);
            no_sets++;
            curSet++;
        }
        for (int i = 1; i < parents.length; i++) {
            if (parents[i] == 0) {
                continue;
            }
            parents[i] = setMap.get(parents[i]);
        }
        finalized = true;
        return no_sets;
    }

    
    
    public static void main(String[] args) {
        String fileName = "face.img.txt";
        String[] imageArray = new String[72];

        //file input
        try (Scanner scanner = new Scanner(System.in)) {
            int curLine = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                imageArray[curLine] = line;
                curLine++;
            }
        }

        //Create Disjoint Set from connected componenets
        uandf imageSet = new uandf(72 * 75);
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 75; j++) {
                if (imageArray[i].charAt(j) == '+') {
                    int currentNode = i * 75 + j + 1;
                    int curPar = imageSet.find_set(currentNode);
                    if (curPar == 0) {
                        imageSet.make_set(currentNode);
                    }
                    for (int k = -1; k <= 1; k++) {
                        for (int l = -1; l <= 1; l++) {
                            if (k == 0 && l == 0) {
                                continue;
                            }
                            int x = i + k;
                            int y = j + l;
                            if (x < 0 || x >= 72 || y < 0 || y >= 75) {
                                continue;
                            }
                            if (imageArray[x].charAt(y) != '+') {
                                continue;
                            }
                            int otherNode = x * 75 + y + 1;
                            imageSet.union_sets(currentNode, otherNode);
                        }
                    }
                }
            }
        }
        
        imageSet.final_sets();


        //Part 1: Input Image
        for (String s : imageArray) {
            System.out.println(s);
        }

        //Part 2: Connected Component Image
        char[] componentLabels = new char[26];
        int[] componentSizes = new int[26];
        for (int i = 0; i < 25; i++) {
            componentLabels[i+1] = (char) ('a' + i);
        }
        
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 75; j++) {
                int currentNode = i * 75 + j + 1;
                int rep = imageSet.parents[currentNode];
                if (rep == 0) {
                    System.out.print(' ');
                } else {
                    System.out.print(componentLabels[rep]);
                    componentSizes[rep]++;
                }
            }
            System.out.println();
        }

        //Part 3: Sorted Components
        TreeMap<Character, Integer> componentMap = new TreeMap<>();
        

        for (int i = 1; i < 16; i++) {
            componentMap.put(componentLabels[i], componentSizes[i]);
        }

        Comparator<Character> valueComparator = (char1, char2) -> {
            int valueCompare = componentMap.get(char1).compareTo(componentMap.get(char2));
            return valueCompare != 0 ? valueCompare : char1.compareTo(char2);
        };

        TreeMap<Character, Integer> sortedByValueMap = new TreeMap<>(valueComparator);
        sortedByValueMap.putAll(componentMap);


        for (Map.Entry<Character, Integer> entry : sortedByValueMap.entrySet()) {
            System.out.println("Key: " + entry.getKey() + ", Value: " + entry.getValue());
        }

        //Part 4: Components greater than 2
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 75; j++) {
                int currentNode = i * 75 + j + 1;
                int rep = imageSet.parents[currentNode];
                if (rep == 0 || componentSizes[rep] <= 2) {
                    System.out.print(' ');
                    continue;
                } else {
                    System.out.print(componentLabels[rep]);
                }
            }
            System.out.println();
        }

        //Part 5: Components greater than 11
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 75; j++) {
                int currentNode = i * 75 + j + 1;
                int rep = imageSet.parents[currentNode];
                if (rep == 0 || componentSizes[rep] <= 11) {
                    System.out.print(' ');
                    continue;
                } else {
                    System.out.print(componentLabels[rep]);
                }
            }
            System.out.println();
        }
    }
}   