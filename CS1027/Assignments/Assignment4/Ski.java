public class Ski {
    private BinaryTreeNode<SkiSegment> root;

    public Ski(String[] data) {
        SkiSegment[] segments = new SkiSegment[data.length];
        for (int i = 0; i < data.length; i++) {
            if (data[i] == null) {
                segments[i] = null;
            }
            else if (data[i].contains("jump")) {
                segments[i] = new JumpSegment(String.valueOf(i), data[i]);
            } else if (data[i].contains("slalom")) {
                segments[i] = new SlalomSegment(String.valueOf(i), data[i]);
            } else {
                segments[i] = new SkiSegment(String.valueOf(i), data[i]);
            }
        }
        TreeBuilder<SkiSegment> tree = new TreeBuilder<SkiSegment>();
        root = tree.buildTree(segments).getRoot();
    }

    public BinaryTreeNode<SkiSegment> getRoot() {
        return root;
    }

    public void skiNextSegment(BinaryTreeNode<SkiSegment> node, ArrayUnorderedList<SkiSegment> sequence) {
        sequence.addToRear(node.getData());
        if (node.getLeft() == null && node.getRight() == null) {
            return;
        }
        skiNextSegment(bestNextNode(node), sequence);
    }

    private BinaryTreeNode<SkiSegment> bestNextNode(BinaryTreeNode<SkiSegment> node) {
        if (node.getLeft() == null) {
            return node.getRight();
        }
        if (node.getRight() == null) {
            return node.getLeft();
        }
        SkiSegment right = node.getRight().getData();
        SkiSegment left = node.getLeft().getData();
        if (right instanceof JumpSegment && left instanceof JumpSegment) {
            JumpSegment rightJump = (JumpSegment) right;
            JumpSegment leftJump = (JumpSegment) left;
            if (rightJump.getHeight() >= leftJump.getHeight()) {
                return node.getRight();
            } else {
                return node.getLeft();
            }
        }
        if (right instanceof JumpSegment) {
            return node.getRight();
        }
        if (left instanceof JumpSegment) {
            return node.getLeft();
        }
        if (left instanceof SlalomSegment && right instanceof SlalomSegment) {
            SlalomSegment leftSlalom = (SlalomSegment) left;
            if (leftSlalom.getDirection().equals("L")) {
                return node.getLeft();
            } else {
                return node.getRight();
            }
        }
        if (left instanceof SlalomSegment || right instanceof SlalomSegment) {
            if (left instanceof SlalomSegment) {
                SlalomSegment leftSlalom = (SlalomSegment) left;
                if (leftSlalom.getDirection().equals("L")) {
                    return node.getLeft();
                } else {
                    return node.getRight();
                }
            } else {
                SlalomSegment rightSlalom = (SlalomSegment) right;
                if (rightSlalom.getDirection().equals("L")) {
                    return node.getRight();
                } else {
                    return node.getLeft();
                }
            }
        }
        return node.getRight();
    }
}
