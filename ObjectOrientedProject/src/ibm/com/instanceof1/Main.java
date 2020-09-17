package ibm.com.instanceof1;
public class Main {
	public static void main(String[] args) {
		show(new Cat());
		show(new Cattle());
	}
	public static void show(Animal a) {
		// 类型判断
		if (a instanceof Cat) { // 猫做的事情
			Cat c = (Cat) a;
			c.work();
		} else if (a instanceof Cattle) { // 狗做的事情
			Cattle c = (Cattle) a;
			c.work();
		}
	}
}
