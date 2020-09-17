package ibm.com.collection.set;

import java.util.Comparator;
import java.util.TreeSet;

public class ComparatorTreeSetDemo {
	/**
	 * TreeSet集合是用来对象元素进行排序的，同样他也可以保证元素唯一 当CompareTo方法返回0的时候集合中只有一个元素
	 * 当CompareTo方法返回正数的时候集合会怎么存就怎么取 当CompateTo方法返回负数的时候集合会倒序存储
	 */
	public static void main(String[] args) {
		TreeSet<String> ts = new TreeSet<>(new CompareByLen());
		ts.add("张三");
		ts.add("李四");
		ts.add("王五");
		ts.add("麻溜");
		ts.add("李四");// 加 重复的李四
		System.out.println(ts);
	}
}

class CompareByLen implements Comparator<String> {
	@Override
	public int compare(String s1, String s2) {
		System.out.println(s1 + " :" + s2);
		int num = s1.length() - s2.length();
		return num == 0 ? s1.compareTo(s2) : num;
	}
}
//class CompareByLen implements Comparator<String> {
//	@Override
//	public int compare(String s1, String s2) {
//		System.out.println(s1 + " :" + s2);
//		int num = s1.length() - s2.length();
//		return num == 0 ? s1.compareTo(s2) : num;
//	}
//}
