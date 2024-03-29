import java.util.*;

public class asn1_b {
    public static void main(String[] args) {
        for (int i = 0; i <= 25; i++) {
            System.out.println(FastLucas(i * 20));
        }
    }
    public static BigInteger FastLucas(int n) {
        BigInteger[] memo = new BigInteger[n+2];
        memo[0] = new BigInteger("2");
        memo[1] = new BigInteger("1");
        return FastLucasHelper(n, memo);
    }

    private static BigInteger FastLucasHelper(int n, BigInteger[] memo) {
        if (memo[n] != null) {
            return memo[n];
        }
        BigInteger res = FastLucasHelper(n - 1, memo).add(FastLucasHelper(n - 2, memo));
        memo[n] = res;
        return res;        
    }
}

class BigInteger {
    private List<Integer> digits;

    public BigInteger(String number) {
        digits = new ArrayList<>();
        for (int i = number.length() - 1; i >= 0; i--) {
            digits.add(Character.getNumericValue(number.charAt(i)));
        }
    }
    public BigInteger() {
        digits = new ArrayList<>();
    }

    public BigInteger add(BigInteger other) {
        BigInteger result = new BigInteger();
        int size = Math.max(digits.size(), other.digits.size());
        int carry = 0;
        for (int i = 0; i < size; i++) {
            int first = 0;
            int second = 0;
            if (i < digits.size()) {
                first = digits.get(i);
            }
            if (i < other.digits.size()) {
                second = other.digits.get(i);
            }
            int sum = first + second + carry;
            int remainder = sum % 10;
            carry = sum >= 10 ? 1 : 0;
            result.digits.add(remainder);

        }
        if (carry == 1) {
            result.digits.add(1);
        }
        return result;
    }

    @Override
    public String toString(){
        String result = "";
        for(int i = digits.size()-1; i>=0; i--){
            result+=digits.get(i);
        }
        return result;
    }
}