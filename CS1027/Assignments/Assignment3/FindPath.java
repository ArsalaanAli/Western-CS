public class FindPath {
    Map pyramidMap;//instance variable

    public FindPath(String fileName){//constructor takes in filename for map
        try{
            this.pyramidMap = new Map(fileName);//initializing instance variable
        }
        catch(Exception e){
            System.out.println(e);//if an error is thrown it is printed out
        }
    }

    public DLStack path() {//functions that returns a stakc with a path to each treasure chamber
        DLStack<Chamber> path = new DLStack<Chamber>();//empty stack 
        int numTreasures = pyramidMap.getNumTreasures(), treasuresFound = 0;//integer counter for the amount of treasures found variable for the amount of existing treasures
        path.push(pyramidMap.getEntrance());//pushing the entrance chamber to the stack
        pyramidMap.getEntrance().markPushed();//marking the entrance as pushed
        while (!path.isEmpty()) {//loop that runs until the stack is empty
            Chamber currentChamber = path.peek();//getting the chamber at the top of the array
            if (currentChamber.isTreasure()) {//if the chamber is a traesure chamber, then the count of treasures found is increased
                treasuresFound++;
            }
            if (treasuresFound == numTreasures) {//if all of the treasures have been found, then the loop is broken
                break;
            }
            Chamber bestChamber = bestChamber(currentChamber);//using the best chamber function to find which chamber to move to next 
            if (bestChamber != null) {//if there is a chamber to move to
                path.push(bestChamber);//that chamber is added to the stack
                bestChamber.markPushed();//the chamber is also marked as pushed
            }
            else {//if there isnt a chamber to move to
                Chamber popChamber = path.pop();//the chamber at the top of the stack is popped
                popChamber.markPopped();//the chamber that was just popped is marked as popped
            }
        }

        return path;//after the path has been constructed it is returned
    }

    public Map getMap(){
        return pyramidMap;//returns the pyramidMap instance variable
    }
    
    public boolean isDim(Chamber currentChamber) {//checks if a chamber is dim
        if (currentChamber == null || currentChamber.isSealed() || currentChamber.isLighted()) {//if the chamber is null, sealed, or lighted it cant be dim
            return false;
        }
        for (int i = 0; i < 6; i++) {//otherwise if the chamber has any lighted neighbors then it is dim
            if (currentChamber.getNeighbour(i) != null && currentChamber.getNeighbour(i).isLighted()) {
                return true;//returning true if any of its neighbors is lighted
            }
        }
        return false;
    }
    
    public Chamber bestChamber(Chamber currentChamber) {//returns the best chamber to move to given a current chamber
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor != null && neighbor.isTreasure() && !neighbor.isMarked()) {//if any unmarked treasure exists in the neighbor chambers, then that chamber is returned
                return neighbor;
            }
        }
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor != null && neighbor.isLighted() && !neighbor.isMarked()) {//otherwise if any marked lighted chambers exists, then that chamber is returned
                return neighbor;
            }
        }
        for (int i = 0; i < 6; i++) {
            Chamber neighbor = currentChamber.getNeighbour(i);
            if (neighbor != null && isDim(neighbor) && !neighbor.isMarked()) {//other if any unmarked dim neighbor exists, then that chamber is returned
                return neighbor;
            }
        }
        return null;//otherwise there is no chamber that can be moved to
    }
}
