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
    public DLStack path(){

    }

    public Map getMap(){
        return pyramidMap;
    }
    
    public boolean isDim(Chamber currentChamber){
        if(currentChamber == null || currentChamber.isSealed() || currentChamber.isLighted()){
            return false;
        }
        for(int i = 0; i<6; i++){
            if(currentChamber.getNeighbour(i) != null && currentChamber.getNeighbour(i).isLighted()){
                return true;
            }
        }
        return false;
    }
}
