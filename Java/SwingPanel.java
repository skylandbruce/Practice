<<<<<<< HEAD:SwingPanel.java
import javax.swing.JOptionPane;

/**
 * Ctrl+Shift+f 자동 열맞춤
 * Ctrl+Shift+o 라이브러리 자동 추가
 * @author bruce
 *
 */
 // Crative Comment
public class SwingPanel {

	public SwingPanel() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final String str_Title="정수를 입력해 주세요";
		String str_input=null;
		int n_input=0;
		
		str_input=JOptionPane.showInputDialog(str_Title);
		n_input=Integer.parseInt(str_input);
		
		System.out.printf("입력된 값은 %d 입니다.",n_input);
		
		double numerator=4l;
		double denomirator;
		double dl_num=numerator/n_input;
		System.out.printf("입력된 값은 %f 입니다.",dl_num);
		
	}

}
=======
import javax.swing.JOptionPane;

/**
 * Ctrl+Shift+f 자동 열맞춤
 * Ctrl+Shift+o 라이브러리 자동 추가
 * @author bruce
 *
 */
public class SwingPanel {

	public SwingPanel() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final String str_Title="정수를 입력해 주세요";
		String str_input=null;
		int n_input=0;
		
		str_input=JOptionPane.showInputDialog(str_Title);
		n_input=Integer.parseInt(str_input);
		
		System.out.printf("입력된 값은 %d 입니다.",n_input);
		
		double numerator=4l;
		double denomirator;
		double dl_num=numerator/n_input;
		System.out.printf("입력된 값은 %f 입니다.",dl_num);
		
	}

}
>>>>>>> 820e65c66b7e37a85f3663f064ede3616baa29c9:Java/SwingPanel.java
