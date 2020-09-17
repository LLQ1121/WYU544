package ibm.com.obj;

public class Birthday {
	 private int day;
	    private int month;
	    private int year;
	    //有参构造方法
	    public Birthday(int day, int month, int year) {
	        this.day = day;
	        this.month = month;
	        this.year = year;
	    }
	 
	    public int getDay() {
	        return day;
	    }
	 
	    public void setDay(int day) {
	        this.day = day;
	    }
	 
	    public int getMonth() {
	        return month;
	    }
	 
	    public void setMonth(int month) {
	        this.month = month;
	    }
	 
	    public int getYear() {
	        return year;
	    }
	 
	    public void setYear(int year) {
	        this.year = year;
	    }
	 
	    @Override
	    public String toString() {
	        return "Birthday{" +
	                "day=" + day +
	                ", month=" + month +
	                ", year=" + year +
	                '}';
	    }
	   
}
