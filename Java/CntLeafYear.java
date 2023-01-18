import java.util.Scanner;

public class CntLeafYear {

	public CntLeafYear() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String TITLE0 = "연도를 입력 하시오\n종료는 0을 누르시오2";
		String str_num = null;
		int year_curr = 0;
		String str_year = null;
		//
		System.out.println(TITLE0);
		Scanner scanner = new Scanner(System.in);
		year_curr = scanner.nextInt();
		int cnt_LeafYear = 0;
		int cnt_Week=0;
		final int NORMAL_YEAR=1;
		final int MONDAY=0;
		final int SUNDAY=6;
		final int MAX_WEEK=7;
		final int LEAF_NORMAL=4;
		final int YEAR_100=100;
		final int YEAR_400=400;
		final int DAY_OF_YEAR=365;
		int day_total=0;		
		int leaf_normal_cnt=0;
		int leaf_100_cnt=0;
		int leaf_400_cnt=0;
		int week_end=0;
		int week_sum=1;
		int next_week_end=0;
		//1년1월1일 은 월요일 
		//평년:365 윤년366
		//매달 1일의 요일은 전달까지의 일수%7
		//1월 1일이 월요일인 해는 해+=(평년 일%7+윤년 일)
						
		for (int check_year = 1; check_year <= year_curr; check_year++) {
			if (year_curr == 0)
				break;
			if(check_year % 4 == 0 && check_year % 100 != 0 || check_year % 400 == 0) {
				cnt_LeafYear++;
			// str_year = (year_curr%4==0 && year_curr%100!=0 || year_curr%400==0 )?"윤년":"평년";						
			}
			else {
				
			}
			//System.out.println(year_curr%LEAF_NORMAL);
			//System.out.println(year_curr%YEAR_100);
			//System.out.println(year_curr%YEAR_400);
			next_week_end = ((check_year%LEAF_NORMAL==0 && check_year%YEAR_100!=0) || check_year%YEAR_400==0 )? 2:1;
			week_sum+=next_week_end;
			//if(cnt_Week%MAX_WEEK==SUNDAY)
			//	System.out.println(check_year+": Next 1mon1day will be MONDAY ");
			if(week_sum%MAX_WEEK==SUNDAY)
				System.out.printf("%d년 1월 1일은 일요일 \n",check_year+1);
		}
		System.out.println("카운트 윤년"+cnt_LeafYear);
		System.out.println("마지막 요일:"+week_sum%MAX_WEEK);
		
		
		leaf_normal_cnt=year_curr/LEAF_NORMAL;
		leaf_100_cnt=year_curr/YEAR_100;
		leaf_400_cnt=year_curr/YEAR_400;
		cnt_LeafYear=(leaf_normal_cnt-leaf_100_cnt+leaf_400_cnt);
		day_total=year_curr*DAY_OF_YEAR+cnt_LeafYear;
		week_end=day_total%MAX_WEEK;
		System.out.println("계산 윤년"+cnt_LeafYear);
		System.out.println(year_curr+"년 마지막 요일:"+week_end);
		
				
		
	}

}
