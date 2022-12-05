public class Pel {//Pel obejct
    private Location loc;
    private int col;//holds a location and a color

    public Pel(Location p, int color) {//initializes the location and color
        loc = p;
        col = color;
    }
    
    public Location getLocus() {//returns the location
        return loc;
    }

    public int getColor() {//returns the color
        return col;
    }

}
