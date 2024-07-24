#include <iostream>
#include <cstring>
using namespace std;
namespace me
{
    class String
    {
    public:
        class iterator
        {
        public:
            iterator(char *p) : p(p) {}
            bool operator!=(const iterator &other) const { return p != other.p; }
            void operator++() { p++; }
            char & operator*() const { return *p; }
        private:
            char *p;
        };
        iterator begin() const { return iterator(m_data); }
        iterator end() const { return iterator(m_data + length()); }
        String(const char *str = nullptr)
        {
            if (str != nullptr)
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
            }

            return *this;
        }
        bool operator>(const String &other) const
        {
            return strcmp(m_data, other.m_data) > 0;
        }
        bool operator<(const String &other) const
        {
            return strcmp(m_data, other.m_data) < 0;
        }
        bool operator==(const String &other) const
        {
            return strcmp(m_data, other.m_data) == 0;
        }
        int length() const { return strlen(m_data); }
        char &operator[](int index) { return m_data[index]; }
        char &operator[](int index) const { return m_data[index]; }
        const char *c_str() const { return m_data; }
        ~String()
        {
            delete[] m_data;
            m_data = nullptr;
        }

    private:
        char *m_data;
        friend ostream &operator<<(ostream &os, const String &str);
        friend String operator+(const String &s1, const String &s2);
    };
    ostream &operator<<(ostream &os, const String &str)
    {
        os << str.m_data;
        return os;
    }
    String operator+(const String &s1, const String &s2)
    {
        String temp;
        temp.m_data = new char[strlen(s1.m_data) + strlen(s2.m_data) + 1];
        strcpy(temp.m_data, s1.m_data);
        strcat(temp.m_data, s2.m_data);

        return temp;
    }
}

int main(int argc, char *argv[])
{
    me::String str1("Hello, ");
    me::String str2("World!");
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str1 > str2: " << (str1 > str2) << endl;
    cout << "str1 < str2: " << (str1 < str2) << endl;
    cout << "str1 == str2: " << (str1 == str2) << endl;

    me::String str3 = str1 + str2;
    cout << "str1 + str2: " << str3 << endl;

    str3[0] = 'J';
    cout << "Modified str3: " << str3 << endl;
    me::String str4("hello iterator");
    //me::String::iterator it = str4.begin();
    auto it=str4.begin();
    for (; it != str4.end(); ++it)
    {
        cout << *it << " ";
    }
    cout<<endl;
    for(auto p:str4){
        cout<<p<<" ";
    }
    return 0;
};
