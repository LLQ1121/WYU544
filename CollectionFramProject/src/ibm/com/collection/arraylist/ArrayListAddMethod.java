package ibm.com.collection.arraylist;

import java.util.ArrayList;
import java.util.List;

public class ArrayListAddMethod {
	public static void main(String[] args) {
		ArrayList list = new ArrayList();
        list.add(0);
        list.add(1);
        list.add(2);
        list.add(3); // 此时list : 0 1 2 3
        print("list", list);
        list.add(0, 4); //  在指定位置插入元素
        print("list", list); //  此时list ；4 0 1 2 3
        List newList = list.subList(2, 4); //截取list ，不包含最后一位
        print("newList", newList); //  此时 newList ： 1 2
        list.addAll(2, newList); //新增list，新的list元素默认排在原来元素的后面 ,此时newList 不能再使用了
        print("list", list); // 此时，list : 4 0 1 2 1 2 3
        System.out.println("list size " + list.size());
        list.set(0, 1); //在指定位置替换元素
        print("list", list); // 此时 list : 1 0 1 2 1 2 3
        System.out.println(list.indexOf(1));
        System.out.println(list.lastIndexOf(1));
        System.out.println(list.isEmpty());
 
    }
 
    private static void print(String flag, List list) {
        System.out.print(flag + ":");
        list.forEach(System.out::print);
        System.out.println();

	}
}
