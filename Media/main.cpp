#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>

using namespace std;
/*
constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

std::string hexStr(char *data, int len)
{
  std::string s(len * 3, ' ');
  for (int i = 0; i < len; ++i) {
    s[3 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[3 * i + 1] = hexmap[data[i] & 0x0F];
    if((i+1)%8==0)
        s[3 * i + 2] = '\n';
    else
        s[3 * i + 2] = ' ';
  }
  return s;
}
 */
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
        E=(rand() % Fi-1)+1;
        for(int i=2;i*i<=E;i++)
        {
            if(E%i==0)
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
    T D=0;
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
    C=(pow(Mess,E)%N);
    return C;
}
template<class T>
T EncodingPublicKey(T C,T D, T N)
{
    T Menc;
    Menc=(pow(C,D)%N);
    return Menc;

}

int main()
{
    /*
    std::ifstream in("kot.jpg", std::ios::binary);

    char buffer[1151534];

    while (in)
    {
        in.read(buffer, sizeof(buffer));
    }

    string hex=hexStr(buffer,sizeof(buffer));
    std::ofstream os("filename.txt");
    os << hex;
    std::ofstream file;
    file.open("kot.jpg", std::ios_base::binary);
    file.is_open();

    for(int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); ++i)
       file.write((char*)(buffer + i * sizeof(buffer[0])), sizeof(buffer[0]));
    file.close();
*/
    int P,Q,i,Fi,E,Mess,N,C,D,Messenc;
    P=11;
    Q=17;
    i=1;
    Mess=42;
    N=GenerateKey(P,Q);
    FiFunction(P,Q);
    E=FindFirstNumber(i,Fi);
    D=FindD(Fi,E);
    C=CodindPublicKey(E,Mess,N);
    Messenc=EncodingPublicKey(C,D,N);
    cout<<"Zakodowana wiadomość szyfrem RSA to: "<<Messenc<<endl;
    return 0;
}

