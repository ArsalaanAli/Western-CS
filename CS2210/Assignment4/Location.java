public class Location {//location object
    private int x, y;//field vairables to hold the coordinates

    public Location(int x, int y){
        this.x = x;
        this.y = y;//initialize coordinates
    }

    public int getx() {//getter functions for coordinates
        return x;
    }

    public int gety() {
        return y;
    }

    public int compareTo(Location p) {//compare function that compares two locations as bigger, smaller, or equal
        if(this.gety() > p.gety() || (this.gety() == p.gety() && this.getx() > p.getx())){
            return 1;
        } 
        else if(this.getx() == p.getx() && this.gety() == p.gety()) {
            return 0;
        }
        else{
            return -1;
        }
    }
}