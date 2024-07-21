#include <iostream>
#include <cstring>
using namespace std;
class String
{
public:
    String(const char *str = nullptr)
    {
        if (str!=nullptr)
        {
            m_data = new char[strlen(str) + 1];
            strcpy(m_data, str);
        }
        else
        {
            m_data = new char[1];
            *m_data = '\0';
        }
    }
    String(const String &other)
    {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_data = new char[strlen(other.m_data) + 1];
            strcpy(m_data, other.m_data);
            return *this;
        }
        else
        {
            return *this;
        }
    }
    ~String(){
        delete[] m_data;
        m_data=nullptr;
    }
private:
    char *m_data;
};
int main(int argc, char *argv[])
{   
    String s1;
    String s2("test");
    s1 = s2;
    cout << "test sucessfully!" << endl;
    return 0;
};