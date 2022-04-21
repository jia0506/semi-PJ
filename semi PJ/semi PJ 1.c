#include <stdio.h>
#include <windows.h> // 콘솔창 초기화가 포함되 헤더
#include <conio.h> // _getch가 포함된 헤더
#define leapyear(year) ((year)%4==0 && ( (year)%100!=0 || (year)%400==0 )) //윤년판정매크로 

void Start() {		//시작화면
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t 티켓오픈 등록 \t\t\t\t\t");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t 티켓오픈 확인 \t\t\t\t\t");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int input() {		// 입력받을 뮤지컬 수 설정 
	int num =2; //2개로 임의 설정
	printf("몇개의 스케줄을 입력하시겠습니까?");
	scanf_s("%d", &num);
	// 동적할당으로 배열 받기
	return num;
}

//typedef struct choice(int num, int *choice_day, choice *musical) {		// 스케줄 입력
//	int choice_day;
//	char musical;
//	for (int i; i < num; i++) {
//		printf("극 이름을 입력하세요.");
//		scanf_s("%c", &musical);
//		printf("날짜를 입력하세요.");
//		scanf_s("%d", &choice_day);
//	}
//
//	return 0;
//}

void Calendar() {
	int year, month; // 연도와 월을 저장할 변수 
	int month_total[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // 각 달의 총일 수 (첫번째 수는 제외) 
	int lastyear, day, i;

	printf("몇년 몇월의 달력을 출력하시겠습니까?: ");
	scanf_s("%d %d", &year, &month);

	if (month == 2 && leapyear(year)) // 해당년도가 윤년이면, 2월은 총 29일 
		month_total[2] = 29;
	lastyear = year - 1; // 작년 말까지 진행된 요일을 계산하기 위해 lastyear를 선언 
	day = (lastyear + (lastyear / 4) - (lastyear / 100) + (lastyear / 400) + 1) % 7; /* lastyear : 1년은 365일, 1년이 지날때마다 요일이 한번 늘어난다 (365를 7로 나누면 1이기 때문) +(lastyear/4)-(lastyear/100)+(lastyear/400) : 윤년의 다음연도는 요일이 두번 늘어므로, lastyear까지 있던 모든 윤년을 더한다 +1 : 1년 1월 1일은 일요일이 아니라 월요일이므로 1을 더한다 (0년은 없다) %7 : 요일은 7가지 이므로, 앞의 계산값을 7로 나눈 나머지가 year년 1월의 첫요일 뜻한다 나머지값에 따라 0:일요일, 1:월요일, 2:화요일, 3:수요일, 4:목요일, 5:금요일, 6:토요일 */

	for (i = 1;i < month;i++) // year년 month월 직전까지의 총 일 수를 구하기 위한 for문 
		day += month_total[i];
	day %= 7; // year년 month월 1일의 시작 요일
	printf("\n %d년 %d일\n", year, month); // year년 month월 타이틀 출력 
	printf("\n	일	월	화	수	목	금	토"); // 요일 리스트 출력

	for (i = -day;i < month_total[month];i++) {
		if ((i + day) % 7 == 0) // 출력될 차례가 일요일이면, 개행 
			printf("\n");
		if (i < 0) // month월 1일이 출력되기 이전의 날짜는 공백으로 채움 
			printf("	");
		else // 날짜 출력 
			printf("	%d", i + 1);
	}
	printf("\n\n");
}
int main(void) { 
	Start();
	char c;
	int i, num ;
	c = _getch();
	if (c=72) {	// 위쪽 화살표 방향키 클릭 시
		system("cls");
		num = input();
		//Choice();
		for (i = 0; i < num ; i++) {
			Calendar();
		}
	}
	else if (c=80){	// 아래쪽 화살표 방향키 클릭 시
		system("cls");
		Calendar();
	}
	
	//\a //경고음 소리 발생
	return 0;
}
