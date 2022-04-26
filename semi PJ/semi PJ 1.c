#include <stdio.h>
#include <windows.h> // 콘솔창 초기화가 포함되 헤더
#include <conio.h> // _getch가 포함된 헤더
#include <stdlib.h> // 동적할당을 위한 헤더
#include <string.h>
#define leapyear(year) ((year)%4==0 && ( (year)%100!=0 || (year)%400==0 )) //윤년판정매크로 
#pragma warning(disable:4996)

int** Booking_office;		//예매처 받기 동적할당
char musical[50];
int choice_day;
int c = 0;
int year, month; // 연도와 월을 저장할 변수 
int count = 0;
int num;


void start(); // 함수 선언
int input();
void calendar();
void AddNote();
void showNote();

void start() {		//시작화면
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t  티켓오픈 등록 (↑) \t\t\t\t\t");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t  티켓오픈 확인 (↓) \t\t\t\t\t");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int input() {		// 입력받을 뮤지컬 수 설정 
	printf("몇개의 스케줄을 입력하시겠습니까?");
	scanf_s("%d", &num);
	//동적할당으로 배열 받기
	return num;
}

void choice(int num) {		// 스케줄 입력
	char booking_office[50];

	Booking_office = (int**)malloc(sizeof(int*) * num);
	for (int i = 0; i < num; i++)
		Booking_office[i] = (int*)malloc(sizeof(int) * 50);

	for (int i = 0; i < num; i++)
	{
		printf("날짜를 입력하세요.(DD)");
		scanf("%d", &choice_day);
		printf("극 이름을 입력하세요.");
		scanf("%s", &musical);
		getchar();

		printf("예매처를 입력하세요\n (ex : 인터파크, 예스24, 티켓링크, 멜론티켓, 샤롯데시어터, 헤븐마니아)\n");

		for (int j = 0; ; j++)		//무한 루프로 예매처 받기
		{
			printf("( %d ) : ", j + 1);
			scanf("%s", &booking_office);
			getchar();
			if (!strcmp("end", booking_office))		// 차수를 줄이기 위해 문자열이 아닌 배열로 변환 
				break;
			else if (!strcmp("인터파크", booking_office))
				Booking_office[i][j] = 1;
			else if (!strcmp("예스24", booking_office))
				Booking_office[i][j] = 2;
			else if (!strcmp("티켓링크", booking_office))
				Booking_office[i][j] = 3;
			else if (!strcmp("멜론티켓", booking_office))
				Booking_office[i][j] = 4;
			else if (!strcmp("샤롯데시어터", booking_office))
				Booking_office[i][j] = 5;
			else if (!strcmp("헤븐마니아", booking_office))
				Booking_office[i][j] = 6;
			count += 1;
		}
		AddNote();
		count = 0;
	}
}

void calendar() {
	int month_total[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // 각 달의 총일 수 (첫번째 수는 제외) 
	int lastyear, day, i;
	//FILE* file;

	printf("년도와 월을 입력해주세요.(YYYY MM): ");
	scanf_s("%d %d", &year, &month);

	if (month == 2 && leapyear(year)) // 해당년도가 윤년이면, 2월은 총 29일 
		month_total[2] = 29;
	lastyear = year - 1; // 작년 말까지 진행된 요일을 계산하기 위해 lastyear를 선언 
	day = (lastyear + (lastyear / 4) - (lastyear / 100) + (lastyear / 400) + 1) % 7; /* lastyear : 1년은 365일, 1년이 지날때마다 요일이 한번 늘어난다 (365를 7로 나누면 1이기 때문) +(lastyear/4)-(lastyear/100)+(lastyear/400) : 윤년의 다음연도는 요일이 두번 늘어므로, lastyear까지 있던 모든 윤년을 더한다 +1 : 1년 1월 1일은 일요일이 아니라 월요일이므로 1을 더한다 (0년은 없다) %7 : 요일은 7가지 이므로, 앞의 계산값을 7로 나눈 나머지가 year년 1월의 첫요일 뜻한다 나머지값에 따라 0:일요일, 1:월요일, 2:화요일, 3:수요일, 4:목요일, 5:금요일, 6:토요일 */

	for (i = 1;i < month;i++) // year년 month월 직전까지의 총 일 수를 구하기 위한 for문 
		day += month_total[i];
	day %= 7; // year년 month월 1일의 시작 요일
	printf("\n %d년 %d월\n", year, month); // year년 month월 타이틀 출력 
	printf("\n	일	월	화	수	목	금	토"); // 요일 리스트 출력

	for (i = -day;i < month_total[month];i++) {			// 출력된 달력을 동시 저장 후 나중에 출력시에는 한번에 저장된 달력이 출력 만약 달력이 겹칠경우 날짜 색만 변경
		if ((i + day) % 7 == 0) // 출력될 차례가 일요일이면, 개행 
			printf("\n");
		if (i < 0) // month월 1일이 출력되기 이전의 날짜는 공백으로 채움 
			printf("	");
		else // 날짜 출력 
			printf("	%d", i + 1);
	}
	printf("\n\n");
	getchar();
}

void AddNote() {
	FILE* fp = fopen("note.txt", "a");
	system("cls");
	fprintf(fp, "%d/%d/%d\n:%s\n예매처 (1:인터파크, 2:예스24, 3:티켓링크, 4:멜론티켓, 5:샤롯데시어터, 6:헤븐마니아)\n : ", year, month, choice_day, musical);
	for (int i = 0;i < num;i++) {
		for (int j = 0;j < count;j++) {
			fprintf(fp, "%d ", Booking_office[i][j]);
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}

void showNote() {
	FILE* fp = fopen("note.txt", "r");  //test파일을 r(읽기) 모드로 열기
	char buffer[1024] = { 0 };

	fread(buffer, 1, 1024, fp); //전체 읽기
	printf("%s", buffer);

	fclose(fp); //파일 포인터 닫기
	getchar();
}


int main() {
	
	while (c != 27) { //esc 선택전까지 반복
		start();
		c = _getch();
		int i, num, day;
		if (c == 72) {	// 위쪽 화살표 방향키 클릭 시
			system("cls");
			calendar();
			num = input();
			choice(num);
			
			if (c = _getch(13)) {
				start();
			}
		}
		
		else if (c == 80) {	// 아래쪽 화살표 방향키 클릭 시
			system("cls");
			calendar();
			showNote();
		}
	}
	return 0;
}
