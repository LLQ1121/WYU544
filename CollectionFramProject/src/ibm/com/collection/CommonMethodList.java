package ibm.com.collection;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class CommonMethodList {
	public static void main(String[] args)
	{
	    List<String> L = new ArrayList<>();
	    //末尾添加元素
	    L.add("abc");
	    L.add("bcd");
	    L.add("cde");
	    //由于List集合是有索引的，还可以使用索引进行迭代
	    for(int i = 0;i < L.size();i++)
	    {
	        System.out.println(L.get(i));
	    }
	    System.out.println("以上数据是list添加之前---------------------");
	    //指定位置添加元素
	    L.add(1,"fgh");
	    for(int i = 0;i < L.size();i++)
	    {
	        System.out.println(L.get(i));
	    }
	    System.out.println("list添加之后---------------------");
	    //删除指定元素
	    L.remove("abc");
	    for(int i = 0;i < L.size();i++)
	    {
	        System.out.println(L.get(i));
	    }
	    System.out.println("list删除abc之后---------------------");
	    //删除指定索引元素
	    L.remove(1);
	    for(int i = 0;i < L.size();i++)
	    {
	        System.out.println(L.get(i));
	    }
	    System.out.println("list中remove(1)之后---------------------");
	    //将指定索引处的元素替换成指定元素
	    L.set(1,"hello");
	    //获取指定索引处的元素
	    L.get(1);
	    //使用迭代器获取出集合中的元素,最好使用listIterator进行迭代
	    Iterator<String> it = L.listIterator();
	    while(it.hasNext())
	    {
	        System.out.println(it.next());
	    }
	    System.out.println("list中L.get()之后---------------------");
	    //由于List集合是有索引的，还可以使用索引进行迭代
	    for(int i = 0;i < L.size();i++)
	    {
	        System.out.println(L.get(i));
	    }
	}
}
