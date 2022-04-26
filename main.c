
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
void gotoxy(int ,int );
void menu();
void add();
void view();
void search();
void modify();
void deleterec();
struct record
{
    char name[20];
    char mname[20];
    int cost;
    char tbill[20];
    char date[20];
};
int main()
{
    gotoxy(15,8);
    printf("<--:Medical Store Management System:-->");
    gotoxy(19,15);
    printf("Press any key to continue.");
    getch();
    menu();
    return 0;
}
void menu()
{
    int choice;
    system("cls");
    gotoxy(10,3);
    printf("<--:MENU:-->");
    gotoxy(10,5);
    printf("Enter appropriate number to perform following task.");
    gotoxy(10,7);
    printf("1 : Add New Sales.");
    gotoxy(10,8);
    printf("2 : View All Sales.");
    gotoxy(10,9);
    printf("3 : Search for Sales.");
    gotoxy(10,10);
    printf("4 : Modify Sales.");
    gotoxy(10,11);
    printf("5 : Delete Sales.");
    gotoxy(10,12);
    printf("6 : Exit.");
    gotoxy(10,15);
    printf("Enter your choice.");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        add();
        break;

    case 2:
        view();
        break;

    case 3:
        search();
        break;

    case 4:
        modify();
        break;

    case 5:
        deleterec();
        break;

    case 6:
        exit(1);
        break;

    default:
        gotoxy(10,17);
        printf("Invalid Choice.");
    }
}
void add()
{
    FILE *fp;
    struct record std;
    char another ='y';
    system("cls");

    fp = fopen("record.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(another == 'y')
    {
        gotoxy(10,3);
        printf("<--:ADD New Sale:-->");
        gotoxy(10,5);
        printf("Enter details of new Sale : ");
        gotoxy(10,7);
        printf("Enter name of medicine : ");
//        gets(std.name);///???
        gets(std.name);
        gotoxy(10,8);
        printf("Enter customer name : ");
        gets(std.mname);
        gotoxy(10,9);
        printf("Enter Cost of medicine : ");
        scanf("%d",&std.cost);
        fflush(stdin);
        gotoxy(10,10);
        printf("Enter total bill : ");
//        gets(std.course);///???
        gets(std.tbill);
        gotoxy(10,11);
        printf("Enter Date : ");
        gets(std.date);
//        gotoxy(10,12);
//        printf("Enter Father's Name : ");
//        gets(std.fathername);
        fwrite(&std,sizeof(std),1,fp);
        gotoxy(10,15);
        printf("Want to add of another sale? Then press 'y' else 'n'.");
        fflush(stdin);
//        another = getch();///???
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,18);
    printf("Press any key to continue.");
    getch();
    menu();
}
void view()
{
    FILE *fp;
    int i=1,j;
    struct record std;
    system("cls");
    gotoxy(10,3);
    printf("<--:ALL SALES:-->");
    gotoxy(10,5);
    printf("S.No   Name of Medicine       Customer    Cost    Total-Bill      Date");
    gotoxy(10,6);
    printf("-----------------------------------------------------------------------");
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error opening file.");
        exit(1);
    }
    j=8;
    while(fread(&std,sizeof(std),1,fp) == 1){
        gotoxy(10,j);
        printf("%-7d%-22s%-12s%-9d%-12s%-12s",i,std.name,std.mname,std.cost,std.tbill,std.date);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to continue.");
    getch();
    menu();
}
void search()
{
    FILE *fp;
    struct record std;
    char stname[20];
    system("cls");
    gotoxy(10,3);
    printf("<--:SEARCH SALE:-->");
    gotoxy(10,5);
    printf("Enter name of medicine : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp ) == 1){
        if(strcmp(stname,std.name) == 0){
            gotoxy(10,8);
            printf("Medicine : %s",std.name);
            gotoxy(10,9);
            printf("Customer : %s",std.mname);
            gotoxy(10,10);
            printf("Cost : %d",std.cost);
            gotoxy(10,11);
            printf("Total-Bill : %s",std.tbill);
            gotoxy(10,12);
            printf("Date : %s",std.date);
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Press any key to continue.");
    getch();
    menu();
}
void modify()
{
    char stname[20];
    FILE *fp;
    struct record std;
    system("cls");
    gotoxy(10,3);
    printf("<--:MODIFY SALE:-->");
    gotoxy(10,5);
    printf("Enter medicine to modify: ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while(fread(&std,sizeof(std),1,fp) == 1)
    {
        if(strcmp(stname,std.name) == 0){
            gotoxy(10,7);
            printf("Enter medicine name: ");
            gets(std.name);
            gotoxy(10,8);
            printf("Enter customer name : ");
            gets(std.mname);
            gotoxy(10,9);
            printf("Enter Cost : ");
            scanf("%d",&std.cost);
            gotoxy(10,10);
            printf("Enter Total Bill : ");
            fflush(stdin);
            gets(std.tbill);
            gotoxy(10,11);
            printf("Enter date : ");
            fflush(stdin);
            gets(std.date);
            fseek(fp ,-sizeof(std),SEEK_CUR);
            fwrite(&std,sizeof(std),1,fp);
            break;
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Press any key to continue.");
    getch();
    menu();
}
void deleterec()
{
    char stname[20];
    FILE *fp,*ft;
    struct record std;
    system("cls");
    gotoxy(10,3);
    printf("<--:DELETE SALE:-->");
    gotoxy(10,5);
    printf("Enter name of medicine to delete record : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    ft = fopen("temp.txt","wb+");
    if(ft == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp) == 1){
        if(strcmp(stname,std.name)!=0)
            fwrite(&std,sizeof(std),1,ft);
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(10,10);
    printf("Press any key to continue.");
    getch();
    menu();
}
void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}