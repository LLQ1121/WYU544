package ibm.com.collection;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class IteratorList {
	public static void main(String[] args) {
		//定义集合
		List list=new ArrayList<>();
		//往集合中添加数据
		list.add("aa");
		list.add("bb");
		list.add("cc");
		System.out.println("List集合的迭代器遍历测试：");
		//迭代器输出显示
		Iterator it = list.iterator();
		while(it.hasNext()) {
			System.out.println(it.next());
		}
		
	}
}
