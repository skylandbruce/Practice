 
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.StringWriter;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextPane;
import javax.swing.event.MouseInputAdapter;

import org.w3c.dom.events.MouseEvent;

public class Memo extends JFrame implements MouseEvent{
    JTextArea ta;
    JTextPane tp;
    File f;
    public Memo(String title) {
        setTitle(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JMenu mfile=new JMenu("파일");
        
        JMenuItem mOpen=new JMenuItem("열기");
        JMenuItem mNew=new JMenuItem("새파일");
        JMenuItem mSave=new JMenuItem("저장");
        JMenuItem mSaveAs=new JMenuItem("다른이름으로 저장");
        JMenuItem mExit=new JMenuItem("끝내기");
        
        mfile.add(mOpen);
        mfile.add(mNew);
        mfile.add(mSave);
        mfile.add(mSaveAs);
        mfile.addSeparator();
        mfile.add(mExit);
        
        // 편집
        JMenu mEdit=new JMenu("편집");
        
        JMenuItem mItem1=new JMenuItem("빨강");
        JMenuItem mItem2=new JMenuItem("파랑");
        
        mEdit.add(mItem1);
        mEdit.add(mItem2);
        // 색상
        JMenu mColor=new JMenu("색상");
        
        ButtonGroup group = new ButtonGroup();
        
        JMenuItem m_t_color=new JMenuItem("아이콘 보기");
        JRadioButton m_rd1=new JRadioButton("라디오1");
        JRadioButton m_rd2=new JRadioButton("라디오2");
        group.add(m_rd1);
        group.add(m_rd2);
        
        JMenuItem m_sub_t=new JMenuItem("서브메뉴");

        ImageIcon Image=new ImageIcon("D:\\Git\\JavaGUI\\ref\\1_talk.jpg");
        JCheckBox m_sub_check = new JCheckBox("체크박스");
		JCheckBox m_sub_image_check = new JCheckBox("이미지 체크", Image);
        m_sub_t.add(m_sub_check);
        // m_sub_t.add(m_sub_image_check);

        mColor.add(m_t_color);
        mColor.add(m_rd1);
        mColor.add(m_rd2);
        // mColor.add(m_sub_t);
        mColor.add(m_sub_image_check);
        mColor.add(m_sub_check);
        // m_t_color.addSeparator();



        
 /////////////메뉴바/////////////       
        JMenuBar mb=new JMenuBar();
        mb.add(mfile);
        mb.add(mEdit);
        mb.add(mColor);
        setJMenuBar(mb);
        
        // ta=new JTextArea();
        tp = new JTextPane();
//        JScrollPane scroll_pain=new JScrollPane(ta);
//        JScrollPane scroll_pain=new JScrollPane();
//        scroll_pain.setViewportView(ta);
//        add(ta);
        

        JPopupMenu pop_menu=new JPopupMenu();
        JMenuItem pop_m_copy=new JMenuItem("복사");
        JMenuItem pop_m_cut=new JMenuItem("잘라내기");
        JMenuItem pop_m_paste=new JMenuItem("붙혀넣기");
        pop_menu.add(pop_m_copy);
        pop_menu.add(pop_m_cut);
        pop_menu.add(pop_m_paste);
        tp.add(pop_menu);

        //add(scroll_pain);
        add(tp);


        //새파일
        mNew.addActionListener(new ActionListener() {
            
            public void actionPerformed(ActionEvent e) {
                ta.setText("");
                setTitle("제목없음");
            }
        });
        
        //열기 (선택된 파일을 읽어들이기. fileread)
        mOpen.addActionListener(new ActionListener() {
            
            public void actionPerformed(ActionEvent e) {
                JFileChooser fc=new JFileChooser();
                if(fc.showOpenDialog(Memo.this)==JFileChooser.CANCEL_OPTION)
                    return; //자신을 불러주는 부모창을 인수로함. Memo자기자신.
                f=fc.getSelectedFile(); //선택된 파일 
                setTitle(f.getName()); //선택된 파일의 이름 가져오기
                fileRead(f); //취소를 눌렀을경우 선택된 파일이 없기때문에 파일 읽어들이는 fileRead오류남
            }
        });
 
        //저장 (기존파일 없음=제목없음이면 새 창을 띄우기)
        mSave.addActionListener(new ActionListener() {
            
            public void actionPerformed(ActionEvent e) {
                if(getTitle().equals("제목없음")) { 
//                    JFileChooser fc=new JFileChooser();
//                    if(fc.showSaveDialog(Memo.this)==JFileChooser.CANCEL_OPTION)
//                        return;
//                    f=fc.getSelectedFile();
//                    fileSave(f);
//                    setTitle(f.getName());
                    mSaveAs.doClick(); //mSaveAs가 다시 실행되는 것과 같음.
                }else {    //기존파일 있음
                    fileSave(f);
                }
            }
        });
 
        //새이름 저장
        mSaveAs.addActionListener(new ActionListener() {
            
            public void actionPerformed(ActionEvent e) {
                JFileChooser fc=new JFileChooser();
                if(fc.showSaveDialog(Memo.this)==JFileChooser.CANCEL_OPTION)
                    return;
                f=fc.getSelectedFile();
//                System.out.println("파일 저장: "+f);
                fileSave(f);
                setTitle(f.getName());
            }
        });
        
        //끝내기
        mExit.addActionListener(new ActionListener() {
            
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
        
    
        final int MS_BUTTOM_PUSH =1;
        final int MS_BUTTOM_LEFT =2;
        final int MS_BUTTOM_RIGHT =3;

        // tp.addMouseListener(new MouseListener(){
        //     public void mousePressed(MouseEvent e){
        //         if(e.getButton()==MS_BUTTOM_RIGHT)
        //             pop_menu.show(tp, e.getX(), e.getY());
        //             //pop_menu.show();
        //     }
        // });
        
        setSize(500,400);
        setVisible(true);
        
    }
 
    public static void main(String[] args) {
        new Memo("제목없음");
    }
    
    //파일 읽기 메소드
    private void fileRead(File f) {
        try {
            FileReader fr=new FileReader(f);
            StringWriter sw=new StringWriter();
            while(true) {
                int ch=fr.read();
                if(ch==-1) break;
                sw.write(ch);
            }
            ta.setText(sw.toString());
            sw.close();
            fr.close();
        } catch (FileNotFoundException n) {
            n.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
 
    //파일 저장 메소드
    private void fileSave(File f) {
        try {
            PrintStream ps=new PrintStream(f);
            ps.println(ta.getText());
            ps.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
    }

    
}