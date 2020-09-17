package ibm.com.map.hashmap;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class GetKeyMethodHashMapDemo {
public static void main(String []args) {	
	HashMap<String, String> map = new HashMap<>();
	map.put("ABC001", "Kevin");
	map.put("ABC002", "Lily");
	map.put("ABC003", "Bob");
	map.put("ABC004", "Zombie");

	//Set<K> keySet()
	Set<String> keys = map.keySet();
	System.out.println("Hashmap»ñÈ¡¼ükey:");
	for(String key: keys) {
		System.out.println(key);
	}
	
	}
}
