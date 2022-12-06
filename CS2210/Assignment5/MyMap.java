import java.io.File;  // Import the File class
import java.util.Scanner; // Import the Scanner class to read text files

public class MyMap {
    private int start, end, width, length, privateRoads, constRoads;

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
            
            
            input.close();
        } catch (Exception e) {
            throw new MapException("input file does not exist");
        }
    }
    
    public static void main(String[] args) {
        try{
            MyMap map = new MyMap("map5");
        }
        catch (Exception e) {
            
        }
    }

}