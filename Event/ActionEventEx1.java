import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

//내부 클래스(inner class)로 이벤트 처리기를 작성
class ActionEventEx1 extends JFrame {
	private JPanel panel;
	private JButton button;   
   
	public ActionEventEx1() {    
		setTitle("이벤트 예제");  
		setSize(300, 200);
		// setBounds(400, 300, 300, 200); // 프레임 위치, 크기
  
		panel = new JPanel();
		button = new JButton("버튼을 누르시오");

		// Action 이벤트 리스너 객체 생성
		MyListener listener = new MyListener();
		// Action 이벤트 리스너 등록
		button.addActionListener(listener);
		panel.add(button);

		add(panel);
		setVisible(true);
	}
        
	// 이벤트 처리하기 
	// 내부 클래스(inner class)로 이벤트 처리기를 작성
	class MyListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			// 이벤트 객체가 제공하는 메소드들 중 getSource() 이용
			// getSource() 이벤트 소스 알아 내기.  Object EventObject.getSource()
			// 발생한 이벤트의 소스(JButton) 컴포넌트의 레퍼런스(주소값) 리턴. 즉 JButton 객체의 참조변수 리턴 
			// getSource()는 Object 반환. 타입변환 필요
			
//			JButton btn = (JButton) e.getSource();
//			if (btn.getText() == "버튼을 누르시오") 
//				btn.setText("마침내 버튼이 눌려졌습니다.");
//			else
//				btn.setText("버튼을 누르시오");			
			
			
//			if (e.getSource() == button) 
//				button.setText("마침내 버튼이 눌려졌습니다.");
			
			// getActionCommand()는 이벤트 소스의 텍스트 반환. 
			// String str = e.getActionCommand();
			if (e.getActionCommand() == "버튼을 누르시오") 
				button.setText("마침내 버튼이 눌려졌습니다.");			
			else
				button.setText("버튼을 누르시오");
			
		}
	}

	public static void main(String[] args) {
		new ActionEventEx1();
	}
}