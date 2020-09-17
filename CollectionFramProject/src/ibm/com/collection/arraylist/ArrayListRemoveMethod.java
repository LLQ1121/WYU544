package ibm.com.collection.arraylist;

import java.util.ArrayList;
import java.util.List;

public class ArrayListRemoveMethod {
	public static void main(String[] args) {
		ArrayList<String> list = new ArrayList<>();
        createDefaultList(list); // list : 0 1 2 3
        print("list", list);
        list.remove(2); // list : 0 1 3
        print("list", list);
        list.add(2, "2");
        print("list", list);
        list.remove("2");
        print("list", list);
 
        ArrayList<String> newList = new ArrayList<>();
        newList.add("0");
        newList.add("1");
        print("old list", list);
        print("new list", newList);
        list.removeAll(newList);
        print("list", list);
 
    }
 
	private static void print(String flag, List list) {
        System.out.print(flag + ":");
        list.forEach(System.out::print);
        System.out.println();
	}
	
    private static void createDefaultList(ArrayList<String> list) {
        list.add("0");
        list.add("1");
        list.add("2");
        list.add("3");
	}
}
