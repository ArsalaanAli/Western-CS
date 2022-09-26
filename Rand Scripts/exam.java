public class exam {
    public static void main(String[] args) {
        System.out.println(doWork(32));
    }
    public static int doWork (int x) {
        if (x <= 1) {
            return 1;
        }
        return 1 + doWork(x / 2);
    }
}
