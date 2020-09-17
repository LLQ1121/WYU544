package ibm.com.map.hashmap;

import java.util.Collections;
import java.util.Iterator;
import java.util.TreeMap;

public class TreeMapDemo2 {
	public static void main(String[] args){
        //Comparator排序
		//Sort keys in reverse order
        TreeMap<Integer, String> pairs = new TreeMap<>(Collections.reverseOrder());//reverseOrder看源码
        pairs.put(2,  "B" );
        pairs.put(1,  "A");
        pairs.put(3,  "C");
        //迭代输出
        Iterator<Integer> iterator =  pairs.keySet().iterator();
        while(iterator.hasNext()) {
            Integer key = iterator.next();
            System.out.println("Key: " + key + ", Value: " + pairs.get(key));
        }
	}
}
