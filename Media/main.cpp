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
#include "D:\boost_1_56_0\boost_1_56_0\boost/lexical_cast.hpp"

using namespace std;
namespace mp = boost::multiprecision;
namespace ran = boost::random;

const mp::int1024_t xorKey=477777777774745848;
constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
string hexStr(char *data, int len)
{
string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}
string XOR(string &str)
{
    string key = boost::lexical_cast<string>(xorKey);
    int k=0;
    for (unsigned int i(0); i < str.length(); i++)
    {
        if(k==key.length())
            k=0;
        str[i] = str[i] ^ key[k];
        k++;
    }
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
    ifstream inputStream(filename, ifstream::ate | ifstream::binary);
    return inputStream.tellg();
}
int main()
{
    string fileName="D:/1.jpg";
    string saveFileName="D:/3.jpg";
    int arraySize=filesize(fileName);
    ifstream inputStream(fileName, ios::binary);
    char buffer[arraySize];
    while (inputStream)
    {
        inputStream.read(buffer, sizeof(buffer));
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

    string encrypt = XOR(pixels);
    fstream headStream(saveFileName, ios_base::binary|ios::out);
    headStream << head;

    int k=9;
    mp::int1024_t P,Q,Fi,E,Mess,N,C,D,Messenc;
    do
    {
        P=gen128();
    }while(!Miller(P,k));
    do
    {
        Q=gen128();
    }while(!Miller(Q,k));
    Mess=5675446363757123347;
    N=GenerateKey(P,Q);
    Fi=FiFunction(P,Q);
    E=FindFirstNumber(Fi);
    D=FindD(Fi,E);
    C=CodindPublicKey(E,Mess,N);
    //cout<<"Zakodowana wiadomość szyfrem RSA to: "<<C<<endl;
    Messenc=EncodingPublicKey(C,D,N);
    //cout<<"Zdekodowana wiadomość szyfrem RSA to: "<<Messenc<<endl;

    ofstream dataStream(saveFileName, ios_base::binary|ios::out | ios::app);
    dataStream << encrypt;

    ofstream endStream(saveFileName, ios_base::binary|ios::out | ios::app);
    endStream << endMarker;

    return 0;
}
