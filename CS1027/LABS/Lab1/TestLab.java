public class TestLab {
    public static void main(String[] args) {
        Player p1 = new Player("Arsalaan", "Center", 99);
        System.out.println(p1.getName());
        System.out.println(p1.getPosition());
        System.out.println(p1.getJerseyNum());
        p1.setJerseyNum(10);
        p1.setName("Jack");
        p1.setPosition("Defence");
        System.out.println(p1.getName());
        System.out.println(p1.getPosition());
        System.out.println(p1.getJerseyNum());
        System.out.println(p1);
        Player p2 = new Player("Jack", "Defence", 10);
        if (p1.equals(p2)) {
            System.out.println("Same Player");
        }
        else {
            System.out.println("Different Player");
        }
    }
}