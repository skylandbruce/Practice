package TABLE;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.ListSelectionModel;

// JSplitPane 화면을 두 개의 구성요소로 분리
// Dimension 클래스는 특정영역의 사각형의 폭과 높이의 값을 관리할 수 있도록 해주는 클래스
// 프레임에 입력폼과 테이블 표시하여 행, 열 추가 삭제
public class JTableOneFormSplit extends JFrame {
//	FormInput inForm;
//	FormJTable taForm;
	
	static FormInput inForm;
	static FormJTable taForm;
	
	JPanel northp, southp;
	JLabel label;
	JButton bt_del, bt_exit;

	Font font;	

	JSplitPane splitPane;	// 화면을 두 개의 구성요소로 나누는 컴포넌트

	public JTableOneFormSplit() {
		setTitle("JTable One Form Application");
 
		// 위쪽 JPanel
		northp = new JPanel();
		northp.setSize(350, 40);
		// Dimension 클래스는 특정영역의 사각형의 폭과 높이의 값을 관리할 수 있도록 해주는 클래스
		// northp.setPreferredSize(new Dimension(350, 40));
		label = new JLabel("안녕!! 테이블*^~^*", JLabel.CENTER);
		label.setPreferredSize(new Dimension(350, 30));
		font = new Font("돋움", Font.BOLD, 18);
		label.setFont(font);
		northp.add(label);		
		add("North", northp);

		// 아래쪽 JPanel
		southp = new JPanel();
		bt_del = new JButton("  삭제  ");
		bt_exit = new JButton("  종료  ");
		southp.add(bt_del);
		southp.add(bt_exit);		
		add("South", southp);

		bt_del.addActionListener(new MyListner());
		bt_exit.addActionListener(new MyListner());
		
		inForm = new FormInput(this);	// 입력 클래스		
		taForm = new FormJTable(this);	// 테이블 클래스	
		
		inForm.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("입력"),
                BorderFactory.createEmptyBorder(5,5,5,5)));
		
		taForm.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("테이블"), null));				
		
		//taForm.setBorder(BorderFactory.createEmptyBorder());	// 보더 없애기
		
		//JSplitPane은 화면을 두 개의 구성요소로 나누는 컴포넌트. 왼쪽: inForm 객체 배치  오: taForm 객체 배치		
		splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,  inForm, taForm);
		
		splitPane.setResizeWeight(0.8);	// 분할 영역 크기 변경
		//splitPane.setDividerSize(10);	// 디바이더 두께를 설정
		//splitPane.setContinuousLayout(true);	// 크기조절 가능
		splitPane.setOneTouchExpandable(true);	// 삼각형. 분할기를 빠르게 확장/축소	
		
		add(splitPane, BorderLayout.CENTER);			

		setBounds(400, 300, 750, 600);
		setVisible(true);
	}

	class MyListner implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			Object ob = e.getSource();

			// [삭제]
			if (ob == bt_del) {		
				if (taForm.srow < 0) { // JTable에서 선택된 행이 없다면 -1 리턴
					JOptionPane.showMessageDialog(null, "삭제할 이름을 선택하세요?");
					return;
				}

				String name = (String) taForm.dtm.getValueAt(taForm.srow, 0);
				int yn = JOptionPane.showConfirmDialog(null, name + " 님을 삭제하시겠습니까?", "이름", JOptionPane.YES_NO_OPTION);

				if (yn == JOptionPane.YES_OPTION) {
					taForm.dtm.removeRow(taForm.srow);
					inForm.initTF();		
				} else
					return;				
				
				JOptionPane.showMessageDialog(null, name + " 님을 삭제했습니다.");

			}

			// [종료]
			if (ob == bt_exit) {
				System.exit(0);
			}

		}
	}

	public static void main(String[] args) {
		new JTableOneFormSplit();
	}
}


