#include <cstdio>
#include<iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

struct Object{
    std::string name;
    float price;
    float quantity;
    std::string unit ;
};
enum class Colors{
    white = 7,
    red  =12,
    yellow =14,
    grey = 8,
    green = 11,
};
enum class Err_lab{
    mem = 2,
    no_obj = 1,
    wrong_pos = 0
};

inline void ChangeColor(Colors color)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), int(color));
}
void PrintError(Err_lab error_code)
{
    std::string errors [3] ;
    errors[0] =  "Wrong number!";
    errors[1] = "There are no objects!";
    errors[2] = "There is no memory left :(";
    ChangeColor(Colors::red);
    std::cout <<  errors[int(error_code)] << "\n";
    Sleep(1000);
    system("cls");
}
bool CmpAtr(std::string atribute, Object object, char operation)
{
    if(atribute == "name" ){
        if(operation == '='){
            std::string tmp;
            printf("Enter x: ");
            std::cin >> tmp;
            if(object.name == tmp) return true;
            else return false;
        }
        else {
            char tmpc;
            printf("Enter x: ");
            std::cin >> tmpc;
            if(object.name[0] == tmpc) return true;
            else return false;
        }
    }
    if(atribute == "price")
    {
        float tmpf;
        printf("Enter x: ");
        scanf("%f", &tmpf);
        switch(operation){
            case '=':
            if(tmpf == object.price) return true;
            else return false;
            case '>':
            if(tmpf< object.price) return true;
            else return false;
            case '<':
            if(tmpf > object.price) return true;
            else return false;
        }
    }
    if(atribute == "quantity")
    {
        float tmpff;
        printf("Enter x: ");
        scanf("%f", &tmpff);
         switch(operation){
            case '=':
            if(tmpff == object.quantity) return true;
            else return false;
            case '>':
            if(tmpff < object.quantity) return true;
            else return false;
            case '<':
            if(tmpff > object.quantity) return true;
            else return false;
        }
    }
    return false;
}
void ReadObject(Object & item, int number)
{
    ChangeColor(Colors::green);
    printf("You are currently entering data for object number [%d]:\n", number);
    ChangeColor(Colors::yellow);
    printf("[%d] Enter object's name: ", number);
    std::cin >> item.name;
    printf("[%d] Enter object's price: ", number);
     std::cin >> item.price;
    printf("[%d] Enter object's quantity: ", number);
    std::cin >> item.quantity;
    printf("[%d] Enter measurement unit: ", number);
    std::cin >> item.unit;
}
void PrintObject(Object item, int number)
{
    ChangeColor(Colors::grey);
    printf("Object number [%d]:\n",number);
    ChangeColor(Colors::white);
    std::cout << "Name: " << item.name<< "\t";
    std::cout << "Price: " << item.price<< "\t";
    std::cout << "Quantity: " << item.quantity<< "\t";
    std::cout << "Measurment unit : " << item.unit<< "\n";
}
void PrintAuthor()
{
    ChangeColor(Colors::white);
    system("cls");
    printf( "Author: Kacper Aleks (CZ/NP 12:15) \n\n") ;
}
void PrintTable(Object *  table_pointer, int  table_size)
{
    ChangeColor(Colors::red);
    if(table_pointer == nullptr) PrintError(Err_lab::no_obj);
    else{
        float sum=0;
        ChangeColor(Colors::green);
        printf("Current shopping list\n");
        for(int i=0;i<table_size;i++){
            PrintObject(table_pointer[i], i+1);
            sum += table_pointer[i].price*table_pointer[i].quantity;
        }
        printf("\t\t\t\t\t\tTotal sum is: %.2f;\n", sum);
        system("Pause");
    }
}
void PrintSelected(Object *  table_pointer, int  table_size)
{
    if(table_pointer == NULL) {
        PrintError(Err_lab::no_obj);
        return;
    }
    printf("Welcome to the condition printing creator!\n\n");
    while(true){
        std::string atribute;
        char operation;
        system("cls");
        ChangeColor(Colors::white);
        printf("[Atributes => price; name; quantity]\n[Operations => = ; > ; < ; |]\nEnter the search [Write \"0 0\" to leave] : ");
        fflush(stdin);
        std::cin >> atribute >> operation;
        if(atribute == "0" || operation == '0') return;
        for(int i =0; i<table_size; i++){
            if(CmpAtr( atribute ,table_pointer[i], operation)) {
                system("cls");
                PrintObject(table_pointer[i], i+1);
            }
        }
        system("pause");
    }
}   
void InitNewTab(Object * & table_pointer, int & table_size)
{
    ChangeColor(Colors::yellow);
    printf("Enter the table size: ");
    scanf("%d", &table_size);
    if(table_size == 0) table_pointer = nullptr;
    else {
        table_pointer=  new Object[table_size];
        if(table_pointer == nullptr)
            PrintError(Err_lab::mem);
    }

    for(int i=0;i<table_size;i++) ReadObject(*(table_pointer +i), i+1);
}
void DelTab(Object * & table_pointer, int & table_size)
{
    if(table_pointer != nullptr){
        free(table_pointer);
        table_size = 0;
        table_pointer = nullptr;
    }
    else  PrintError(Err_lab::no_obj);
}
void AddObject(Object * & table_pointer, int & table_size)
{
    Object * tmp_ptr;
    tmp_ptr =  new Object [++ table_size];
    if(tmp_ptr == nullptr) PrintError(Err_lab::mem);
    for(int i=0; i< table_size -1;i++) tmp_ptr[i] = table_pointer[i];
    table_pointer = tmp_ptr;
    free(tmp_ptr);
    ReadObject(table_pointer[table_size-1], table_size);
}
void DelObjectPos(Object * & table_pointer, int & table_size)
{
    int pos;
    if(table_pointer == nullptr) {
        PrintError((Err_lab::no_obj));
        return;
    }
    while(true){
        PrintTable(table_pointer,table_size);
        ChangeColor(Colors::yellow);
        printf("\nWhat position should be deleted? [wpisz \'0\' aby wyjsc]: ");
        fflush(stdin);
        scanf("%d", &pos); 
        if(pos == 0) return;
        if(pos-1>= table_size || pos -1<0)  PrintError(Err_lab::wrong_pos);
        else break;
    }
   
    if(table_size == 1) {  
        table_pointer =  nullptr;
        table_size = 0;
    }
    else {
        Object * tmp_ptr;
        tmp_ptr = new Object [-- table_size];
        if(tmp_ptr == nullptr) PrintError(Err_lab::mem);
        for(int i = 0; i< pos -1; i++ ) tmp_ptr[i] = table_pointer[i];
        for(int i = pos -1; i< table_size; i++) tmp_ptr[i] = table_pointer[i+1];
        table_pointer = tmp_ptr;
        free(tmp_ptr);
    }
}
void Menu( Object* &arg_1, int &arg_2)
{
    PrintAuthor();
    printf("Adress of the table's first element: %d\nCurrent size of table: %d\n", arg_1, arg_2);
    printf("\n\n");
    ChangeColor(Colors::green);
    printf("Welcome to the program that immitates a paper shoppping list!\n");
    ChangeColor(Colors::yellow);
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
        PrintError(Err_lab::wrong_pos);
    }
    
}

int main()
{
    /*
        Autor:  Kacper Aleks
        Grupa:  CZ/NP 12:15     (Czwartek nieparzysty godz 12:15)
        Temat:  program - lab 6
        Data ostatniej modyfikacji  14.01.21 12.55
    */

    Object * table;
    table = nullptr;
    int table_size=0;
    while(true) Menu(table, table_size);
    return 0;
}