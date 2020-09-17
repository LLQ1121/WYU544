package ibm.com.sup;
public class Cattle extends Animal {
    public Cattle() {
        super();
    }
    public void getFatherData(){
        System.out.println(super.name);
        super.move();
    }
    
    public static void main(String[] args) {
        Cattle dog = new Cattle();
        dog.getFatherData();
    }
}
