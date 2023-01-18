
public class Minority {

	public Minority() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int num_in=100;
		int cnt_column=0;
		boolean b_minor=true;
		for(int num_test=1; num_test<=num_in; num_test++) {
			++cnt_column;
			for(int i=2; i<num_test&&num_test!=1; i++) {
				if(num_test%i==0) { //소수 아님
					b_minor=false;
					break;
				}
				else {//소수
					b_minor=true;
				}
			}
			if(b_minor&&num_test!=1)
				System.out.printf("%4d*",num_test);
			else
				System.out.printf("%4d ",num_test);
			if(cnt_column%10==0)
				System.out.print("\n");
		}

	}

}
