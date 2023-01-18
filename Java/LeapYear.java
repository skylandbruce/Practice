import javax.swing.JOptionPane;

public class LeapYear {

	public LeapYear() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String TITLE0="연도를 입력 하시오\n종료는 0을 누르시오2";
		String str_num=null;
		int n_num=0;
		String str_year=null;
		//
		while(true){
		str_num=JOptionPane.showInputDialog(TITLE0);
		n_num=Integer.parseInt(str_num);
		if(n_num==0)break;
		
		str_year = (n_num%4==0 && n_num%100!=0 || n_num%400==0 )?"윤년":"평년";
		System.out.println(n_num+"년도는\t"+str_year);
		}
	}

}
