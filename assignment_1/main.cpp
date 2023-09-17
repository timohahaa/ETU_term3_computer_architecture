#include <iostream>
#include <bitset>
#include <iomanip>

union LDbl
{
    long double num;
    unsigned char bytes[sizeof(long double)] = {0};
};

struct Integer
{
    int num = 0;
    char bits[sizeof(int) * 8] = {0};
};

struct LDouble
{
    // intel is LE, so there will be a bunch of inverting magic going on
    // union has LE order, but bits array has BE order
    // why am I so stupid and decided to do this???
    LDbl out = {0};
    char bits[sizeof(long double) * 8] = {0};
};

void outputInt(int num)
{
    int mask = 1;
    std::cout<< "Integer is: "<< num<< std::endl;
    //32 bits basically, but no hardcode
    //print indecies first, then bits, so the output looks nicer
    for(int i = sizeof(int) * 8 - 1; i >=0; i--)
    {
        std::cout<< std::setw(3)<< i;
    }
    std::cout<<std::endl;
    for(int i = sizeof(int) * 8 - 1; i >=0; i--)
    {
        std::cout<<"___";
    }
    std::cout<<std::endl;
    for(int i = sizeof(int) * 8 - 1; i >=0; i--)
    {
        int bit = (num >> i) & mask;
        std::cout<< std::setw(3)<< bit;
    }
    std::cout<<std::endl;
}

void outputLDouble(LDbl out)
{
    std::cout<< "Long double is: "<< out.num <<std::endl;
    std::cout<< "Bits: "<< std::endl;
    // inverse the order cause of LE
    for(int i = sizeof(long double) - 1; i>= 0; i--)
    {
        std::cout<< std::bitset<CHAR_BIT>(out.bytes[i]);
    }
    std::cout<<std::endl;
    // inverse the order cause of LE
    for(int i = sizeof(long double) - 1; i>= 0; i--)
    {
        std::cout<< std::hex << int(out.bytes[i]) << " ";
    }
    std::cout<<std::dec<<std::endl;
}

Integer inputInt()
{
    Integer i = {0, {0}};
    std::cout<<"Intput your intger: ";
    std::cin>> i.num;
    //fill the bits
    int mask = 1;
    int idx = 0;
    for(int j = sizeof(int) * 8 - 1; j >=0; j--)
    {
        int bit = (i.num >> j) & mask;
        i.bits[idx] = char(bit);
//        std::cout<<int(i.bits[idx]);
        idx++;
    }
//    std::cout<<std::endl;
    return i;
}

LDouble inputLDouble()
{
    LDouble ld = {{.bytes = {0}}, {0}};
    std::cout<<"Input your long double: ";
    std::cin>>ld.out.num;
    int idx = 0;
    char mask = 1;
    // now we reverse the order back to BE to store in the bits array
    for(int i = sizeof(long double) - 1; i>= 0; i--)
    {
        // sizeof ld.out.bytes[i] = sizeof char
        for(int j = sizeof(char) * 8 - 1; j >= 0; j--)
        {
            char bit = (ld.out.bytes[i] >> j) & mask;
            ld.bits[idx] = bit;
            idx++;
        }
    }
    return ld;
}

void trIntHelper(Integer *itgr, int pos1, int pos2, int len)
{
    int i = pos1, j = pos2;
    char temp = 0;
    for(int k = 0; k < len; k++)
    {
        temp = itgr->bits[i];
        itgr->bits[i] = itgr->bits[j];
        itgr->bits[j] = temp;
        i++;
        j++;
    }
    // now reorder the bits
    itgr->num = 0;
    for(int i = 0; i < sizeof(int) * 8; i++)
    {
        int bit = itgr->bits[i] << (sizeof(int) * 8 - i - 1);
        itgr->num |= bit;
    }
}

