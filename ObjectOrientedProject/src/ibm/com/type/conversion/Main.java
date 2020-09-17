package ibm.com.type.conversion;

public class Main {
	public static void main(String[] args) {
		// 向上转型
		// 调用的是 Cat 的 eat
		Animal a = new Cat();
		a.eat();
		// 向下转型
		// 调用的是 Cat 的 work
		Cat c = (Cat) a;
		c.work();
	}
}
