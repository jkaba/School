import java.util.LinkedList;

public class test {
	public static int hashFunction(String key, LinkedList[] M, int a){
		int v = (int)key.length()-1;
		for(int i = key.length()-2; i > 0; i--){
			v = ((v*a) + (int)key.charAt(i)) % M.length;
		}
		return v;
	}
	
	public static void main(String[] args) throws Exception{
		LinkedList<DictEntry>[] M = new LinkedList[4096];
		String s = "DELETED";
		String y = "String";
		System.out.println(hashFunction(s, M, 7));
		System.out.println(hashFunction(y, M, 7));
	}
}
