package ibm.com.pack;

public class Student1 extends Person1{
	private String school;
    public String getSchool() {
        return school;
    }
    public void setSchool(String school) {
        this.school = school;
    }
    @Override
    public String toString() {
        return "Student1{" + "name='" + getName() + '\'' +
                " age='" + getAge()+'\''+
                " school='" + school + '\'' +
                '}';
    }
}
