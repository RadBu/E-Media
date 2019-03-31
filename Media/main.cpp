#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
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
int main()
{
    std::ifstream in("D:/2.jpg", std::ios::binary);

    char buffer[1151534];

    while (in)
    {
        in.read(buffer, sizeof(buffer));
    }

    string hex=hexStr(buffer,sizeof(buffer));
    std::ofstream os("D:/filename.txt");
    os << hex;
    std::ofstream file;
    file.open("D:/1.jpg", std::ios_base::binary);
    file.is_open();

    for(int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); ++i)
       file.write((char*)(buffer + i * sizeof(buffer[0])), sizeof(buffer[0]));
    file.close();

    return 0;
}

