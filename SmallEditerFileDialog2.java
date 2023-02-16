package SmailEditor;


import java.awt.Color;
import java.awt.FileDialog;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.FileReader;
import java.io.FileWriter;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextPane;
import javax.swing.border.Border;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;

//문서(블록단위 처리 가능)에 속성 적용하는 3단계 
//1. SimpleAttributeSet 클래스는 텍스트에 속성(글꼴, 크기, 스타일, 색상등) 적용 클래스
//2. StyleConstants 클래스는 SimpleAttributeSet 이용 텍스트에 실제 속성 적용  
//3. setCharacterAttributes() 이용 편집영역의 블록 설정한 텍스트 속성 활성화

//프레임 클래스에 이벤트 처리기 구현
public class SmallEditerFileDialog2 extends JFrame implements ActionListener, ItemListener {
	JPanel menupanel, downpanel, downpanel2;
	JButton newbtn, copybtn, cutbtn, pastebtn, savebtn, openbtn, colorbtn;
	JTextPane editarea;
	JComboBox combox;
	JRadioButton red, yellow, blue, green, pink;

	// 텍스트 속성 정의하기 위한 클래스
	SimpleAttributeSet saset;
	String path = null; // 저장경로
	Font font;
	Image logo;

	// 생성자. 프레임 설정
	public SmallEditerFileDialog2() {
		this.setTitle("메모장");
		this.setSize(800, 800);

		Toolkit tk = Toolkit.getDefaultToolkit();
		logo = tk.getImage("D:/이미지/5.jpg");
		this.setIconImage(logo);
		
		// 텍스트 속성 적용하는 SimpleAttributeSet 클래스
		saset = new SimpleAttributeSet();
		
		EditWindows();	// EditWindows() 호출

		this.setVisible(true);
	}
	
