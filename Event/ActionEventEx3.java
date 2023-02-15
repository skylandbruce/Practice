
import java.awt.FlowLayout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

// 프레임 클래스에 이벤트 처리기를 구현
class MyFrame3 extends JFrame implements ActionListener {
	private JPanel panel;
	JButton button;

	public MyFrame3() {
		setTitle("액션 이벤트 예제");		
		setSize(260, 200);
		  
		panel = new JPanel();
		button = new JButton("버튼을 누르시오");			
		panel.add(button);
		add(panel);
		
		// 버튼에 이벤트 리스너 추가
		button.addActionListener(this);
		
		setVisible(true);
	}
	// ActionListener 구현
	// ActionListener 인터페이스의 오버라이딩 된 추상 메소드. 반드시 구현
	@Override
	public void actionPerformed(ActionEvent e) {		
		JButton btn = (JButton) e.getSource();
		if (btn.getText() == "버튼을 누르시오") 
			btn.setText("마침내 버튼이 눌려졌습니다.");
		else
			btn.setText("버튼을 누르시오");		
	}
}	

public class ActionEventEx3 {	
	public static void main(String[] args) {
		 new MyFrame3();
	}
}
