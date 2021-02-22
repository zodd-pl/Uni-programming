#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#define white 7
#define red 12
#define yellow 14
#define green 10
#define grey 8

struct T_Towar{
    char  name [20];
    float price;
    int quantity;
    char unit [10];
};

void Menu(T_Towar* &arg_1, int &arg_2);
void ReadObject(T_Towar & object, int number);
void AddObject(T_Towar * & table_pointer ,int & size);
void DelObjectPos(T_Towar * & table_pointer ,int & size);
void PrintObject(T_Towar object, int number);
void PrintError(int error_code);
void PrintAuthor();
void PrintTable(T_Towar *  table_pointer ,int  size);
void PrintSelected(T_Towar *  table_pointer ,int  size);
void InitNewTab(T_Towar * & table_pointer ,int & size);
void DelTab(T_Towar * & table_pointer ,int & size);

int main()
{
    /*
        Autor:  Kacper Aleks
        Grupa:  CZ/NP 12:15     (Czwartek nieparzysty godz 12:15)
        Temat:  program - lab 6
        Data ostatniej modyfikacji  14.01.21 12.55
    */

    T_Towar * table;
    table = nullptr;
    int table_size=0;
    while(true) Menu(table, table_size);
    return 0;
}

void Menu( T_Towar* &arg_1, int &arg_2)
{
    PrintAuthor();
    printf("Adres poczatku tablicy: %d\nAktualny rozmiar: %d\n", arg_1, arg_2);
    printf("\n\n");
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), green);
    printf("Welcome to the program that immitates a paper shoppping list!\n");
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), yellow);
    printf("[1] Create new table\n[2] Delete table\n[3] Add one object \n[4] Delete object at certain position\n[5] Print table \n[6] Print selected objects\nExit [K]\n");
    fflush(stdin);
    char c=getch();
    switch(c){
        case '1':
        system("cls");
        InitNewTab(arg_1, arg_2);
        break;

        case '2':
        system("cls");
        DelTab(arg_1, arg_2);
        break;

        case '3':
        system("cls");
        AddObject(arg_1, arg_2);
        break;

        case '4':
        system("cls");
        DelObjectPos(arg_1, arg_2);
        break;

        case '5':
        system("cls");
        PrintTable(arg_1, arg_2);
        system("Pause");
        break;

        case '6':
        system("cls");
        PrintSelected(arg_1, arg_2);
        system("Pause");
        break;

        case 'k':
        return ;

        case 'K':
        return ;

        default:
        PrintError(0);
    }
    
}
void ReadObject(T_Towar & object, int number)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), green );
    printf("You are currently entering data for object number [%d]:\n", number);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), yellow );
    printf("[%d] Enter object's name: ", number);
    scanf("%s", &object.name);
    printf("[%d] Enter object's price: ", number);
    scanf("%f", &object.price);
    printf("[%d] Enter object's quantity: ", number);
    scanf("%d", &object.quantity);
    printf("[%d] Enter measurement unit: ", number);
    scanf("%s", &object.unit);
}
void AddObject(T_Towar * & table_pointer, int & size)
{
    size ++;
    table_pointer= (T_Towar *) realloc(table_pointer ,sizeof(T_Towar)*size);
    ReadObject(table_pointer[size-1], size);
}
void DelObjectPos(T_Towar * & table_pointer, int & size)
{
    int pos;
    if(table_pointer == nullptr) {
        PrintError(1);
        return;
    }
    while(true){
        PrintTable(table_pointer,size);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),yellow);
        printf("\nWhat position should be deleted? [wpisz \'0\' aby wyjsc]: ");
        fflush(stdin);
        scanf("%d", &pos); 
        if(pos == 0) return;
        if(pos-1>= size || pos -1<0)  PrintError(0);
        else break;
    }
    for(int i =pos -1 ; i < size ; i++) table_pointer[i] = table_pointer[i+1];
    free(table_pointer + pos);
    if(size == 1) {  
        table_pointer =  nullptr;
        size = 0;
    }
    else {
        table_pointer= (T_Towar*)realloc(table_pointer,sizeof(T_Towar)*size);
        size --;
    }
}
void PrintObject(T_Towar object, int number)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), grey);
    printf("Object number [%d]:\n",number);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), white );
    printf("Name: %s;\t\t", object.name);
    printf("Price: %f ;\t", object.price);
    printf("Quantity: %d;\t", object.quantity);
    printf("Measurement unit: %s;\n", object.unit);
}
void PrintError(int error_code)
{
    char errors [2] [30];
    strcpy(errors[0], "Wrong number!");
    strcpy(errors[1], "There are no objects!");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
    printf("%s\n", errors[error_code]);
    Sleep(1000);
    system("cls");
}
void PrintAuthor()
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), white );
    system("cls");
    printf( "Author: Kacper Aleks (CZ/NP 12:15) \n\n") ;
}
void PrintTable(T_Towar *  table_pointer, int  size)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), red);
    if(table_pointer == NULL) PrintError(1);
    else{
        float sum=0;
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), green);
        printf("Current shopping list\n");
        for(int i=0;i<size;i++){
            PrintObject(table_pointer[i], i+1);
        }
        printf("\t\t\t\t\t\tTotal sum is: %f;\n", sum);
    }
}
void PrintSelected(T_Towar *  table_pointer, int  size)
{
    if(table_pointer == NULL) {
        PrintError(1);
        return;
    }
    printf("Welcome to the condition printing creator!\n\n");
    while(true){
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
        printf("[0] Exit\n[1] Show objects which price is lower than n\n[2] Show objects which price is higher or even to n\n[3] Show objects with certain name\n[4] Show objects that start with certain letter\n[5] Show objects which quantity is lower than n\n[6] Show objects which quantity is lower or even to n\n");
        fflush(stdin);
        char choice = getch();
        switch(choice){
            case '1':
            float n;
            system("cls");
            printf("Enter n: ");
            scanf("%f",&n);
            for(int i=0;i<size;i++){
                if(table_pointer[i].price < n){
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;
            
            case '2':
            float  k;
            system("cls");
            printf("Enter n: ");
            scanf("%f",&k);
            for(int i=0;i<size;i++){
                if(table_pointer[i].price >= k){
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;

            case '3':
            char word [81];
            system("cls");
            printf("Enter name: ");
            scanf("%s",&word);
            for(int i=0;i<size;i++){
                if(strcmp(table_pointer[i].name,word) == 0){
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;

            case '4':
            char letter;
            system("cls");
            printf("Enter first letter: ");
            scanf("%c",&letter);
            for(int i=0;i<size;i++){
                if(table_pointer[i].name[0] == letter) {
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;

            case '5':
            int l;
            system("cls");
            printf("Enter n: ");
            scanf("%d",&l);
            for(int i=0;i<size;i++){
                if(table_pointer[i].quantity < l){
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;

            case '6':
            int m;
            system("cls");
            printf("Enter n: ");
            scanf("%d",&m);
            for(int i = 0 ;i < size; i++){
                if(table_pointer[i].quantity >= m){
                    PrintObject(table_pointer[i], i+1);
                }
            }
            system("Pause");
            break;

            case '0':
            return;

            default:
            PrintError(0);
        }
    }
}   
void InitNewTab(T_Towar * & table_pointer, int & size)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), yellow );
    if(table_pointer != nullptr)  DelTab(table_pointer, size);
    printf("Enter the table size: ");
    scanf("%d", &size);
    if(size == 0) table_pointer = nullptr;
    else {
        do{
            table_pointer= (T_Towar *) malloc(sizeof(T_Towar)*size);
        } while( table_pointer == nullptr );
    }

    for(int i=0;i<size;i++){
        ReadObject(table_pointer[i], i+1);
    }
}
void DelTab(T_Towar * & table_pointer, int & size)
{
    if(table_pointer != nullptr){
        free(table_pointer);
        size = 0;
        table_pointer = nullptr;
    }
    else  PrintError(1);
}