	// 화면 디자인
	void EditWindows() {
		menupanel = new JPanel();
		menupanel.setLayout(new GridLayout(0, 7)); // 1, 0

		newbtn = new JButton("새글");
		copybtn = new JButton("복사");
		cutbtn = new JButton("잘라내기");
		pastebtn = new JButton("붙이기");
		savebtn = new JButton("저장하기");
		openbtn = new JButton("불러오기");
		colorbtn = new JButton("색상");

		menupanel.add(newbtn);
		menupanel.add(copybtn);
		menupanel.add(cutbtn);
		menupanel.add(pastebtn);
		menupanel.add(savebtn);
		menupanel.add(openbtn);
		menupanel.add(colorbtn);

		openbtn.addActionListener(this);
		savebtn.addActionListener(this);
		colorbtn.addActionListener(this);
		this.add("North", menupanel);

		editarea = new JTextPane();
		editarea.setToolTipText("이곳에 텍스트를 입력하세요");
		font = new Font("돋움", Font.BOLD, 15); // 초기 폰트 설정
		editarea.setFont(font);
		editarea.setSelectionColor(Color.YELLOW);	// 블록 설정 텍스트 배경색
		editarea.setSelectedTextColor(Color.RED);	// 블록 설정 텍스트 전경색	
		editarea.setBackground(Color.WHITE);
		this.add(editarea);

		downpanel = new JPanel();
		downpanel.setLayout(new GridLayout(0, 2));
		Border border = BorderFactory.createTitledBorder("글자크기");
		Border border1 = BorderFactory.createTitledBorder("글자색상");

		String[] size = { "5", "10", "15", "20", "25", "30" };
		combox = new JComboBox(size);
		combox.setSelectedIndex(2);	// 15 설정
		combox.setBorder(border);
		downpanel.add(combox);

		downpanel2 = new JPanel();
		ButtonGroup group = new ButtonGroup();
		red = new JRadioButton("red", true);
		yellow = new JRadioButton("yellow");
		blue = new JRadioButton("blue");
		green = new JRadioButton("green");
		pink = new JRadioButton("pink");
		group.add(red);
		group.add(yellow);
		group.add(blue);
		group.add(green);
		group.add(pink);
		downpanel2.add(red);
		downpanel2.add(yellow);
		downpanel2.add(blue);
		downpanel2.add(green);
		downpanel2.add(pink);
		downpanel2.setBorder(border1);
		downpanel.add(downpanel2);

		this.add("South", downpanel);

		//combox.addItemListener(this);
		combox.addActionListener(this);
		red.addActionListener(this);
		yellow.addActionListener(this);
		blue.addActionListener(this);
		green.addActionListener(this);
		pink.addActionListener(this);

		// 무명(익명) 클래스로 이벤트 처리기 작성. 객체생성+클래스정의 동시
		newbtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editarea.requestFocus();
				editarea.setText(null);
				setTitle("메모장");
				newbtn.setBackground(Color.cyan); // 시안
			}
		});

		copybtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editarea.copy();
			}
		});

		cutbtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editarea.cut();
			}
		});

		pastebtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editarea.paste();
			}
		});
	}

	public void actionPerformed(ActionEvent e) {		
		Object o = e.getSource();
		path = null;

		if (o == openbtn) { 			 
			FileDialog dialog = new FileDialog(this, "불러오기", FileDialog.LOAD);
			dialog.setFile("*.txt");
			dialog.setVisible(true);

			path = dialog.getDirectory() + dialog.getFile();
			String s = ""; // 한문자+한문자

			try {
				// FileReader 클래스는 외부 파일 읽기 
				// read()는 FileReader 객체 이용 문자의 코드값 입력 
				FileReader r1 = new FileReader(path);
				
				int k; // 코드 값
				while (true) {
					k = r1.read(); 
					if (k == -1) { // -1 문자 없다
						break;
					}
					s += (char) k; // 코드 값 문자로 형변환 한 후 문자열 결합
				}
				
				setTitle(path);
				r1.close();
			} catch (Exception e2) {
				System.out.println("오류" + e2);
			}
			
			editarea.setText(s);	// 편집영역에 표시
		}

		// 저장
		if (o == savebtn) { 
			FileDialog dialog = new FileDialog(this, "저장하기", FileDialog.SAVE);
			dialog.setFile("*.txt");
			dialog.setVisible(true);

			path = dialog.getDirectory() + dialog.getFile();

			try {
				// FileWriter 클래스는 외부 파일 저장 
				// write()는 FileWriter 객체 이용 문자열 저장 
				FileWriter w = new FileWriter(path);
				String s = editarea.getText();
				w.write(s);
				
				setTitle(path);
				w.close();
			} catch (Exception e2) {
				System.out.println("오류" + e2);
			}
		}

		if (o == colorbtn) {
			// Color color = JColorChooser.showDialog(editarea, "색선택", Color.YELLOW);

			JColorChooser chooser = new JColorChooser();
			Color color = chooser.showDialog(this, "색선택", Color.YELLOW);
			editarea.setForeground(color); // 편집영역 전체텍스트 적용

			// StyleConstants.setForeground(saset, color);// saset에 color 저장
			// editarea.setCharacterAttributes(saset, true);
		}

		if (o == red)
			StyleConstants.setForeground(saset, Color.RED);
		if (o == yellow)
			StyleConstants.setForeground(saset, Color.yellow);
		if (o == blue)
			StyleConstants.setForeground(saset, Color.blue);
		if (o == green)
			StyleConstants.setForeground(saset, Color.green);
		if (o == pink)
			StyleConstants.setForeground(saset, Color.pink);

		int size = Integer.parseInt((String) combox.getSelectedItem());
		StyleConstants.setFontSize(saset, size);
		editarea.setCharacterAttributes(saset, true);
		editarea.requestFocus();
	}

	@Override
	public void itemStateChanged(ItemEvent e) {		
//		editarea.getSelectedTextColor();
//		int size = Integer.parseInt((String) combox.getSelectedItem());
//		StyleConstants.setFontSize(saset, size);		
//		editarea.setCharacterAttributes(saset, true);
	}
		
	public static void main(String[] args) {
		new SmallEditerFileDialog2();
	}

}
