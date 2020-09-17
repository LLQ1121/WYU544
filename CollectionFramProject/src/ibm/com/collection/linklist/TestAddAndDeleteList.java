package ibm.com.collection.linklist;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

//ArrayList 、LinkedList插入删除操作耗时对比
public class TestAddAndDeleteList {
	static final int N = 50000;

	static long timeList(List list) {
		long start = System.currentTimeMillis();
		Object o = new Object();
		for (int i = 0; i < N; i++)
			list.add(0, o);
		return System.currentTimeMillis() - start;
	}

	public static void main(String[] args) {
		System.out.println("ArrayList耗时：" + timeList(new ArrayList()) + " ms");
		System.out.println("LinkedList耗时：" + timeList(new LinkedList()) + " ms");
	}
}
