package ibm.com.pack;

public class TestStudent1 {
	public static void main(String[] args) {
        Student1 student=new Student1();
        Person1 person=new Person1();
        person.setName("john");
        person.setAge(19);
        student.setName("yuhua");
        student.setAge(18);
        student.setSchool("BJTU");
        System.out.println(person.toString());
        System.out.println(student.toString());
    }
}
