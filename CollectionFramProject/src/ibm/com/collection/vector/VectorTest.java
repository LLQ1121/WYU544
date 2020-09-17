package ibm.com.collection.vector;

import java.util.Vector;
import java.util.concurrent.CountDownLatch;

public class VectorTest {
	
	static class MyThread extends Thread {
		private CountDownLatch countDownLatch;
		private Vector<String> vector;
		private String element;
		
		public MyThread(CountDownLatch countDownLatch, Vector<String> vector, String element) {
			this.countDownLatch = countDownLatch;
			this.vector = vector;
			this.element = element;
		}
		
		@Override
		public void run() {
			super.run();
			
			try {

             synchronized (vector) {
				if (!vector.contains(element)) {
					System.out.println("≤ªœ‡µ»---- ");
					Thread.sleep(1000);
					vector.add(element);
				}
             }
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				countDownLatch.countDown();
			}
		}
	}
 
	public static void main(String[] args) throws InterruptedException {
		CountDownLatch countDownLatch = new CountDownLatch(2);
		Vector<String> vector = new Vector<>();
		MyThread myThread1 = new MyThread(countDownLatch, vector, "abc");
		MyThread myThread2 = new MyThread(countDownLatch, vector, "abc");
		myThread1.start();
		myThread2.start();
		countDownLatch.await();
		int vectorSize = vector.size();
		System.out.println("vector size: " + vectorSize);
		for (int i = 0; i < vectorSize; i++) {
			System.out.println("index " + i + ": " + vector.get(i));
		}
	}
}
