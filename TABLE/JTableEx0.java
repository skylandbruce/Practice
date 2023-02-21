package TABLE;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

public class JTableEx0 extends JFrame{
    DefaultTableModel model;
    JTable table;
    JTable table2;
    JScrollPane jscroll_pane;
    public JTableEx0(){
        String[] colheading={"이름","주소","전화"};
        String[][] rowdata={ 
            {"박효신", "서울", "010-0000-0000"},
            {"김진호", "대구", "010-1111-1111"},
            {"마마무", "부산", "010-2222-2222"}
        };
        
        model=new DefaultTableModel(rowdata,colheading);    //1.자료 등록
        table=new JTable(model);                            //2.자료 구조 등록
        jscroll_pane=new JScrollPane(table);                //3.
        
        String[] newrow = {"알리", "대전", "101-4444-4444"};
        // table.addRow(newrow);
        
        model.addRow(newrow);
        // table2=new JTable(model);
        // jscroll_pane=new JScrollPane(table2);
        
        model.removeRow(2);
        // this.add(jscroll_pane);


        // model.addColumn(new_column);


        add("Center",jscroll_pane);
        setSize(450,400);
        setVisible(true);

        

    }
    public static void main(String[] args) {
        new JTableEx0();
    }
}