void transformInt(Integer *itgr)
{
    int pos1, pos2;
    int len;
    std::cout<<"Enter position 1: ";
    std::cin >> pos1;
    if(pos1 > sizeof(int) * 8 || pos1 < 0)
    {
        std::cout<<"Value is out of range (0-31)!"<<std::endl;
        return;
    }
    std::cout<<"Enter position 2: ";
    std::cin >> pos2;
    if(pos2 > sizeof(int) * 8 || pos2 < 0)
    {
        std::cout<<"Value is out of range (0-31)!"<<std::endl;
        return;
    }
    if(pos1 < pos2)
    {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    std::cout<<"Enter length of the bit groups: ";
    std::cin >> len;
    if(len < 1)
    {
        std::cout<<"Length cant be less than 1!"<<std::endl;
        return;
    }
    if(pos1 - len + 1 <= pos2)
    {
        std::cout<<"pos1 + length >= pos2!"<<std::endl;
        return;
   }
    if(pos2 - len + 1 < 0)
    {
        std::cout<<"pos2 + length >= 32!"<<std::endl;
        return;
    }
    // cause bits array is 0-indexed and goes from ms bit to ls bit
    pos1 = sizeof(int) * 8 - pos1 - 1;
    pos2 = sizeof(int) * 8 - pos2 - 1;
    trIntHelper(itgr, pos1, pos2, len);
}

void trLDHelper(LDouble *ld, int pos1, int pos2, int len)
{
//    for(int p = 0; p < 128; p++)
//    {
//        std::cout<<int(ld->bits[p]);
//    }
//    std::cout<<std::endl;
    int i = pos1, j = pos2;
    char temp = 0;
    for(int k = 0; k < len; k++)
    {
        temp = ld->bits[i];
        ld->bits[i] = ld->bits[j];
        ld->bits[j] = temp;
        i++;
        j++;
    }
//    for(int p = 0; p < 128; p++)
//    {
//        std::cout<<int(ld->bits[p]);
//    }
//    std::cout<<std::endl;
    // now reorder the bits
    // zero the number
    for(int i = 0; i < sizeof(long double); i++)
    {
        ld->out.bytes[i] = 0;
    }
    // go from 0 bit to 127 bit
    // I don't know why it works, but it does, I'm honestly too lazy to redo the endianness of the whole program
    // However I do understand that this code is a complete garbage and I should be fucking embarrassed
    // But honestly, I hate my life so much at this point, that I just don't care
    for(int i = 0; i < sizeof(long double) * 8; i++)
    {
        int byteIdx = i / (sizeof(char) * 8);
        int bit = ld->bits[i] << (sizeof(char) * 8 - i % (sizeof(char) * 8) - 1);
        ld->out.bytes[15 - byteIdx] |= bit;
    }
}

void transformLDouble(LDouble *ld)
{
    int pos1, pos2;
    int len;
    std::cout<<"Enter position 1: ";
    std::cin >> pos1;
    if(pos1 > sizeof(long double) * 8 || pos1 < 0)
    {
        std::cout<<"Value is out of range (0-31)!"<<std::endl;
        return;
    }
    std::cout<<"Enter position 2: ";
    std::cin >> pos2;
    if(pos2 > sizeof(long double) * 8 || pos2 < 0)
    {
        std::cout<<"Value is out of range (0-31)!"<<std::endl;
        return;
    }
    if(pos1 < pos2)
    {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    std::cout<<"Enter length of the bit groups: ";
    std::cin >> len;
    if(len < 1)
    {
        std::cout<<"Length cant be less than 1!"<<std::endl;
        return;
    }
    if(pos1 - len + 1 <= pos2)
    {
        std::cout<<"pos1 + length >= pos2!"<<std::endl;
        return;
    }
    if(pos2 - len + 1 < 0)
    {
        std::cout<<"pos2 + length >= 32!"<<std::endl;
        return;
    }
//    // cause bits array is 0-indexed and goes from ms bit to ls bit
    pos1 = sizeof(long double) * 8 - pos1 ;
    pos2 = sizeof(long double) * 8 - pos2 ;
    trLDHelper(ld, pos1, pos2, len);
}

int menu()
{
    int option = 0;
    std::cout<< "1) Input integer"<< std::endl;
    std::cout<< "2) Print current integer"<< std::endl;
    std::cout<< "3) Transform integer"<< std::endl;
    std::cout<< "4) Input long double"<< std::endl;
    std::cout<< "5) Print current long double"<< std::endl;
    std::cout<< "6) Transform long double"<< std::endl;
    std::cout<< "7) Exit"<< std::endl;
    std::cout<< "your input: ";
    std::cin>> option;
    return option;
}

int main()
{
    LDouble ld = {{.bytes = {0}}, {0}};
    Integer i = {0, {0}};

    bool exit = false;
    int option = 0;
    while(!exit)
    {
        std::cout<<std::endl;
        option = menu();
        switch(option)
        {
            case 1:
            {
                i = inputInt();
            }
            break;
            case 2:
            {
                outputInt(i.num);
            }
            break;
            case 3:
            {
                transformInt(&i);
            }
            break;
            case 4:
            {
                ld = inputLDouble();
            }
                break;
            case 5:
            {
                outputLDouble(ld.out);
            }
                break;
            case 6:
            {
                transformLDouble(&ld);
            }
            break;
            case 7:
            {
                exit = true;
            }
            break;
            default:
            {
                std::cout<<"Wrong option!"<<std::endl;
            }
        }
    }
}
