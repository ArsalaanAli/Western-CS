public class FindPath {
    Map pyramidMap;

    public FindPath(String fileName){
        try{
            this.pyramidMap = new Map(fileName);
        }
        catch(Exception e){
            System.out.println(e);
        }
    }

    public DLStack path() {
        DLStack<Chamber> path = new DLStack<Chamber>();
        int numTreasures = pyramidMap.getNumTreasures(), treasuresFound = 0;
        path.push(pyramidMap.getEntrance());
        pyramidMap.getEntrance().markPushed();
        while (!path.isEmpty()) {
            Chamber currentChamber = path.peek();
            if (currentChamber.isTreasure()) {
                treasuresFound++;
            }
            if (treasuresFound == numTreasures) {
                break;
            }
            Chamber bestChamber = bestChamber(currentChamber);
            if (bestChamber != null) {
                path.push(bestChamber);
                bestChamber.markPushed();
            }
            else {
                Chamber popChamber = path.pop();
                popChamber.markPopped();
            }
        }

        return path;
    }

    public Map getMap(){
        return pyramidMap;
    }
    
    public boolean isDim(Chamber currentChamber) {
        if (currentChamber == null || currentChamber.isSealed() || currentChamber.isLighted()) {
            return false;
        }
        for (int i = 0; i < 6; i++) {
            if (currentChamber.getNeighbour(i) != null && currentChamber.getNeighbour(i).isLighted()) {
                return true;
            }
        }
        return false;
    }
    
    public Chamber bestChamber(Chamber currentChamber) {
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor == null) {
                continue;
            }
            if (neighbor.isTreasure() && !neighbor.isMarked()) {
                return neighbor;
            }
        }
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor == null) {
                continue;
            }
            if (neighbor.isLighted() && !neighbor.isMarked()) {
                return neighbor;
            }
        }
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor == null) {
                continue;
            }
            if (isDim(neighbor) && !neighbor.isMarked()) {
                return neighbor;
            }
        }
        return null;
    }
}
