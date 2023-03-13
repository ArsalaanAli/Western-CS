import java.io.File;// Import the File class
import java.util.Scanner;// Import the Scanner class to read text files
import java.util.Iterator;
import java.util.ArrayList;//import iterator and arraylist to use interators

public class MyMap {
    private int start, end, width, length, privateRoads, constRoads;//private field variables
    private Graph graph;//private field variable to hold the graph

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
            this.constRoads = Integer.parseInt(input.nextLine());//read all input and set the integers to field variables
            String[] inputMap = new String[(length * 2) - 1];
            for (int i = 0; i < inputMap.length; i++) {
                inputMap[i] = input.nextLine();//inputting the map into an array of strings.
            }
            this.graph = buildGraph(inputMap);//use helper function to build the graph
            input.close();//close the input stream
        } catch (Exception e) {
            throw new MapException("input file does not exist");//throw exception if file doesn't exist
        }
    }
    
    private Graph buildGraph(String[] inputMap) {//private helper function to build the graph from input
        Graph inputGraph = new Graph(width * length);//initializing graph
        int nodeNum = -1;//variable to keep track of the current node id
        for (int y = 0; y < inputMap.length; y++) {
            for (int x = 0; x < inputMap[y].length(); x++) {//looping throw every index in the array
                if (y % 2 == 0) {
                    if (inputMap[y].charAt(x) == '+') {//if a node is found
                        nodeNum++;//increase nodeNum to keep track of the current node id
                        try {
                            Node curNode = inputGraph.getNode(nodeNum);//get the current node grom the graph
                            if (x - 1 > 0) {//if there is a road to the left of the current node
                                if (inputMap[y].charAt(x - 1) == 'V') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "private");
                                } else if (inputMap[y].charAt(x - 1) == 'P') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "public");
                                } else if (inputMap[y].charAt(x - 1) == 'C') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - 1), "construction");//add an edge for this road with the type of road
                                }
                            }
                            if (y - 1 > 0) {//if there is a road on top of the current node
                                if (inputMap[y - 1].charAt(x) == 'V') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "private");
                                } else if (inputMap[y - 1].charAt(x) == 'P') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "public");
                                } else if (inputMap[y - 1].charAt(x) == 'C') {
                                    inputGraph.addEdge(curNode, inputGraph.getNode(nodeNum - width), "construction");//add an edge for this road with the type of road
                                }
                            }
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    }
                } else {
                    break;//if there are no nodes in the current line, skip this line
                }
            }
        }
        return inputGraph;//return the completed graph
    }
    
    public Graph getGraph() {
        return graph;//return the graph stored in this map
    }

    public int getStartingNode() {
        return start;//get the starting node of this map
    }

    public int getDestinationNode() {
        return end;//get the destination node of this map
    }

    public int maxPrivateRoads() {
        return privateRoads;//return the maximum amount of private roads allowed in the path
    }

    public int maxConstructionRoads() {
        return constRoads;//return the maximum amount of construction roads allowed in the path
    }

    public Iterator findPath(int start, int destination, int maxPrivate, int maxConstruction) {//returns a path from the start to the destination given constraints
        try{
            Node startNode = getGraph().getNode(start);
            Node endNode = getGraph().getNode(destination);//getting the start and destination nodes from the graph
            ArrayList<Node> nodeList =  new ArrayList<Node>();//an arraylist to hold the path from the start to the destination
            nodeList.add(startNode);//adding the start node to the path list
            ArrayList<Node> path = pathFinding(startNode, endNode, maxPrivate, maxConstruction, 0, 0, nodeList);
            return path == null ? null : path.iterator();//using helper function to recursively find path
        }
        catch (Exception e) {
            System.out.println(e);
        }
        return null;
    }
    
    private ArrayList<Node> pathFinding(Node cur, Node dest, int maxPrivate, int maxConstruction, int curPrivate,
            int curConstruction, ArrayList<Node> curNodes) {//helper function to recursively find path
        if (curPrivate > maxPrivate || curConstruction > maxConstruction) {//if either of the constraints have been violated, return null becuase this path is not valid
            return null;
        }
        if (cur == dest) {
            return curNodes;//if the path to the destination has been found return the array holding the path
        }
        cur.markNode(true);//mark the current node as visited so it is not revisited
        try{
            Iterator<Edge> iter = graph.incidentEdges(cur);//getting all of the adjacent edges to the current node
            while (iter.hasNext()){
                Edge curEdge = iter.next();//looping through each edge
                
                Node nextNode = curEdge.secondNode();//getting the node this node is attached to
                if (nextNode.getMark()) {
                    continue;//if the other node has already been visited, then we continue to the next node
                }
                ArrayList<Node> clone = (ArrayList<Node>) curNodes.clone();//cloning the array list so that the original list is not affected by this recursive branch
                clone.add(nextNode);//adding the other node to the cloned arraylist
                ArrayList<Node> ans;//an arraylist to hold the solved path if it is found
                if(curEdge.getType() == "private"){
                    ans = pathFinding(nextNode, dest, maxPrivate, maxConstruction, curPrivate+1, curConstruction, clone);
                }
                else if(curEdge.getType() == "construction"){
                    ans =  pathFinding(nextNode, dest, maxPrivate, maxConstruction, curPrivate, curConstruction+1, clone);
                }
                else{
                    ans =  pathFinding(nextNode, dest, maxPrivate, maxConstruction, curPrivate, curConstruction, clone);//calling pathFinding starting at the other node, if the edge is private or construction then 1 is added to the parameter for the respective edge constraint
                }
                if(ans != null){
                    return ans;//if a valid path was found, the path is returned
                }
            }
        }
        catch (Exception e) {
            System.out.println(e);
        }
        cur.markNode(false);//if a valid path is not found, then the current node is marked as unvisited and we return back to the previous node in the stack by returning null
        return null;
    }
}