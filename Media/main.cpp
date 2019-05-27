#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <cstddef>
#include <random>
#include "D:\boost_1_56_0\boost_1_56_0\boost\multiprecision\cpp_int.hpp"
#include "D:\boost_1_56_0\boost_1_56_0\boost\random.hpp"

using namespace std;
namespace mp = boost::multiprecision;
namespace ran = boost::random;
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
   //
/* RSA KEY GENERATING */
typedef ran::independent_bits_engine<mt19937, 128, mp::uint128_t> generator128_type;
generator128_type gen128;

template<class T>
T mulmod(T a, T b, T m)
{
   T x = 0,y = a % m;
   while (b > 0) {
      if (b % 2 == 1) {
         x = (x + y) % m;
      }
      y = (y * 2) % m;
      b /= 2;
   }
   return x % m;
}

template<class T>
T modular_pow(T base, T exponent, T modulus)
{
    T result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
template<class T>
bool Miller(T p, int iteration) {
   if (p < 2) {
      return false;
   }
   if (p != 2 && p % 2==0) {
      return false;
   }
   T s = p - 1;
   while (s % 2 == 0) {
      s /= 2;
   }
   for (int i = 0; i < iteration; i++) {
      T a = rand() % (p - 1) + 1, temp = s;
      T mod = modular_pow(a, temp, p);
      while (temp != p - 1 && mod != 1 && mod != p - 1) {
         mod = mulmod(mod, mod, p);
         temp *= 2;
      }
      if (mod != p - 1 && temp % 2 == 0) {
         return false;
      }
   }
   return true;
}
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
T FindFirstNumber(T Fi)
{
    T E,j=2,a,b,t;
    for(E=1+1;E<Fi;E++)
    {
        for(j=2;j <E;j++)
        {
            if(E %j==0)
            {
                break;
            }
        }
        if(E==j || E==1)
        {
            a=E;
            b=Fi;
            while(b)
            {
                t = b;
                b = a % b;
                a = t;
            }
            if(a==1)
                break;
        }
    }
    return E;
}
template<class T>
T FindD(T Fi, T E)
{
  T u,w,D,z,q;

  u = 1; w = E;
  D = 0; z = Fi;
  while(w)
  {
    if(w < z)
    {
      q = u; u = D; D = q;
      q = w; w = z; z = q;
    }
    q = w / z;
    u -= q * D;
    w -= q * z;
  }
  if(z == 1)
  {
    if(D < 0) D += Fi;
        return D;
  }
  return 0;
}
template<class T>
T CodindPublicKey(T E,T Mess,T N)
{
    T C = modular_pow(Mess,E,N);
    return C;
}
template<class T>
T EncodingPublicKey(T C,T D, T N)
{
    T M = modular_pow(C,D,N);
    return M;
}

ifstream::pos_type filesize(string filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}
		string GetBinaryStringFromHexString (string sHex)
		{
			string sReturn = "";
			for (int i = 0; i < sHex.length (); ++i)
			{
				switch (sHex [i])
				{
					case '0': sReturn.append ("0000"); break;
					case '1': sReturn.append ("0001"); break;
					case '2': sReturn.append ("0010"); break;
					case '3': sReturn.append ("0011"); break;
					case '4': sReturn.append ("0100"); break;
					case '5': sReturn.append ("0101"); break;
					case '6': sReturn.append ("0110"); break;
					case '7': sReturn.append ("0111"); break;
					case '8': sReturn.append ("1000"); break;
					case '9': sReturn.append ("1001"); break;
					case 'A': sReturn.append ("1010"); break;
					case 'B': sReturn.append ("1011"); break;
					case 'C': sReturn.append ("1100"); break;
					case 'D': sReturn.append ("1101"); break;
					case 'E': sReturn.append ("1110"); break;
					case 'F': sReturn.append ("1111"); break;
				}
			}
			return sReturn;
		}
int main()
{
    string fileName="D:/5.jpg";
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
*/
    mp::int1024_t P,Q,Fi,E,Mess,N,C,D,Messenc;
    do
    {
        P=gen128();
    }while(!Miller(P,9));
    do
    {
        Q=gen128();
    }while(!Miller(Q,9));
    cout<<P<<endl;
    cout<<Q<<endl;
    Mess=59565;
    N=GenerateKey(P,Q);cout<<N<<endl;
    Fi=FiFunction(P,Q);cout<<Fi<<endl;
    E=FindFirstNumber(Fi);cout<<E<<endl;
    D=FindD(Fi,E);cout<<D<<endl;
    C=CodindPublicKey(E,Mess,N);
    cout<<"Zakodowana wiadomość szyfrem RSA to: "<<C<<endl;
    Messenc=EncodingPublicKey(C,D,N);
    cout<<"Zdekodowana wiadomość szyfrem RSA to: "<<Messenc<<endl;
    return 0;
}
