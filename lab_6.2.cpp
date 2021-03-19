#include <cstdio>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
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
    double Sum();
};
double Object::Sum()
{
    return price*quantity;
}
enum class ColLab{
    white,
    red,
    yellow,
    grey,
    cyan,
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
    const std::map <ColLab, int> Colors {{ColLab::white,7},{ColLab::grey, 8},{ColLab::purple, 9},{ColLab::cyan, 11},{ColLab::red, 12},{ColLab::yellow, 14}};
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
        break;
    }
    return Operation::null;
}
bool CmpNameAttr(Object object, Operation op)
{
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
    ChangeColor(ColLab::cyan);
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
    ChangeColor(ColLab::cyan);
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
    std::cout << "Measurement unit: ";
    ChangeColor(ColLab::yellow);
    std::cout << item.unit<< "\n\n";
}
void PrintTable(std::vector <Lab6::Object> table)
{
    int tableSize= table.size();
    ChangeColor(ColLab::red);
    if(tableSize == 0) PrintError(ErrLab::noObj);
    else{
        float totalSum=0;
        ChangeColor(ColLab::cyan);
        printf("Current shopping list\n\n\n");
        for(int i=0;i<tableSize;i++){
            PrintObject(table.at(i), toGuiPosition(i));
            totalSum += table.at(i).Sum();
        }
        printf("Total sum is: %.2f;\n\n", totalSum);
        system("Pause");
    }
}
void PrintSelected(std::vector <Lab6::Object> table)
{
    int tableSize= table.size();
    if(tableSize == 0 ) {
        PrintError(ErrLab::noObj);
        return;
    }
    printf("Welcome to the condition printing creator!\n\n");
    while(true){
        std::string attribute;
        char c;
        system("cls");
        ChangeColor(ColLab::cyan);
        std::cout << "[Attributes => price; name; quantity]\n[Operations => = ; > ; < ; |]\n\n";
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
void InitNewTab(std::vector <Lab6::Object> & table)
{
    int tableSize= table.size();
    ChangeColor(ColLab::yellow);
    printf("Enter the table size: ");
    std::cin >> tableSize;
    if(tableSize == 0);
    else table.resize(tableSize);
    for(int i=0;i<tableSize;i++) ReadObject(table.at(i), toGuiPosition(i));
}
void DelTab(std::vector <Lab6::Object> & table)
{
    int tableSize= table.size();
    if(tableSize != 0) table.resize(0);
    else  PrintError(ErrLab::noObj);
}
void AddObject(std::vector <Lab6::Object> & table)
{
    int tableSize= table.size();
    table.resize(++tableSize);
    ReadObject(table.at(tableSize-1), tableSize);
}
void DelObjectPos(std::vector <Lab6::Object> & table)
{
    int tableSize= table.size();
    int pos;
    if(table.empty()) {
        PrintError((ErrLab::noObj));
        return;
    }
    while(true){
        PrintTable(table);
        ChangeColor(ColLab::yellow);
        printf("\nWhat position should be deleted? [Enter \'0\' to leave]: ");
        fflush(stdin);
        std::cin >> pos;
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
    PrintAuthor();
    std::cout << "Address of the table's first element: " << &arg1 << "\nCurrent size of table: " << arg1.size() << "\n";
    printf("\n\n");
    ChangeColor(ColLab::cyan);
    printf("Welcome to the program that imitates a paper shopping list!\n");
    ChangeColor(ColLab::yellow);
    printf("[1] Create new table\n[2] Delete table\n[3] Add one object \n[4] Delete object at certain position\n[5] Print table \n[6] Print selected objects\nExit [K]\n");
    fflush(stdin);
    char c=getch();
    switch(c){
        case '1':
        system("cls");
        InitNewTab(arg1);
        break;

        case '2':
        system("cls");
        DelTab(arg1);
        break;

        case '3':
        system("cls");
        AddObject(arg1);
        break;

        case '4':
        system("cls");
        DelObjectPos(arg1);
        break;

        case '5':
        system("cls");
        PrintTable(arg1);
        break;

        case '6':
        system("cls");
        PrintSelected(arg1);
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

int main() {
    std::vector<Lab6::Object> table;
    while (Lab6::Menu(table));
    return 0;
}