package ibm.com.collection;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class IteratorDemo {
	public static void main(String[]args){
        Collection collection = new ArrayList();
        collection.add("aaa");
        collection.add("bbb");
        collection.add("ccc");
        collection.add("ddd");

        //使用了Collection中的iterator()方法。调用 集合中的迭代器，是为了获取集合中的迭代器对象

        //用法一
        Iterator iterator = collection.iterator();
        System.out.println("测试Iterator遍历Collection的元素方法一");
        while (iterator.hasNext()){
    	   
           System.out.println("测试Iterator遍历Collection的元素："+iterator.next());
           
        }

       System.out.println("测试Iterator遍历Collection的元素方法二");
        //用法二
        for (Iterator iterator1 = collection.iterator();iterator1.hasNext();){
            System.out.println("测试Iterator遍历Collection的元素："+iterator1.next());
        }
    }

}
