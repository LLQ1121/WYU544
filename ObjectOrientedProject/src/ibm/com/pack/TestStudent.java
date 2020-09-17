package ibm.com.pack;
public class TestStudent {
	public static void main(String[] args) {
		Student student = new Student();
		student.setName("yuhua");
		student.setAge(18);
		student.setSchool("BJTU");
		System.out.println("name: " + student.getName() 
		+ " age:" + student.getAge() + " School:" + student.getSchool());
	}

}
