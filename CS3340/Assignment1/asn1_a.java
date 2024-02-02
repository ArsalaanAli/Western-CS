public class asn1_a {
    public static void main(String[] args) {
        for (int i = 0; i <= 10; i++) {
            System.out.println(RecursiveLucas(i * 5));
        }
    }

    public static long RecursiveLucas(int n) {
        if (n <= 1) {
            if (n == 1) {
                return 1;
            }
            return 2;
        }
        return RecursiveLucas(n - 1) + RecursiveLucas(n - 2);
    }
}
