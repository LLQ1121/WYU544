package ibm.com.collection.arraylist;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MoreThreadArrayList {
	public static void main(String[] args) {
		List <String> list = new ArrayList<String>();
		List <String> synchronizedList = Collections.synchronizedList(list);
		synchronizedList.add("aaa");
		synchronizedList.add("bbb");

		for (int i = 0; i < synchronizedList.size(); i++) {
		    System.out.println(synchronizedList.get(i));
		}
	
    }
}
