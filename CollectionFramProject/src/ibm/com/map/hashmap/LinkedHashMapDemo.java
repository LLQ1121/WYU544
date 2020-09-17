package ibm.com.map.hashmap;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

public class LinkedHashMapDemo {
	public static void main(String []args) {
	LinkedHashMap<String, String> map = new LinkedHashMap<>();
	map.put("ABC001", "Kevin");
	map.put("ABC003", "Lily");
	map.put("ABC002", "Bob");
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