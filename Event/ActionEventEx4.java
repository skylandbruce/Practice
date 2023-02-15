//이벤트 처리를 위한 패키지 
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
// 무명(익명) 클래스로 이벤트 처리기 작성 방법. 클래스 작성과 객체생성 한번에
class MyFrame4 extends JFrame {
	private JPanel panel;
	private JButton button;	

	public MyFrame4() {
		setSize(300, 200);		
		setTitle("이벤트 예제");

		panel = new JPanel();
		button = new JButton("버튼을 누르시오");		
		panel.add(button);	
		add(panel);	
		
        // 무명(익명) 클래스로 이벤트 처리기를 작성. 클래스 정의+객체 생성 동시 작성		
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JButton btn = (JButton) e.getSource();
				if (btn.getText() == "버튼을 누르시오") 
					btn.setText("마침내 버튼이 눌려졌습니다.");
				else
					btn.setText("버튼을 누르시오");		
			}
		});
		
		setVisible(true);	
		
	} 	
} 

public class ActionEventEx4 {
	public static void main(String[] args) {		
		new MyFrame4();
	}
}