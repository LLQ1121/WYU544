package ibm.com.obj;

public class TestBirthday {
	public static void main(String[] args) {
		// new TestBirthday();相当于调用了TestBirthday类的无参构造方法（编译器默认加的）
		TestBirthday test = new TestBirthday();
		// 调到这句在栈内存分配一块名为date，值为9的内存
		int date = 9;
		// new Birthday(7,7,1970)；相当于调用了Birthday类中的有参构造方法
		Birthday d1 = new Birthday(7, 7, 1970);
		Birthday d2 = new Birthday(1, 1, 2000);
		test.change1(date);
		test.change2(d1);
		System.out.println("date1=" + d1.getDay());
		test.change3(d2);
		System.out.println("date2=" + d2.getDay());
		System.out.println("date=" + date);
		d1.toString();
		d2.toString();

	}

	public void change1(int i) {
		i = 1234;
	}

	public void change2(Birthday b) {
		b = new Birthday(22, 2, 2004);
	}

	public void change3(Birthday b) {
		b.setDay(22);
	}
}
