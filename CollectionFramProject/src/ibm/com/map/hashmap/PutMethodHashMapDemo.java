package ibm.com.map.hashmap;

import java.util.HashMap;

public class PutMethodHashMapDemo {
public static void main(String []args) {	
		HashMap<String, String> map = new HashMap<>();
		map.put("ABC001", "Kevin");
		map.put("ABC002", "Lily");
		System.out.println("键不重复时候---"+map);
		System.out.println(map.put("ABC001", "Clack"));  //此处Key与第一个重复！！
		System.out.println("键重复时候---"+map);		
	}
}
