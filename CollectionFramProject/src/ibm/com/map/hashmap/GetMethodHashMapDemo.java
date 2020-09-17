package ibm.com.map.hashmap;

import java.util.Collection;
import java.util.HashMap;

public class GetMethodHashMapDemo {
public static void main(String []args) {	
	HashMap<String, String> map = new HashMap<>();
	map.put("ABC001", "Kevin");
	map.put("ABC002", "Lily");
	map.put("ABC003", "Bob");
	map.put("ABC004", "Zombie");
	System.out.println("HashMap的get()方法获取值---"+map.get("ABC003"));
	Collection<String> values=map.values();
	for(String value: values) {
		System.out.println("HashMap的values()获取值---"+value);
	}
	
	}
}
