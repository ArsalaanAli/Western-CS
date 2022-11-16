public class Pel {
    private Location loc;
    private int col;

    public Pel(Location p, int color) {
        loc = p;
        col = color;
    }
    
    public Location getLocation() {
        return loc;
    }

    public int getCol() {
        return col;
    }

}
