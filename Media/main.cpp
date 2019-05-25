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
string XOR(string &str, int key)
{
    for (unsigned int i(0); i < str.length(); i++)
        str[i] = str[i] ^ key;
    return str;
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
/* RSA KEY GENERATING */

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

ifstream::pos_type filesize(string filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}
int main()
{
    string fileName="D:/1.jpg";
    string saveFileName="D:/3.jpg";
    int arraySize=filesize(fileName);
    ifstream in(fileName, ios::binary);
    char buffer[arraySize];
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

    string encrypt = XOR(pixels,'F');
   //pixels = XOR(encrypt,'F');
    fstream ost(saveFileName, ios_base::binary|ios::out);
    ost << head;

 /*
   ofstream outt(saveFileName, ios_base::binary|ios::out | ios::app);
   int segment=1024;
   for(unsigned int i=0;i>=0;i++){
        if((segment*(i+1))>pixels.length())
        {
            string temp = pixels.substr(segment*i,pixels.length()%segment);
            string encrypt = XOR(temp,'F');
            outt << encrypt;
            break;
        }
        else{
            string temp = pixels.substr(segment*i,segment);
            string encrypt = XOR(temp,'F');
            outt << encrypt;
        }
    }
 */
    ofstream outt(saveFileName, ios_base::binary|ios::out | ios::app);
    outt << encrypt;

    ofstream outtt(saveFileName, ios_base::binary|ios::out | ios::app);
    outtt << endMarker;

/*

    ofstream myFile ("D:/bin.txt", ios::out | ios::binary);
    myFile.write (buffer, sizeof(buffer));

    fstream os("D:/filename.txt", ios::out);
    os << header;

    std::ofstream out;
    out.open("D:/filename.txt", ios::out | ios::app);
    out << image;

    ofstream file;
    file.open("D:/2.jpg", ios_base::binary);
    file.is_open();
    for(unsigned int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); ++i)
       file.write((char*)(buffer + i * sizeof(buffer[0])), sizeof(buffer[0]));
    file.close();

    int P,Q,i,Fi,E,Mess,N,C,D,Messenc;
    P=5;
    Q=11;
    i=1;
    Mess=23553;
    N=GenerateKey(P,Q);cout<<N<<endl;
    Fi=FiFunction(P,Q);cout<<Fi<<endl;
    E=FindFirstNumber(i,Fi);cout<<E<<endl;
    D=FindD(Fi,E);cout<<D<<endl;
    C=CodindPublicKey(E,Mess,N);cout<<C<<endl;
    cout<<"Zakodowana wiadomość szyfrem RSA to: "<<C<<endl;
    Messenc=EncodingPublicKey(C,D,N);
    cout<<"Zdekodowana wiadomość szyfrem RSA to: "<<Messenc<<endl;*/
    return 0;
}
