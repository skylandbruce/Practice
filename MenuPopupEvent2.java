import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JTextPane;
import javax.swing.KeyStroke;

public class MenuPopupEvent2 extends JFrame implements ActionListener {
	private JMenuBar menuBar; // 메뉴바
	private JMenu file, edit, color, submenu; // 메뉴
	private JMenuItem f1, f2, f3, f4; // 메뉴 항목
	private JMenuItem e, e1, e2, e3, e4; // 메뉴 항목
	private JMenuItem sbMenuItem1, sbMenuItem2; // 서브메뉴에 등록되 서브 메뉴 항목
	private JMenuItem c1, c2, c3; // 메뉴 항목
	private JRadioButtonMenuItem rbMenuItem1, rbMenuItem2;
	private JCheckBoxMenuItem cbMenuItem1, cbMenuItem2;
	private JTextPane text; // 텍스트 편집 창

	JPopupMenu popmn; // 팦업 객체
	JMenuItem jmCopy, jmCut, jmPaste; // // 팦업 메뉴
	
	MenuPopupEvent2() {
		setTitle("메뉴 만들기");
		makeMenu(); // 화면 디자인 호출
		pop(); // 팦업메뉴 호출

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500, 500);
		setVisible(true);
	}

	// 화면 디자인
	void makeMenu() {
		text = new JTextPane();
		// 메뉴바 생성
		menuBar = new JMenuBar();
		// 메뉴 생성과 단축키 설정. setMnemonic()
		file = new JMenu("파일(F)");
		file.setMnemonic('F');
		file.setMnemonic(KeyEvent.VK_F); // 단축키 Alt + F 설정
		edit = new JMenu("편집(E)");
		edit.setMnemonic('E');
		color = new JMenu("색상(C)");
		color.setMnemonic('C');

		// 메뉴 항목 생성과 단축키 설정. setAccelerator()
		f1 = new JMenuItem("새 파일(N)"); // Ctrl + N
		f1.setAccelerator(KeyStroke.getKeyStroke('N', Event.CTRL_MASK));
		f2 = new JMenuItem("파일 열기(O)");
		f2.setAccelerator(KeyStroke.getKeyStroke('O', Event.CTRL_MASK));
		f3 = new JMenuItem("파일 저장(S)");
		f3.setAccelerator(KeyStroke.getKeyStroke('S', Event.CTRL_MASK));
		f4 = new JMenuItem("끝내기(X)");
		f4.setAccelerator(KeyStroke.getKeyStroke('X', Event.CTRL_MASK));

		// [편집] 메뉴에 메뉴 항목 등록하고 이미지 아이콘이란 라디오 버튼, 체크 버튼 표시
		// ImageIcon 객체 이용하여 메뉴 항목 앞에 이미지 아이콘 설정
		ImageIcon icon = new ImageIcon("c:\\이미지/b.jpg");
		e = new JMenuItem("아이콘 보기", icon);
		edit.add(e);

		// [편집] 메뉴에 구분선 넣기
		edit.addSeparator();
		// 라디오 버튼 메뉴 항목들을 생성하여 그룹에 등록하여 메뉴에 추가
		ButtonGroup group = new ButtonGroup();
		rbMenuItem1 = new JRadioButtonMenuItem("라디오 버튼 메뉴 항목 1");
		rbMenuItem1.setSelected(true); // 디폴트 선택
		group.add(rbMenuItem1);
		edit.add(rbMenuItem1);
		rbMenuItem2 = new JRadioButtonMenuItem("라디오 버튼 메뉴 항목 2");
		group.add(rbMenuItem2);
		edit.add(rbMenuItem2);

		// [편집] 메뉴에 구분선 넣기
		edit.addSeparator();
		// 체크 박스 메뉴 항목들을 생성하여 메뉴에 추가
		cbMenuItem1 = new JCheckBoxMenuItem("체크 박스 메뉴 항목 1");
		edit.add(cbMenuItem1);
		cbMenuItem2 = new JCheckBoxMenuItem("체크 박스 메뉴 항목 2");
		edit.add(cbMenuItem2);

		// [편집] 메뉴에 구분선 넣기
		edit.addSeparator();
		// [편집] 메뉴에 서브 메뉴 항목 생성하여 등록
		submenu = new JMenu("서브메뉴");
		// [편집] 메뉴에 서브 메뉴에 서브 메뉴 항목 생성하여 등록
		sbMenuItem1 = new JMenuItem("서브 메뉴 항목 1");
		sbMenuItem1.setAccelerator(KeyStroke.getKeyStroke('1', Event.ALT_MASK));
		submenu.add(sbMenuItem1);
		sbMenuItem2 = new JMenuItem("서브 메뉴 항목 2");
		submenu.add(sbMenuItem2);
		edit.add(submenu);

		c1 = new JMenuItem("파란색"); // Ctrl + B
		c1.setAccelerator(KeyStroke.getKeyStroke('B', Event.CTRL_MASK));
		c2 = new JMenuItem("빨간색");
		c2.setAccelerator(KeyStroke.getKeyStroke('R', Event.CTRL_MASK));
		c3 = new JMenuItem("노란색");
		c3.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Y, ActionEvent.CTRL_MASK));

		// [파일] 메뉴에 메뉴 항목 등록
		file.add(f1);
		file.add(f2);
		file.add(f3);
		// [파일] 메뉴에 구분선 넣기
		file.addSeparator();
		file.add(f4);
		// [색상] 메뉴에 메뉴 항목 등록
		color.add(c1);
		color.add(c2);
		color.add(c3);
		// [메뉴바]에 파일, 편집, 색상 메뉴 등록
		menuBar.add(file);
		menuBar.add(edit);
		menuBar.add(color);
		// 프레임에 JTextPane 등록   
		add(text);  
		// [프레임]에 메뉴바 등록
		setJMenuBar(menuBar);
		
		f1.addActionListener(this);
		f4.addActionListener(this);
	}

	// 이벤트 처리하기
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == f1)
			text.setText(null);
		else if (e.getSource() == f4) {
			this.dispose();
			//System.exit(0);
		}
	}

	void pop() {
		// 팦업 객체 생성
		popmn = new JPopupMenu();
		// 팦업 메뉴 객체 생성
		jmCopy = new JMenuItem("복사(C)");
		jmCut = new JMenuItem("잘라내기(X)");
		jmPaste = new JMenuItem("붙여넣기(V)");
		// 팦업 메뉴에 메뉴 항목 등록
		popmn.add(jmCopy);
		popmn.add(jmCut);
		popmn.addSeparator();
		popmn.add(jmPaste);
		// 텍스트에 팝업 메뉴 등록
		text.add(popmn);
		
		// 텍스트에서 마우스 오른쪽눌렀을 때 팦업창 뜨우기(익명으로 클래스 만들기)
		text.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) { // 마우스를 누르면				
				if(e.getButton()==3) // 마우스 버튼 3개 : 왼쪽, 휠, 오른쪽					
					popmn.show(text, e.getX(), e.getY());
					// 마우스의 좌표 값 getx() gety() 받음				
			}
		});
	}

	
	public static void main(String[] args) {
		new MenuPopupEvent2();
	}
}