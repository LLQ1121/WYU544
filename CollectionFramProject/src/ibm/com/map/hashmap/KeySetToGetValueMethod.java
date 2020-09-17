package ibm.com.map.hashmap;

import java.util.HashMap;
import java.util.Set;

public class KeySetToGetValueMethod {
public static void main(String []args) {
		HashMap<String, String> map = new HashMap<>();
		map.put("ABC001", "Kevin");
		map.put("ABC002", "Lily");
		map.put("ABC003", "Bob");
		map.put("ABC004", "Zombie");

		//获取所有key
		Set<String> keys = map.keySet(); 
		for(String key: keys) {
		     //通过Key来找Value
			String value = map.get(key); 
			System.out.println("ID:"+key+"--Name: "+value);
		}
	}
}
