package ibm.com.map.hashmap;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class EntrySetToGetValueMethod {
public static void main(String []args) {
	HashMap<String, String> map = new HashMap<>();
	map.put("ABC001", "Kevin");
	map.put("ABC002", "Lily");
	map.put("ABC003", "Bob");
	map.put("ABC004", "Zombie");
	//获取所有中间人entrys
	Set<Map.Entry<String, String>> entrys =map.entrySet();
	//遍历所有entrys用Map.Entry<String, String>类型的entry接收
	for(Map.Entry<String, String> entry:entrys) {
		String key = entry.getKey();
		String value = entry.getValue();
		System.out.println("ID:"+key+"--Name: "+value);
	}
	}
}
