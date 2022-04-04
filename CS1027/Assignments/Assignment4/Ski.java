public class Ski {
    private BinaryTreeNode<SkiSegment> root;//instance vairable that holds the root node of the binary tree

    public Ski(String[] data) {//constructor method takes in a set of data to make ski segments out of
        SkiSegment[] segments = new SkiSegment[data.length];//a list of ski segments the size of data
        
        for (int i = 0; i < data.length; i++) {//adding all the data elements as segments to the segments list
            if (data[i] == null) {
                segments[i] = null;//if the data is null, then the segment is going to be null too
            }
            else if (data[i].contains("jump")) {
                segments[i] = new JumpSegment(String.valueOf(i), data[i]);//adding jump segments if the data has "jump" in it
            } else if (data[i].contains("slalom")) {
                segments[i] = new SlalomSegment(String.valueOf(i), data[i]);//adding slalom segments if the data has "slalom" in it
            } else {
                segments[i] = new SkiSegment(String.valueOf(i), data[i]);//adding regular segments if the data has nothing else in it
            }
        }
        TreeBuilder<SkiSegment> tree = new TreeBuilder<SkiSegment>();//creating a treebuilder class so the buildTree method can be used
        root = tree.buildTree(segments).getRoot();//creating a tree using the buildTree method and using the segments array as the data for the tree, setting the root fo the tree to the instance variable root
    }

    public BinaryTreeNode<SkiSegment> getRoot() {//public getter method for the root
        return root;//returns the root
    }

    public void skiNextSegment(BinaryTreeNode<SkiSegment> node, ArrayUnorderedList<SkiSegment> sequence) {//public method to find the best path down the ski slope using the segments array
        sequence.addToRear(node.getData());//adding segment node to the path of the ski slope
        if (node.getLeft() == null && node.getRight() == null) {//BASE CASE: if the node doesnt have any children, then the recursive fucntion is exited
            return;
        }
        skiNextSegment(bestNextNode(node), sequence);//calling this function inside itself, creating a recursive loop that will go down the best path of the ski slope until it hits a node with no children.
    }

    private BinaryTreeNode<SkiSegment> bestNextNode(BinaryTreeNode<SkiSegment> node) {//a function to find the next best node given a segment node in the ski slope.
        //since the case with both children being null has already been checked, if either node is null, then the other one is not, meaing that theother node is returned.
        if (node.getLeft() == null) {
            return node.getRight();
        }
        if (node.getRight() == null) {
            return node.getLeft();
        }

        SkiSegment right = node.getRight().getData();
        SkiSegment left = node.getLeft().getData();//vairbales to hold the segments in each node
        
        if (right instanceof JumpSegment && left instanceof JumpSegment) {//if both children are JumpSegments
            JumpSegment rightJump = (JumpSegment) right;//casting the children as JumpSegments
            JumpSegment leftJump = (JumpSegment) left;
            if (rightJump.getHeight() >= leftJump.getHeight()) {
                return node.getRight();//if the right side is higher or both sides are the same, the right node is returned
            } else {
                return node.getLeft();//otherwise the left node is returned
            }
        }

        //if bother children arent jump segments, but one of them is, the that node is returned
        if (right instanceof JumpSegment) {
            return node.getRight();
        }
        if (left instanceof JumpSegment) {
            return node.getLeft();
        }

        if (left instanceof SlalomSegment && right instanceof SlalomSegment) {//if both nodes are slalom segments
            SlalomSegment leftSlalom = (SlalomSegment) left;//casing the left node as a slalom segment
            if (leftSlalom.getDirection().equals("L")) {
                return node.getLeft();//if the left side is leeward then it is returned
            } else {
                return node.getRight();//otherwise the right side is returned
            }
        }

        if (left instanceof SlalomSegment || right instanceof SlalomSegment) {//if only one node is slalom segment
            if (left instanceof SlalomSegment) {//if the left side is slalom segment
                SlalomSegment leftSlalom = (SlalomSegment) left;
                if (leftSlalom.getDirection().equals("L")) {//if the left side is also leeward then it is returned
                    return node.getLeft();
                } else {
                    return node.getRight();//if it is windward then the other is returned
                }
            } else {
                SlalomSegment rightSlalom = (SlalomSegment) right;//same logic but if the right side is the slalom
                if (rightSlalom.getDirection().equals("L")) {
                    return node.getRight();
                } else {
                    return node.getLeft();
                }
            }
        }
        return node.getRight();//if both sides are regular segments, then choose the right side
    }
}
