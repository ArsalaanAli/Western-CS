import java.io.File;  // Import the File class
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.Iterator;

public class MyMap {
    private int start, end, width, length, privateRoads, constRoads;
    private Graph graph;

    public MyMap(String inputFile) throws MapException {
        try {
            File inputRead = new File(inputFile);
            Scanner input = new Scanner(inputRead);
            input.nextLine();
            this.start = Integer.parseInt(input.nextLine());
            this.end = Integer.parseInt(input.nextLine());
            this.width = Integer.parseInt(input.nextLine());
            this.length = Integer.parseInt(input.nextLine());
            this.privateRoads = Integer.parseInt(input.nextLine());
            this.constRoads = Integer.parseInt(input.nextLine());
            String[] inputMap = new String[(length * 2) - 1];
            for (int i = 0; i < inputMap.length; i++) {
                inputMap[i] = input.nextLine();
            }
            for (int i = 0; i < inputMap.length; i++) {
                System.out.println(inputMap[i]);
            }
            this.graph = buildGraph(inputMap);
            input.close();
        } catch (Exception e) {
            throw new MapException("input file does not exist");
        }
    }
    
    private Graph buildGraph(String[] inputMap) {
        Graph inputGraph = new Graph(width * length);
        int nodeNum = -1;
        for (int y = 0; y < inputMap.length; y++) {
            for (int x = 0; x < inputMap[y].length(); x++) {
                if (y % 2 == 0) {
                    if (inputMap[y].charAt(x) == '+') {
                        nodeNum++;
                        try {
                            Node curNode = inputGraph.getNode(nodeNum);
                            if (x - 1 > 0) {
                                if (inputMap[y].charAt(x - 1) == 'V') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "private");
                                } else if (inputMap[y].charAt(x - 1) == 'P') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "public");
                                } else if (inputMap[y].charAt(x - 1) == 'C') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "construction");
                                }
                            }
                            if (y - 1 > 0) {
                                if (inputMap[y - 1].charAt(x) == 'V') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "private");
                                } else if (inputMap[y - 1].charAt(x) == 'P') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "public");
                                } else if (inputMap[y - 1].charAt(x) == 'C') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "construction");
                                }
                            }
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    }
                } else {
                    break;
                }
            }
        }
        return inputGraph;
    }
    
    public Graph getGraph() {
        return graph;
    }

    public int getStartingNode() {
        return start;
    }

    public int getDestinationNode() {
        return end;
    }

    public int maxPrivateRoads() {
        return privateRoads;
    }

    public int maxConstructionRoads() {
        return constRoads;
    }
    
    public static void main(String[] args) {
        try{
            MyMap map = new MyMap("map0");
            Graph gr = map.getGraph();
            Iterator<Edge> iter = gr.incidentEdges(gr.getNode(6));
            while (iter.hasNext()) {
                Edge e = iter.next();
                System.out.println(e.firstNode().getId() + " " +e.secondNode().getId() + "THESE TWO NODES ARE CONNECTED");
            }
        }
        catch (Exception e) {
            
        }
    }

}