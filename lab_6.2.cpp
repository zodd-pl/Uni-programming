
#include <cstdio>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <map>

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
enum class ErrLab{
    noMem,
    noObj,
    wrongPos,
};

inline void ChangeColor(Colors color)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), static_cast<int>(color));
}
void PrintError(ErrLab errorName)
{
    std::map <ErrLab, std::string> Errors {{ErrLab::wrongPos,"Wrong number!"},{ErrLab::noObj,"There are no objects!"},{ErrLab::noMem,"There is no memory left :("}};
    ChangeColor(Colors::red);
    std::cout << Errors[errorName] << "\n";
    std::this_thread::sleep_for(2000);
    system("cls");
}
bool CmpAtr(std::string atribute, Object object, char operation)
{
    if(atribute == "name" ){
        if(operation == '='){
            std::string tmp;
            std::cout << "Enter x: ";
            std::cin >> tmp;
            if(object.name == tmp) return true;
            else return false;
        }
        else {
            char tmpC;
            std::cout << "Enter x: ";
            std::cin >> tmpC;
            if(object.name[0] == tmpC) return true;
            else return false;
        }
    }
    if(atribute == "price")
    {
        float tmpF;
        std::cout << "Enter x: ";
        std::cin >> tmpF;
        switch(operation){
            case '=':
            if(tmpF == object.price) return true;
            else return false;
            case '>':
            if(tmpF< object.price) return true;
            else return false;
            case '<':
            if(tmpF > object.price) return true;
            else return false;
        }
    }
    if(atribute == "quantity")
    {
        float tmpFF;
        std::cout << "Enter x: ";
        std::cin >> tmpFF;
         switch(operation){
            case '=':
            if(tmpFF == object.quantity) return true;
            else return false;
            case '>':
            if(tmpFF < object.quantity) return true;
            else return false;
            case '<':
            if(tmpFF > object.quantity) return true;
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
    std::cout << "Author: Kacper Aleks (CZ/NP 12:15) \n\n" ;
}
void PrintTable(Object *  tablePointer, int  tableSize)
{
    ChangeColor(Colors::red);
    if(tablePointer == nullptr) PrintError(ErrLab::noObj);
    else{
        float sum=0;
        ChangeColor(Colors::green);
        printf("Current shopping list\n");
        for(int i=0;i<tableSize;i++){
            PrintObject(tablePointer[i], i+1);
            sum += tablePointer[i].price*tablePointer[i].quantity;
        }
        printf("\t\t\t\t\t\tTotal sum is: %.2f;\n", sum);
        system("Pause");
    }
}
void PrintSelected(Object *  tablePointer, int  tableSize)
{
    if(tablePointer == NULL) {
        PrintError(ErrLab::noObj);
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
        for(int i =0; i<tableSize; i++){
            if(CmpAtr( atribute ,tablePointer[i], operation)) {
                system("cls");
                PrintObject(tablePointer[i], i+1);
            }
        }
        system("pause");
    }
}   
void InitNewTab(Object * & tablePointer, int & tableSize)
{
    ChangeColor(Colors::yellow);
    printf("Enter the table size: ");
    scanf("%d", &tableSize);
    if(tableSize == 0) tablePointer = nullptr;
    else {
        tablePointer=  new Object[tableSize];
        if(tablePointer == nullptr)
            PrintError(ErrLab::noMem);
    }

    for(int i=0;i<tableSize;i++) ReadObject(*(tablePointer +i), i+1);
}
void DelTab(Object * & tablePointer, int & tableSize)
{
    if(tablePointer != nullptr){
        free(tablePointer);
        tableSize = 0;
        tablePointer = nullptr;
    }
    else  PrintError(ErrLab::noObj);
}
void AddObject(Object * & tablePointer, int & tableSize)
{
    Object * tmpPtr;
    tmpPtr =  new Object [++ tableSize];
    if(tmpPtr == nullptr) PrintError(ErrLab::noMem);
    for(int i=0; i< tableSize -1;i++) tmpPtr[i] = tablePointer[i];
    tablePointer = tmpPtr;
    free(tmpPtr);
    ReadObject(tablePointer[tableSize-1], tableSize);
}
void DelObjectPos(Object * & tablePointer, int & tableSize)
{
    int pos;
    if(tablePointer == nullptr) {
        PrintError((ErrLab::noObj));
        return;
    }
    while(true){
        PrintTable(tablePointer,tableSize);
        ChangeColor(Colors::yellow);
        printf("\nWhat position should be deleted? [wpisz \'0\' aby wyjsc]: ");
        fflush(stdin);
        scanf("%d", &pos); 
        if(pos == 0) return;
        if(pos-1>= tableSize || pos -1<0)  PrintError(ErrLab::wrongPos);
        else break;
    }
   
    if(tableSize == 1) {  
        tablePointer =  nullptr;
        tableSize = 0;
    }
    else {
        Object * tmpPtr;
        tmpPtr = new Object [-- tableSize];
        if(tmpPtr == nullptr) PrintError(ErrLab::noMem);
        for(int i = 0; i< pos -1; i++ ) tmpPtr[i] = tablePointer[i];
        for(int i = pos -1; i< tableSize; i++) tmpPtr[i] = tablePointer[i+1];
        tablePointer = tmpPtr;
        free(tmpPtr);
    }
}
void Menu( Object* &arg1, int &arg2)
{
    PrintAuthor();
    printf("Adress of the table's first element: %d\nCurrent size of table: %d\n", arg1, arg2);
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
        InitNewTab(arg1, arg2);
        break;

        case '2':
        system("cls");
        DelTab(arg1, arg2);
        break;

        case '3':
        system("cls");
        AddObject(arg1, arg2);
        break;

        case '4':
        system("cls");
        DelObjectPos(arg1, arg2);
        break;

        case '5':
        system("cls");
        PrintTable(arg1, arg2);
        break;

        case '6':
        system("cls");
        PrintSelected(arg1, arg2);
        system("Pause");
        break;

        case 'k':
        return ;

        case 'K':
        return ;

        default:
        PrintError(ErrLab::wrongPos);
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
    int tableSize=0;
    while(true) Menu(table, tableSize);
    return 0;
}
