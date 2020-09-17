package ibm.com.collection.arraylist;

import java.util.ArrayList;

class Student {
    private String name;
    private int    age;

    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
    
    @Override
    public boolean equals(Object object) {
        Student student = (Student) object;
        return name.equals(student.getName()) && age == student.getAge();
    }
    
}

public class ArrayListContainsMethod {
	public static void main(String[] args) {
		ArrayList<Student> students = new ArrayList<>();
        Student ryan = new Student("Ryan", 25);
        Student kiven = new Student("Kiven", 25);
        students.add(ryan);
        students.add(kiven);
        Student ry = new Student("Ryan", 25);
        System.out.println("²âÊÔcontains£º"+students.contains(ry));
        Student kv = new Student("Kiven", 25);
        ArrayList<Student> sts = new ArrayList<>();
        sts.add(ry);
        sts.add(kv);
        System.out.println("²âÊÔcontainsAll£º"+students.containsAll(sts));

 
    }
}
