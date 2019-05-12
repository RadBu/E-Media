#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <cstddef>
using namespace std;

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
string hexStr(char *data, int len)
{
string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
 /* std::string s(len * 3, ' ');
  for (int i = 0; i < len; ++i) {
    s[3 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[3 * i + 1] = hexmap[data[i] & 0x0F];
    if((i+1)%16==0)
        s[3 * i + 2] = '\n';
    else
        s[3 * i + 2] = ' ';
  }*/
  return s;
}
string XOREncryption(string str, char key)
{
    string enc("");
    for (unsigned int i(0); i < str.length(); i++)
        enc += str[i] ^ key;
    return enc;
}
string XORDecryption(string str, char key)
{
    string dec("");
    for (unsigned int i(0); i < str.length(); i++)
        dec += str[i] ^ key;
    return dec;
}

string ToChar(string str)
{
    int len = str.length();
    string newStr;
    for(int i=0; i< len; i+=2)
    {
        string byte = str.substr(i,2);
        char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
        newStr.push_back(chr);
    }
    return newStr;
}

void encryptDecrypt(char inpString[]) 
{ 
   
    char xorKey = 'F'; 
  

    int len = strlen(inpString); 
  
  
    for (int i = 0; i < len; i++) 
    { 
        inpString[i] = inpString[i] ^ xorKey; 
        printf("%c",inpString[i]); 
    } 
}
/* RSA KEY GENERATING */
/*
template <class T>
T GenerateKey(T P,T Q)
{
    T N;
    N=P*Q;
    return N;
}
template <class T>
T FiFunction(T P,T Q)
{
    T Fi;
    Fi=(P-1)*(Q-1);
    return Fi;

}
template <class T>
T FindFirstNumber(int i, T Fi)
{
    T E;
    int tmp=0;
    while(tmp!=1)
    {
        E=(rand() % Fi-1)+i;
        for(int j=2;j*j<=E;j++)
        {
            if(E%j==0)
            {
                tmp=1;
            }
        }
    }
    return E;

}
template<class T>
T FindD(T Fi, T E)
{
    int tmp=0;
    T D=1;
    while(tmp != 1)
    {
        if((D*E)%Fi==1)
        {
            tmp=1;
        }
        else
            D++;

    }
return D;
}
template<class T>
T CodindPublicKey(T E,T Mess,T N)
{
    T C;
    for(int i=0;i<E;i++)
    {
      C*=Mess;
    }
    //C=(pow(Mess,E)%N);
    C=(C%N);
    return C;
}
template<class T>
T EncodingPublicKey(T C,T D, T N)
{
    T Menc;
    for(int i=0;i<D;i++)
    {
      Menc*=C;
    }
    //Menc=(pow(C,D)%N);
    Menc=(Menc%N);
    return Menc;

}
*/
int main()
{
	char tab[]="Zwykly napis";
	string first="Pierwszy";
	std::cout<<"Tutaj1: "<<XOREncryption(first,'F')<<endl;
	std::cout<<"Tutaj2: "<<XORDecryption(first,'F')<<endl;
	encryptDecrypt(tab);
	encryptDecrypt(tab);
	/*
    ifstream in("kot.jpg", ios::binary);
    char buffer[1151534];
    while (in)
    {
        in.read(buffer, sizeof(buffer));
    }
    string hex=hexStr(buffer,sizeof(buffer));
    size_t headerEnd = hex.find( "FFDA" );
    string header = hex.substr (0,headerEnd+24);
    string image = hex.substr (headerEnd+24);
    string endKey ("FFD9");
    size_t found = image.rfind(endKey);
    string img = image.substr (0,found);
    string endImage = image.substr (found);

    string head=ToChar(header);
    string pixels=ToChar(img);
    string endMarker=ToChar(endImage);

    string encrypt = XOREncryption(pixels,'F');

    fstream ost("kot.jpg", ios_base::binary|ios::out);
    ost << head;

    ofstream outt("kot.jpg", ios_base::binary|ios::out | ios::app);
    outt << encrypt;

    ofstream outtt("kot.jpg", ios_base::binary|ios::out | ios::app);
    outtt << endMarker;



    ofstream myFile ("bin.txt", ios::out | ios::binary);
    myFile.write (buffer, sizeof(buffer));

    fstream os("filename.txt", ios::out);
    os << header;

    std::ofstream out;
    out.open("filename.txt", ios::out | ios::app);
    out << image;

    ofstream file;
    file.open("2.jpg", ios_base::binary);
    file.is_open();
    for(unsigned int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); ++i)
       file.write((char*)(buffer + i * sizeof(buffer[0])), sizeof(buffer[0]));
    file.close();
    */
/*
    int P,Q,i,Fi,E,Mess,N,C,D,Messenc;
    P=7;
    Q=11;
    i=1;
    Mess=2;
    N=GenerateKey(P,Q);
    Fi=FiFunction(P,Q);
    E=FindFirstNumber(i,Fi);
    D=FindD(Fi,E);
    C=CodindPublicKey(E,Mess,N);
    cout<<"Zakodowana wiadomość szyfrem RSA to: "<<C<<endl;
    Messenc=EncodingPublicKey(C,D,N);
    cout<<"Zdekodowana wiadomość szyfrem RSA to: "<<Messenc<<endl;*/
    return 0;
}
