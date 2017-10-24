import java.io.*;
import java.util.*;
import java.math.*;
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
    }
}
public static class edge implements Comparable<edge>{
	public int u,v,w;
	public int compareTo(edge e){
		return w-e.w;
	}
}
public static class cmp implements Comparator<edge>{
	public int compare(edge a,edge b){
		if(a.w<b.w)return 1;
		if(a.w>b.w)return -1;
		return 0;
	}
}
class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;
    
    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }
    
    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }
    
    public int nextInt() {
        return Integer.parseInt(next());
    }
    
    public long nextLong() {
        return Long.parseLong(next());
    }
}
