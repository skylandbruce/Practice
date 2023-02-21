package TABLE;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTextField;

//입력 폼 작업
public class FormInput extends JPanel implements ActionListener {
	JTableOneFormSplit tf;	

	JLabel la_name, la_age, la_job;
	JTextField tf_name, tf_age, tf_job;
	JButton bt_input, bt_cancel;

	public FormInput(JTableOneFormSplit tf) {
		this.tf = tf;	
			
		setLayout(null);
		la_name = new JLabel("이름");
		la_age = new JLabel("나이");
		la_job = new JLabel("직업");

		tf_name = new JTextField();
		tf_age = new JTextField();
		tf_job = new JTextField();

		bt_input = new JButton("입력");
		bt_cancel = new JButton("취소");

		la_name.setBounds(30, 30, 30, 30);
		la_age.setBounds(30, 80, 30, 30);
		la_job.setBounds(30, 130, 60, 30);

		tf_name.setBounds(80, 30, 80, 30);
		tf_age.setBounds(80, 80, 80, 30);
		tf_job.setBounds(80, 130, 80, 30);

		bt_input.setBounds(30, 190, 60, 30);
		bt_cancel.setBounds(100, 190, 60, 30);

		add(la_name);
		add(la_age);
		add(la_job);

		add(tf_name);
		add(tf_age);
		add(tf_job);

		add(bt_input);
		add(bt_cancel);

		bt_input.addActionListener(this);
		bt_cancel.addActionListener(this);	
		
		setSize(500, 500);
		//setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object ob = e.getSource();
		
		// 입력폼의 [입력]
		if (ob == bt_input) {
			String name = tf_name.getText();
			String age = tf_age.getText();
			String job = tf_job.getText();
							
			// 필드의 입력 값 체크하기
			// isEmpty() 문자열이 null이거나 비어있는 경우("")만 확인	
			// isEmpty() 비어있는 상태(정확하게 "" 값이 들어가있는 상태). null과 공백데이터 와는 다르다
			// null 은 인스턴스가 생성되지 않은 상태. 주소값을 가지고 있지 않는 상태						 
			if (name.isEmpty()) {					
				JOptionPane.showMessageDialog(this, "이름입력!!");
				tf_name.requestFocus();
				return;
			}
			if (age.isEmpty()) {
				JOptionPane.showMessageDialog(this, "나이입력!!");
				tf_age.requestFocus(); 
				return;
			}
			if (job.length() == 0) {
				JOptionPane.showMessageDialog(this, "직업입력!!");
				tf_job.requestFocus();
				return;
			}
						
			if (bt_input.getText() == "입력") { 
				// JTable 영역에 들어갈 데이터 배열로 생성
				Object rowData[] = { name, age, job }; 
				//tf.taForm.dtm.addRow(rowData); 
				JTableOneFormSplit.taForm.dtm.addRow(rowData); 

				initTF(); 
				
			} else if (bt_input.getText() == "수정") {
				// JTable의 데이터 가져오기/변경하기
				// setValueAt(바꿀값, 행인덱스, 열인덱스)
				// getValueAt(행인덱스, 열인덱스)					
				
				//String name = (String) table.getValueAt(srow, 0);
				tf.taForm.dtm.setValueAt(name, tf.taForm.srow, 0);
				JTableOneFormSplit.taForm.dtm.setValueAt(age, JTableOneFormSplit.taForm.srow, 1);
				JTableOneFormSplit.taForm.dtm.setValueAt(job, JTableOneFormSplit.taForm.srow, 2);

				initTF();				
			}				
		}			
		// 입력폼의 [취소]
		if (ob == bt_cancel) {
			tf_name.setText(null);
			tf_age.setText("");
			tf_job.setText("");
			tf_name.requestFocus();
		}
	}

	// 폼 초기화
	void initTF() {
		tf_name.setEditable(true);
		tf_name.setText("");
		tf_age.setText("");
		tf_job.setText("");
		tf_name.requestFocus();
		bt_input.setText("입력");
	}

}
