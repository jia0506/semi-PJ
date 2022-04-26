#include<stdio.h>
#include<conio.h>
#include<windows.h>

struct date {
    int dd;
    int mm;
    int yy;
};
struct date date;

struct remainder {
    int dd;
    int mm;
    char note[50];
};
struct remainder r;


coord xy = { 0, 0 };

void gotoxy(int x, int y)
{
    xy.x = x; xy.y = y; // x and y coordinates
    setconsolecursorposition(getstdhandle(std_output_handle), xy);
}

this will set the forground color for printing in a console window.
void setcolor(int forgc)
{
    word wcolor;
    we will need this handle to get the current background attribute
    handle hstdout = getstdhandle(std_output_handle);
    console_screen_buffer_info csbi;

    we use csbi for the wattributes word.
    if (getconsolescreenbufferinfo(hstdout, &csbi))
    {
        mask out all but the background attribute, and add in the forgournd color
        wcolor = (csbi.wattributes & 0xf0) + (forgc & 0x0f);
        setconsoletextattribute(hstdout, wcolor);
    }
    return;
}

void clearcolor() {
    setcolor(15);
}

void clearconsoletocolors(int forgc, int backc)
{
    word wcolor = ((backc & 0x0f) << 4) + (forgc & 0x0f);
    get the handle to the current output buffer...
    handle hstdout = getstdhandle(std_output_handle);
    this is used to reset the carat/cursor to the top left.
    coord coord = { 0, 0 };
    a return value... indicating how many chars were written
       not used but we need to capture this since it will be
       written anyway (passing null causes an access violation).
    dword count;

    this is a structure containing all of the console info
     it is used here to find the size of the console.
    console_screen_buffer_info csbi;
    here we will set the current color
    setconsoletextattribute(hstdout, wcolor);
    if (getconsolescreenbufferinfo(hstdout, &csbi))
    {
        this fills the buffer with a given character (in this case 32=space).
        fillconsoleoutputcharacter(hstdout, (tchar)32, csbi.dwsize.x * csbi.dwsize.y, coord, &count);

        fillconsoleoutputattribute(hstdout, csbi.wattributes, csbi.dwsize.x * csbi.dwsize.y, coord, &count);
        this will set our cursor position for the next print statement.
        setconsolecursorposition(hstdout, coord);
    }
    return;
}

void setcolorandbackground(int forgc, int backc)
{
    word wcolor = ((backc & 0x0f) << 4) + (forgc & 0x0f);;
    setconsoletextattribute(getstdhandle(std_output_handle), wcolor);
    return;
}

