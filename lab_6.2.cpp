
#include <cstdio>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <map>
#include <vector>

namespace Lab6 {

class Object{
    public:
    std::string name;
    double price;
    float quantity;
    std::string unit ;
    double TotalSum();
};
double Object::TotalSum()
{
    return price*quantity;
}
enum class ColLab{
    white,
    red,
    yellow,
    grey,
    kblue,
    purple
};
enum class ErrLab{
    noMem,
    noObj,
    wrongPos,
};
enum class Operation{
    bigger,
    lower,
    equal,
    startingWith,
    null
};

inline int toGuiPosition(int position)
{
    return ++position;
}
inline int toGenPosition(int position)
{
    return --position;
}
inline void ChangeColor(ColLab colorName)
{
    const std::map <ColLab, int> Colors {{ColLab::white,7},{ColLab::grey, 8},{ColLab::kblue, 11},{ColLab::red, 12},{ColLab::yellow, 14},{ColLab::kblue, 11},{ColLab::purple, 9}};
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), Colors.at(colorName) );
}
void PrintAuthor()
{
    ChangeColor(ColLab::white);
    system("cls");
    std::cout << "Author: Kacper Aleks (CZ/NP 12:15) \n\n" ;
}
void PrintError(ErrLab errorName)
{
    const std::map <ErrLab, std::string> Errors {{ErrLab::wrongPos,"Wrong number!"},{ErrLab::noObj,"There are no objects!"},{ErrLab::noMem,"There is no memory left :("}};
    ChangeColor(ColLab::red);
    std::cout << Errors.at(errorName) << "\n";
    std::this_thread::sleep_for (std::chrono::seconds(1));
    system("cls");
}
Operation ConvertOperation(char c)
{
    switch(c){
        case '=':
        return Operation::equal;
        case '>':
        return Operation::bigger;
        case '<':
        return Operation::lower;
        case '|':
        return Operation::startingWith;
        default:
        return Operation::null;
    };
}
bool CmpNameAttr(Object object, Operation op)
{
    std::string tmp;
    if(op == Operation::equal){
        std::string tmp;
        std::cout << "Enter wanted name: ";
        std::cin >> tmp;
        if(object.name == tmp) return true;
        else return false;
    }
    else {
            char tmpC;
            std::cout << "Enter wanted letter: ";
            std::cin >> tmpC;
            if(object.name[0] == tmpC) return true;
            else return false;
    }
}
template <typename Member> bool CmpGenericAttr(Member m ,Operation op)
{
    Member tmp;
    std::cout << "Enter reference number: ";
    std::cin >> tmp;
    if(op == Operation::equal) {
        if(tmp == m) return true;
        else return false;
    }
    if(op == Operation::bigger) {
        if(tmp < m) return true;
        else return false;
    }
    else {
        if(tmp > m) return true;
        else return false;
    }
}
Lab6::Object ReadObject(Object & item, int number)
{
    fflush(stdin);
    ChangeColor(ColLab::kblue);
    printf("You are currently entering data for object number [%d]:\n", number);
    ChangeColor(ColLab::yellow);
    printf("[%d] Enter object's name: ", number);
    std::cin >> item.name;
    printf("[%d] Enter object's price per measurement unit: ", number);
    std::cin >> item.price;
    printf("[%d] Enter object's quantity: ", number);
    std::cin >> item.quantity;
    printf("[%d] Enter measurement unit: ", number);
    std::cin >> item.unit;
    return item;
}
void PrintObject(Object item, int number)
{
    ChangeColor(ColLab::kblue);
    printf("Object number [%d]:\n",number);
    ChangeColor(ColLab::purple);
    std::cout << "Name: ";
    ChangeColor(ColLab::yellow);
    std::cout<< item.name<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Price: ";
    ChangeColor(ColLab::yellow);
    std::cout << item.price<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Quantity: "; 
    ChangeColor(ColLab::yellow);
    std::cout << item.quantity<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Measurment unit: "; 
    ChangeColor(ColLab::yellow);
    std::cout << item.unit<< "\n\n";
}
void PrintTable(std::vector <Lab6::Object> table, int  tableSize)
{
    ChangeColor(ColLab::red);
    if(tableSize == 0) PrintError(ErrLab::noObj);
    else{
        float sum=0;
        ChangeColor(ColLab::kblue);
        printf("Current shopping list\n\n\n");
        for(int i=0;i<tableSize;i++){
            PrintObject(table.at(i), toGuiPosition(i));
            sum += table.at(i).TotalSum();
        }
        printf("Total sum is: %.2f;\n\n", sum);
        system("Pause");
    }
}
void PrintSelected(std::vector <Lab6::Object> table, int  tableSize)
{
    if(tableSize == 0 ) {
        PrintError(ErrLab::noObj);
        return;
    }
    printf("Welcome to the condition printing creator!\n\n");
    while(true){
        std::string attribute;
        char c;
        system("cls");
        ChangeColor(ColLab::kblue);
        std::cout << "[Atributes => price; name; quantity]\n[Operations => = ; > ; < ; |]\n\n";
        ChangeColor(ColLab::white);
        std::cout << "Enter the search [Write \"0 0\" to leave] : ";
        fflush(stdin);
        std::cin >> attribute >> c;
        Operation op = ConvertOperation(c);
        if(attribute == "0" || c == '0') return;
        for(int i =0; i<tableSize; i++){
            if(attribute == "name"){
                if(CmpNameAttr(table.at(i), op)) {
                    system("cls");
                    PrintObject(table.at(i), toGuiPosition(i));
                }
            }
            if(attribute == "price") {
                if( CmpGenericAttr <double> (table.at(i).price ,op)) {
                    system("cls");
                    PrintObject(table.at(i), toGuiPosition(i));
                }
            }
            if(attribute == "quantity") {
                if(CmpGenericAttr <float> (table.at(i).quantity ,op)) {
                    system("cls");
                    PrintObject(table.at(i), toGuiPosition(i));
                }
            }
        }
        system("pause");
    }
}   
void InitNewTab(std::vector <Lab6::Object> & table, int & tableSize)
{
    ChangeColor(ColLab::yellow);
    printf("Enter the table size: ");
    scanf("%d", &tableSize);
    if(tableSize == 0);
    else table.resize(tableSize);
    for(int i=0;i<tableSize;i++) ReadObject(table.at(i), toGuiPosition(i));
}
void DelTab(std::vector <Lab6::Object> & table, int & tableSize)
{
    if(tableSize != 0) table.resize(0);
    else  PrintError(ErrLab::noObj);
}
void AddObject(std::vector <Lab6::Object> & table, int & tableSize)
{
    table.resize(++tableSize);
    ReadObject(table.at(tableSize-1), tableSize);
}
void DelObjectPos(std::vector <Lab6::Object> & table, int & tableSize)
{
    int pos;
    if(table.size() == 0) {
        PrintError((ErrLab::noObj));
        return;
    }
    while(true){
        PrintTable(table,tableSize);
        ChangeColor(ColLab::yellow);
        printf("\nWhat position should be deleted? [wpisz \'0\' aby wyjsc]: ");
        fflush(stdin);
        scanf("%d", &pos); 
        if(pos == 0) return;
        pos= toGenPosition(pos);
        if(pos >= tableSize || pos < 0)  PrintError(ErrLab::wrongPos);
        else break;
    }
   
    if(tableSize == 1) table.resize(0);
    else {
        for(int i = pos -1; i< tableSize; i++) table.at(i) = table.at(i+1);
        table.resize(--tableSize);
    }
}
int Menu(std::vector <Lab6::Object> & arg1)
{
    int tableSize = arg1.size();
    PrintAuthor();
    printf("Adress of the table's first element: %d\nCurrent size of table: %d\n", arg1, tableSize );
    printf("\n\n");
    ChangeColor(ColLab::kblue);
    printf("Welcome to the program that immitates a paper shoppping list!\n");
    ChangeColor(ColLab::yellow);
    printf("[1] Create new table\n[2] Delete table\n[3] Add one object \n[4] Delete object at certain position\n[5] Print table \n[6] Print selected objects\nExit [K]\n");
    fflush(stdin);
    char c=getch();
    switch(c){
        case '1':
        system("cls");
        InitNewTab(arg1,tableSize);
        break;

        case '2':
        system("cls");
        DelTab(arg1,tableSize);
        break;

        case '3':
        system("cls");
        AddObject(arg1,tableSize);
        break;

        case '4':
        system("cls");
        DelObjectPos(arg1,tableSize);
        break;

        case '5':
        system("cls");
        PrintTable(arg1, tableSize);
        break;

        case '6':
        system("cls");
        PrintSelected(arg1,tableSize);
        system("Pause");
        break;

        case 'k':
        return 0;

        case 'K':
        return  0;

        default:
        PrintError(ErrLab::wrongPos);
    }
    return 1;
}

}

int main(){
    /*
        Autor:  Kacper Aleks
        Grupa:  CZ/NP 12:15     (Czwartek nieparzysty godz 12:15)
        Temat:  program - lab 6
        Data ostatniej modyfikacji  14.01.21 12.55
    */
    std::vector <Lab6::Object> table;
    while(Lab6::Menu(table));
    return 0;
}