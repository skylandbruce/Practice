package TABLE;

import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableRowSorter;

// 테이블 작업
public class FormJTable extends JPanel {
	JTableOneFormSplit tfb;	
	
	DefaultTableModel dtm;
	JTable table;
	JScrollPane scroll;

	String[] columnNames = { "이름", "나이", "직업" };
	Object[][] rowData = { { "홍길동", 13, "학생" }, { "김유신", 15, "화랑" }, { "김덕만", 16, "공주" } };

	int srow = -1; // 선택된 행 인덱스 값. JTable에서 선택된 행이 없다면 -1 반환

	public FormJTable(JTableOneFormSplit tfb) {
		this.tfb = tfb;		
				
		dtm = new DefaultTableModel(rowData, columnNames) {
			   // DefaultTableModel 셀 편집 불가능
			   public boolean isCellEditable(int rowIndex, int colIndex) {
				   return false; 
			   }
		};
		
		
		table = new JTable(dtm); 
		scroll = new JScrollPane(table, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		add(scroll);	
		
		table.setAutoCreateRowSorter(true); // 컬럼 헤더 클릭하면 자동정렬
		//table.setFillsViewportHeight(true);
		table.setBackground(new Color(255, 255, 204));	// 테이블 배경색(기본 흰색)	
		table.setSelectionBackground(Color.blue);	
		table.setSelectionForeground(Color.white);			
				
		// 행 높이 조절
		table.setRowHeight(25);	
		
		// 셀의 너비 조절하고, 셀 안에 데이터 정렬 DefaultTableCellRenderer 객체 이용
		DefaultTableCellRenderer celAlignCenter = new DefaultTableCellRenderer();
		celAlignCenter.setHorizontalAlignment(JLabel.CENTER);	// 셀 데이터 가운데 정렬	
		
		// 각 셀 너비와 정렬. getColumn()로 해당 컬럼 가져와서, setCellRenderer()로 설정		
		table.getColumn("이름").setPreferredWidth(10);			// 너비 10픽셀
		table.getColumn("이름").setCellRenderer(celAlignCenter);	// 텍스트 가운데	
		
		table.getColumn("나이").setPreferredWidth(25);			// 너비 10픽셀
		table.getColumn("나이").setCellRenderer(celAlignCenter);	// 텍스트 가운데	
		
		
		// 이벤트는 테이블에서만 발생. 테이블은 액션이벤트 X. 테이블 셀 마우스 클릭 이벤트
		table.addMouseListener(new MyAdapter());
	}

	class MyAdapter extends MouseAdapter {
		public void mouseClicked(MouseEvent e) {
			srow = table.getSelectedRow(); 
			// JTable의 데이터 가져오기/변경하기
			// setValueAt(바꿀값, 행인덱스, 열인덱스)
			// getValueAt(행인덱스, 열인덱스)			
			
			// rowData의 데이터는 Object 타입 OK, String 타입 OK
			String name = (String) dtm.getValueAt(srow, 0);
			String age = dtm.getValueAt(srow, 1).toString();
			String job = dtm.getValueAt(srow, 2).toString();

			tfb.label.setText("이름:" + name + ", 나이:" + age + ", 직업:" + job);

			// 폼의 각 텍스트 필드에도 표시
			tfb.inForm.tf_name.setText(name); // setText()는 String
			tfb.inForm.tf_age.setText(age);
			JTableOneFormSplit.inForm.tf_job.setText(job);

			// [입력] 버튼 [수정] 버튼 바꾸기			
			tfb.inForm.bt_input.setText("수정");
		}
	}
}
