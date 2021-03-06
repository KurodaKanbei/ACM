import java.math.BigInteger;  
import java.util.Scanner;  
public class Main {  
    public static BigInteger p, q;  
    public static void solve(int n) {  
        BigInteger N, p1, p2, q1, q2, a0, a1, a2, g1, g2, h1, h2;  
        g1 = q2 = p1 = BigInteger.ZERO;  
        h1 = q1 = p2 = BigInteger.ONE;  
        a0 = a1 = BigInteger.valueOf((long)Math.sqrt(1.0*n));  
        N = BigInteger.valueOf(n);  
        while (true) {  
            g2 = a1.multiply(h1).subtract(g1);        
            h2 = N.subtract(g2.pow(2)).divide(h1); 
            a2 = g2.add(a0).divide(h2);
            p = a1.multiply(p2).add(p1); 
            q = a1.multiply(q2).add(q1);
            if (p.pow(2).subtract(N.multiply(q.pow(2)))
				.compareTo(BigInteger.ONE) == 0) return;
			g1 = g2;h1 = h2;a1 = a2;  
            p1 = p2;p2 = p;  
            q1 = q2;q2 = q;  
        }  
    }  
    public static void main(String[] args) {  
        Scanner cin = new Scanner(System.in);  
        int t=cin.nextInt();  
        while (t--!=0) {  
            solve(cin.nextInt());  
            System.out.println(p + " " + q);  
        }  
    }  
}