int check_leapyear(int year) { //checks whether the year passed is leap year or not
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

void increase_month(int* mm, int* yy) { //increase the month by one
    ++* mm;
    if (*mm > 12) {
        ++* yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int* mm, int* yy) { //decrease the month by one
    --* mm;
    if (*mm < 1) {
        --* yy;
        if (*yy < 1600) {
            printf("no record available");
            return;
        }
        *mm = *mm + 12;
    }
}


int getnumberofdays(int month, int year) { //returns the number of days in given month
    switch (month) {                          //and year
    case 1: return(31);
    case 2: if (check_leapyear(year) == 1)
        return(29);
          else
        return(28);
    case 3: return(31);
    case 4: return(30);
    case 5: return(31);
    case 6: return(30);
    case 7: return(31);
    case 8: return(31);
    case 9: return(30);
    case 10: return(31);
    case 11: return(30);
    case 12: return(31);
    default: return(-1);
    }
}

char* getname(int day) { //returns the name of the day
    switch (day) {
    case 0:return("sunday");
    case 1:return("monday");
    case 2:return("tuesday");
    case 3:return("wednesday");
    case 4:return("thursday");
    case 5:return("friday");
    case 6:return("saturday");
    default:return("error in getname() module.invalid argument passed");
    }
}

void print_date(int mm, int yy) { //prints the name of month and year
    printf("---------------------------\n");
    gotoxy(25, 6);
    switch (mm) {
    case 1: printf("january"); break;
    case 2: printf("february"); break;
    case 3: printf("march"); break;
    case 4: printf("april"); break;
    case 5: printf("may"); break;
    case 6: printf("june"); break;
    case 7: printf("july"); break;
    case 8: printf("august"); break;
    case 9: printf("september"); break;
    case 10: printf("october"); break;
    case 11: printf("november"); break;
    case 12: printf("december"); break;
    }
    printf(" , %d", yy);
    gotoxy(20, 7);
    printf("---------------------------");
}
int getdaynumber(int day, int mon, int year) { //retuns the day number
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while (year >= 100) {
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    t1 = (t1 % 7);
    res = res + t1;
    res = res % 7;
    t2 = 0;
    for (t1 = 1;t1 < mon; t1++) {
        t2 += getnumberofdays(t1, y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if (y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

char* getday(int dd, int mm, int yy) {
    int day;
    if (!(mm >= 1 && mm <= 12)) {
        return("invalid month value");
    }
    if (!(dd >= 1 && dd <= getnumberofdays(mm, yy))) {
        return("invalid date");
    }
    if (yy >= 1600) {
        day = getdaynumber(dd, mm, yy);
        day = day % 7;
        return(getname(day));
    }
    else {
        return("please give year more than 1600");
    }
}

int checknote(int dd, int mm) {
    file* fp;
    fp = fopen("note.dat", "rb");
    if (fp == null) {
        printf("error in opening the file");
    }
    while (fread(&r, sizeof(r), 1, fp) == 1) {
        if (r.dd == dd && r.mm == mm) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printmonth(int mon, int year, int x, int y) { //prints the month with all days
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isnote = 0;
    if (!(mon >= 1 && mon <= 12)) {
        printf("invalid month");
        getch();
        return;
    }
    if (!(year >= 1600)) {
        printf("invalid year");
        getch();
        return;
    }
    gotoxy(20, y);
    print_date(mon, year);
    y += 3;
    gotoxy(x, y);
    printf("s   m   t   w   t   f   s   ");
    y++;
    nod = getnumberofdays(mon, year);
    day = getdaynumber(d, mon, year);
    switch (day) { //locates the starting day in calender
    case 0:
        x = x;
        cnt = 1;
        break;
    case 1:
        x = x + 4;
        cnt = 2;
        break;
    case 2:
        x = x + 8;
        cnt = 3;
        break;
    case 3:
        x = x + 12;
        cnt = 4;
        break;
    case 4:
        x = x + 16;
        cnt = 5;
        break;
    case 5:
        x = x + 20;
        cnt = 6;
        break;
    case 6:
        x = x + 24;
        cnt = 7;
        break;
    default:
        printf("invalid data from the getoddnumber()module");
        return;
    }
    gotoxy(x, y);
    if (cnt == 1) {
        setcolor(12);
    }
    if (checknote(d, mon) == 1) {
        setcolorandbackground(15, 12);
    }
    printf("%02d", d);
    setcolorandbackground(15, 1);
    for (d = 2;d <= nod;d++) {
        if (cnt % 7 == 0) {
            y++;
            cnt = 0;
            x = x1 - 4;
        }
        x = x + 4;
        cnt++;
        gotoxy(x, y);
        if (cnt == 1) {
            setcolor(12);
        }
        else {
            clearcolor();
        }
        if (checknote(d, mon) == 1) {
            setcolorandbackground(15, 12);
        }
        printf("%02d", d);
        setcolorandbackground(15, 1);
    }
    gotoxy(8, y + 2);
    setcolor(14);
    printf("press 'n'  to next, press 'p' to previous and 'q' to quit");
    gotoxy(8, y + 3);
    printf("red background indicates the note, press 's' to see note: ");
    clearcolor();
}

void addnote() {
    file* fp;
    fp = fopen("note.dat", "ab+");
    system("cls");
    gotoxy(5, 7);
    printf("enter the date(dd/mm): ");
    scanf("%d%d", &r.dd, &r.mm);
    gotoxy(5, 8);
    printf("enter the note(50 character max): ");
    fflush(stdin);
    scanf("%[^\n]", r.note);
    if (fwrite(&r, sizeof(r), 1, fp)) {
        gotoxy(5, 12);
        puts("note is saved sucessfully");
        fclose(fp);
    }
    else {
        gotoxy(5, 12);
        setcolor(12);
        puts("\afail to save!!\a");
        clearcolor();
    }
    gotoxy(5, 15);
    printf("press any key............");
    getch();
    fclose(fp);
}

void shownote(int mm) {
    file* fp;
    int i = 0, isfound = 0;
    system("cls");
    fp = fopen("note.dat", "rb");
    if (fp == null) {
        printf("error in opening the file");
    }
    while (fread(&r, sizeof(r), 1, fp) == 1) {
        if (r.mm == mm) {
            gotoxy(10, 5 + i);
            printf("note %d day = %d: %s", i + 1, r.dd, r.note);
            isfound = 1;
            i++;
        }
    }
    if (isfound == 0) {
        gotoxy(10, 5);
        printf("this month contains no note");
    }
    gotoxy(10, 7 + i);
    printf("press any key to back.......");
    getch();

}

int main() {
    clearconsoletocolors(15, 1);
    int choice;
    char ch = 'a';
    while (1) {
        system("cls");
        printf("1. find out the day\n");
        printf("2. print all the day of month\n");
        printf("3. add note\n");
        printf("4. exit\n");
        printf("enter your choice : ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
        case 1:
            printf("enter date (dd mm yyyy) : ");
            scanf("%d %d %d", &date.dd, &date.mm, &date.yy);
            printf("day is : %s", getday(date.dd, date.mm, date.yy));
            printf("\npress any key to continue......");
            getch();
            break;
        case 2:
            printf("enter month and year (mm yyyy) : ");
            scanf("%d %d", &date.mm, &date.yy);
            system("cls");
            while (ch != 'q') {
                printmonth(date.mm, date.yy, 20, 5);
                ch = getch();
                if (ch == 'n') {
                    increase_month(&date.mm, &date.yy);
                    system("cls");
                    printmonth(date.mm, date.yy, 20, 5);
                }
                else if (ch == 'p') {
                    decrease_month(&date.mm, &date.yy);
                    system("cls");
                    printmonth(date.mm, date.yy, 20, 5);
                }
                else if (ch == 's') {
                    shownote(date.mm);
                    system("cls");
                }
            }
            break;
        case 3:
            addnote();
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}