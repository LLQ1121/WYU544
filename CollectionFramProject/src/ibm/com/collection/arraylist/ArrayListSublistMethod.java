package ibm.com.collection.arraylist;

import java.util.ArrayList;
import java.util.List;

public class ArrayListSublistMethod {
	public static void main(String[] args) {	
		//修改sublist 会影响原来的list
        ArrayList<String> l1 = new ArrayList<>();
        l1.add("a");
        l1.add("b");
        l1.add("c");
        System.out.println("l1.subList之前的l1----"+l1);
        List<String> l2 = l1.subList(1, 2);
        System.out.println("l2.add之前----"+l2);
        System.out.println("l1.subList之后的l1----"+l1);
        l2.add("new");
        System.out.println("l2.add的l1之后----"+l1);
        System.out.println("l2.add之后----"+l2);
    }
}
