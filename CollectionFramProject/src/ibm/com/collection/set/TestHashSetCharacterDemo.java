package ibm.com.collection.set;

import java.util.HashSet;

public class TestHashSetCharacterDemo {
	public static void main(String []args) {
		HashSet<Integer> hs = new HashSet<>();
		hs.add(5);
		hs.add(2);
		hs.add(3);
		System.out.println("测试set特点之前打印----"+hs);
		System.out.println(hs.add(4));
		System.out.println(hs.add(4));  //检验HashSet是否允许重复元素加入
		System.out.println(hs);    //检验HashSet是否有序
			
	}
}

