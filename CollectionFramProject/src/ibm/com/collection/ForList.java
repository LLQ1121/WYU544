package ibm.com.collection;

import java.util.ArrayList;
import java.util.List;

public class ForList {
	public static void main(String[] args) {
		//定义集合
		List list=new ArrayList<>();
		//往集合中添加数据
		list.add("aa");
		list.add("bb");
		list.add("cc");
		System.out.println("List集合的for循环测试：");
		//for循环
		for(int i=0;i<list.size();i++) {
			System.out.println(list.get(i));
		}
	}
}
