package ibm.com.map.hashmap;

import java.util.Iterator;
import java.util.TreeMap;

public class TreeMapDemo1 {
	public static void main(String[] args){
        //自然默认排序
        TreeMap<Integer, String> pairs = new TreeMap<>();
        pairs.put(2,  "B");
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
