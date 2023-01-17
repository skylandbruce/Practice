import java.util.Random;
import java.util.Scanner;

public class HighLowGame {

	public HighLowGame() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final int MAX_NUM=100;
		final int MIN_NUM=1;
		Random random = new Random();
		Scanner scanner = new Scanner(System.in);
		boolean go_stop = true;
		int man_num = 0;
		int com_num = 0;
		String YorN = null;
		String F_R = null;
		do{
			
			com_num = random.nextInt(100) + 1;
			System.out.println("랜덤수:"+com_num);
			
			int n_cnt=0;
			int max=MAX_NUM;
			int min=MIN_NUM;
			
			System.out.print("숫자 입력:");
			man_num = scanner.nextInt();
		
			do{
				++n_cnt;
					
				if(man_num==com_num) {
					System.out.printf("%d만에 맞춤\n",n_cnt);
					break;
				}
				else if(man_num>com_num && man_num<=max) {
					max=man_num-1;
				}
				else if(man_num<com_num && man_num>=min) {
					min=man_num+1;
				}
				else {
					System.out.println("범위 밖");
				}
				System.out.printf("%d~%d사이 숫자:",min,max);
				man_num = scanner.nextInt();
			}while(go_stop);

			System.out.print("계속(Y)?:");
			YorN = scanner.next();

			if (YorN.equalsIgnoreCase("y"))
				go_stop = true;
			else
				go_stop = false;

		} while (go_stop);

	}

}
