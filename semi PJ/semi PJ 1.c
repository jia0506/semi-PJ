#include <stdio.h>
#include <windows.h> // �ܼ�â �ʱ�ȭ�� ���Ե� ���
#include <conio.h> // _getch�� ���Ե� ���
#define leapyear(year) ((year)%4==0 && ( (year)%100!=0 || (year)%400==0 )) //����������ũ�� 

void Start() {		//����ȭ��
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t Ƽ�Ͽ��� ��� \t\t\t\t\t");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t Ƽ�Ͽ��� Ȯ�� \t\t\t\t\t");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int input() {		// �Է¹��� ������ �� ���� 
	int num =2; //2���� ���� ����
	printf("��� �������� �Է��Ͻðڽ��ϱ�?");
	scanf_s("%d", &num);
	// �����Ҵ����� �迭 �ޱ�
	return num;
}

//typedef struct choice(int num, int *choice_day, choice *musical) {		// ������ �Է�
//	int choice_day;
//	char musical;
//	for (int i; i < num; i++) {
//		printf("�� �̸��� �Է��ϼ���.");
//		scanf_s("%c", &musical);
//		printf("��¥�� �Է��ϼ���.");
//		scanf_s("%d", &choice_day);
//	}
//
//	return 0;
//}

void Calendar() {
	int year, month; // ������ ���� ������ ���� 
	int month_total[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // �� ���� ���� �� (ù��° ���� ����) 
	int lastyear, day, i;

	printf("��� ����� �޷��� ����Ͻðڽ��ϱ�?: ");
	scanf_s("%d %d", &year, &month);

	if (month == 2 && leapyear(year)) // �ش�⵵�� �����̸�, 2���� �� 29�� 
		month_total[2] = 29;
	lastyear = year - 1; // �۳� ������ ����� ������ ����ϱ� ���� lastyear�� ���� 
	day = (lastyear + (lastyear / 4) - (lastyear / 100) + (lastyear / 400) + 1) % 7; /* lastyear : 1���� 365��, 1���� ���������� ������ �ѹ� �þ�� (365�� 7�� ������ 1�̱� ����) +(lastyear/4)-(lastyear/100)+(lastyear/400) : ������ ���������� ������ �ι� �þ�Ƿ�, lastyear���� �ִ� ��� ������ ���Ѵ� +1 : 1�� 1�� 1���� �Ͽ����� �ƴ϶� �������̹Ƿ� 1�� ���Ѵ� (0���� ����) %7 : ������ 7���� �̹Ƿ�, ���� ��갪�� 7�� ���� �������� year�� 1���� ù���� ���Ѵ� ���������� ���� 0:�Ͽ���, 1:������, 2:ȭ����, 3:������, 4:�����, 5:�ݿ���, 6:����� */

	for (i = 1;i < month;i++) // year�� month�� ���������� �� �� ���� ���ϱ� ���� for�� 
		day += month_total[i];
	day %= 7; // year�� month�� 1���� ���� ����
	printf("\n %d�� %d��\n", year, month); // year�� month�� Ÿ��Ʋ ��� 
	printf("\n	��	��	ȭ	��	��	��	��"); // ���� ����Ʈ ���

	for (i = -day;i < month_total[month];i++) {
		if ((i + day) % 7 == 0) // ��µ� ���ʰ� �Ͽ����̸�, ���� 
			printf("\n");
		if (i < 0) // month�� 1���� ��µǱ� ������ ��¥�� �������� ä�� 
			printf("	");
		else // ��¥ ��� 
			printf("	%d", i + 1);
	}
	printf("\n\n");
}
int main(void) { 
	Start();
	char c;
	int i, num ;
	c = _getch();
	if (c=72) {	// ���� ȭ��ǥ ����Ű Ŭ�� ��
		system("cls");
		num = input();
		//Choice();
		for (i = 0; i < num ; i++) {
			Calendar();
		}
	}
	else if (c=80){	// �Ʒ��� ȭ��ǥ ����Ű Ŭ�� ��
		system("cls");
		Calendar();
	}
	
	//\a //����� �Ҹ� �߻�
	return 0;
}
