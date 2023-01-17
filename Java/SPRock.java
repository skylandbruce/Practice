import java.util.Random;
import java.util.Scanner;

public class SPRock {

	public SPRock() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {

		// TODO Auto-generated method stub

		final int SCISSORS = 1;
		final int PAPERS = 2;
		final int ROCK = 3;
		Random random = new Random();
		Scanner scanner = new Scanner(System.in);
		boolean go_stop = true;
		int man_num = 0;
		String man_str = null;
		int com_num = 0;
		String YorN = null;
		String F_R = null;
		do {
			while(go_stop) {
				System.out.print("가위 바위 보 입력:");
				man_str = scanner.next();
				
				switch (man_str) {
				case "가위":
					man_num = SCISSORS;
					go_stop=false;
					break;
				case "바위":
					man_num = PAPERS;
					go_stop=false;
					break;
				case "보":
					go_stop=false;
					man_num = ROCK;
					break;
				default:
					continue;
				}
				
			}

			

			System.out.println("사용자:"+man_str);

			System.out.println("컴퓨터가 가위 바위 보:");
			com_num = random.nextInt(3) + 1;

			// F_R=(com_num==1)? "앞":"뒤";
			//System.out.println("컴퓨터:" + F_R);

			switch (com_num) {
			case 1:
				F_R="가위";
				break;
			case 2:
				F_R="바위";
				break;
			case 3:
				F_R="보";
				break;
			default:
				continue;
			}
			System.out.println("컴퓨터:" + F_R);
			
			if (man_num == com_num) {
				System.out.println("무승부");
			} else {
				if (/* (man_num+2)==com_num || */ (man_num + 2) % 3 == com_num)
					System.out.println("사용자가 이겼습니다");
				else
					System.out.println("사용자가 졌습니다");
			}

			System.out.print("계속(Y)?:");
			YorN = scanner.next();

			if (YorN.equals("y"))
				go_stop = true;
			else
				go_stop = false;

		} while (go_stop);

	}
}
