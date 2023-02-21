package TABLE;

import java.awt.Color;
import java.awt.Container;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

public class CDFTable7 extends JFrame {
	Container con = getContentPane();
	JTable table;
	JScrollPane jsp;

	public CDFTable7() {			
		String colheader[] = { "No", "Name", "Java", "Jsp", "Python", "Total"};				
		String rowdata[][] = { {"1", "김진호", "100", "100", "100", "100%" }, 
				               {"2", "박효신", "90", "90", "90", "90%" },
		                       {"3", "마마무", "80", "80", "80", "80%" }
		                     };
		

		con.setBackground(Color.WHITE);
		con.setLayout(null);		
		
		table = new JTable(rowdata, colheader);
		jsp = new JScrollPane(table);
		con.add(jsp);
		jsp.setBounds(25, 10, 569, 206);
		
		setSize(650, 400);
		setVisible(true);
		
///////////////////////////////////////////////////
		int row = table.getSelectedRow();
		table.setBackground(new Color(255, 255, 204));
		table.setSelectionBackground(Color.blue);	// JTable 행 선택 배경색
		table.setSelectionForeground(Color.white);	// JTable 행 선택 전경색

		// JTable 행 높이 조절
		table.setRowHeight(25);
		
		// JTable의 컬럼 너비 조절하고, 컬럼 안에 데이터 정렬 DefaultTableCellRenderer 객체 이용
		DefaultTableCellRenderer celAlignCenter = new DefaultTableCellRenderer();
		celAlignCenter.setHorizontalAlignment(JLabel.CENTER);	// 컬럼 데이터 가운데 정렬		
		
		DefaultTableCellRenderer celAlignRight = new DefaultTableCellRenderer();
		celAlignRight.setHorizontalAlignment(JLabel.RIGHT);		
		
		DefaultTableCellRenderer celAlignLeft = new DefaultTableCellRenderer();
		celAlignLeft.setHorizontalAlignment(JLabel.LEFT);		

		// JTable의  컬럼 너비와 정렬. getColumn()로 해당 컬럼 반환		
		table.getColumn("No").setPreferredWidth(10);			// 컬럼 너비 10픽셀 설정
		table.getColumn("No").setCellRenderer(celAlignCenter);	// 컬럼 텍스트 가운데	설정	
		table.getColumn("Name").setPreferredWidth(100);
		table.getColumn("Name").setCellRenderer(celAlignCenter);
		table.getColumn("Java").setPreferredWidth(10);
		table.getColumn("Java").setCellRenderer(celAlignCenter);
		
		table.getColumn("Jsp").setPreferredWidth(10);		
		table.getColumn("Jsp").setCellRenderer(celAlignRight);
		table.getColumn("Python").setPreferredWidth(30);
		table.getColumn("Python").setCellRenderer(celAlignRight);
		
		table.getColumn("Total").setPreferredWidth(10);
		table.getColumn("Total").setCellRenderer(celAlignLeft);		
		
		DefaultTableCellRenderer dtcr = new DefaultTableCellRenderer();
		dtcr.setBackground(Color.GREEN);
		dtcr.setForeground(Color.BLUE);		
		table.getColumn("Total").setCellRenderer(dtcr);		// JTable의 컬럼 배경색, 전경색 설정 		

		////////////////////////
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	
	public static void main(String[] args) {		
		CDFTable7 w = new CDFTable7();				
	}
}


//Container con = getContentPane();			
//con.setBackground(Color.white);