package cn.ibm.homework3;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class copyFile {

	public static void copy(String s1, String s2) throws IOException {
		FileInputStream in = new FileInputStream(s1);
		File file = new File(s2);
		if (!file.exists()) {
			file.createNewFile();
		}
		FileOutputStream out = new FileOutputStream(file);
		byte b[] = new byte[s1.length()];
		int c;
		while ((c = in.read(b)) != -1) {
			for (int i = 0; i < c; i++)
				out.write(b[i]);
		}
		in.close();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		String s1 = "C:/Users/11210/Desktop/ab/a1/myfile.txt";
		String s2 = "C:/Users/11210/Desktop/ab/a2/myfile_cp.txt";
		copy(s1, s2);

		File file = new File("C:/Users/11210/Desktop/ab/a2/");
		File[] fs = file.listFiles();
		for (File f : fs) {
			if (!f.isDirectory()) {
				System.out.println(f);
			}
		}
	}

}
