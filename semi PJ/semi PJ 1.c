#include <stdio.h>
#include <windows.h> // �ܼ�â �ʱ�ȭ�� ���Ե� ���
#include <conio.h> // _getch�� ���Ե� ���
#include <stdlib.h> // �����Ҵ��� ���� ���
#include <string.h>
#define leapyear(year) ((year)%4==0 && ( (year)%100!=0 || (year)%400==0 )) //����������ũ�� 
#pragma warning(disable:4996)

int** Booking_office;		//����ó �ޱ� �����Ҵ�
char musical[50];
int choice_day;
int c = 0;
int year, month; // ������ ���� ������ ���� 
int count = 0;
int num;


void start(); // �Լ� ����
int input();
void calendar();
void AddNote();
void showNote();

void start() {		//����ȭ��
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t  Ƽ�Ͽ��� ��� (��) \t\t\t\t\t");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t  Ƽ�Ͽ��� Ȯ�� (��) \t\t\t\t\t");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int input() {		// �Է¹��� ������ �� ���� 
	printf("��� �������� �Է��Ͻðڽ��ϱ�?");
	scanf_s("%d", &num);
	//�����Ҵ����� �迭 �ޱ�
	return num;
}

void choice(int num) {		// ������ �Է�
	char booking_office[50];

	Booking_office = (int**)malloc(sizeof(int*) * num);
	for (int i = 0; i < num; i++)
		Booking_office[i] = (int*)malloc(sizeof(int) * 50);

	for (int i = 0; i < num; i++)
	{
		printf("��¥�� �Է��ϼ���.(DD)");
		scanf("%d", &choice_day);
		printf("�� �̸��� �Է��ϼ���.");
		scanf("%s", &musical);
		getchar();

		printf("����ó�� �Է��ϼ���\n (ex : ������ũ, ����24, Ƽ�ϸ�ũ, ���Ƽ��, ���Ե��þ���, ��츶�Ͼ�)\n");

		for (int j = 0; ; j++)		//���� ������ ����ó �ޱ�
		{
			printf("( %d ) : ", j + 1);
			scanf("%s", &booking_office);
			getchar();
			if (!strcmp("end", booking_office))		// ������ ���̱� ���� ���ڿ��� �ƴ� �迭�� ��ȯ 
				break;
			else if (!strcmp("������ũ", booking_office))
				Booking_office[i][j] = 1;
			else if (!strcmp("����24", booking_office))
				Booking_office[i][j] = 2;
			else if (!strcmp("Ƽ�ϸ�ũ", booking_office))
				Booking_office[i][j] = 3;
			else if (!strcmp("���Ƽ��", booking_office))
				Booking_office[i][j] = 4;
			else if (!strcmp("���Ե��þ���", booking_office))
				Booking_office[i][j] = 5;
			else if (!strcmp("��츶�Ͼ�", booking_office))
				Booking_office[i][j] = 6;
			count += 1;
		}
		AddNote();
		count = 0;
	}
}

void calendar() {
	int month_total[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // �� ���� ���� �� (ù��° ���� ����) 
	int lastyear, day, i;
	//FILE* file;

	printf("�⵵�� ���� �Է����ּ���.(YYYY MM): ");
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

	for (i = -day;i < month_total[month];i++) {			// ��µ� �޷��� ���� ���� �� ���߿� ��½ÿ��� �ѹ��� ����� �޷��� ��� ���� �޷��� ��ĥ��� ��¥ ���� ����
		if ((i + day) % 7 == 0) // ��µ� ���ʰ� �Ͽ����̸�, ���� 
			printf("\n");
		if (i < 0) // month�� 1���� ��µǱ� ������ ��¥�� �������� ä�� 
			printf("	");
		else // ��¥ ��� 
			printf("	%d", i + 1);
	}
	printf("\n\n");
	getchar();
}

void AddNote() {
	FILE* fp = fopen("note.txt", "a");
	system("cls");
	fprintf(fp, "%d/%d/%d\n:%s\n����ó (1:������ũ, 2:����24, 3:Ƽ�ϸ�ũ, 4:���Ƽ��, 5:���Ե��þ���, 6:��츶�Ͼ�)\n : ", year, month, choice_day, musical);
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
	FILE* fp = fopen("note.txt", "r");  //test������ r(�б�) ���� ����
	char buffer[1024] = { 0 };

	fread(buffer, 1, 1024, fp); //��ü �б�
	printf("%s", buffer);

	fclose(fp); //���� ������ �ݱ�
	getchar();
}


int main() {
	
	while (c != 27) { //esc ���������� �ݺ�
		start();
		c = _getch();
		int i, num, day;
		if (c == 72) {	// ���� ȭ��ǥ ����Ű Ŭ�� ��
			system("cls");
			calendar();
			num = input();
			choice(num);
			
			if (c = _getch(13)) {
				start();
			}
		}
		
		else if (c == 80) {	// �Ʒ��� ȭ��ǥ ����Ű Ŭ�� ��
			system("cls");
			calendar();
			showNote();
		}
	}
	return 0;
}
