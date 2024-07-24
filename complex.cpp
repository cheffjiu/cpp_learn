#include <iostream>
using namespace std;
class complex
{
private:
    int real;
    int imag;
    friend complex operator+(const complex &c1, const complex &c2);
    friend ostream &operator<<(ostream &out, const complex &c);
    friend istream &operator>>(istream &in, complex &c);

public:
    complex(int r = 0, int i = 0) : real(r), imag(i) {}
    complex operator+(const complex &other)
    {
        return complex(this->real + other.real, this->imag + other.imag);
    }
    // 重载后置++
    complex operator++(int)
    {
        return complex(real++, this->imag++);
    }
    // 重载前置++
    complex &operator++()
    {
        this->real++;
        this->imag++;
        return *this;
    }
    void operator+=(const complex &other)
    {
        this->real += other.real;
        this->imag += other.imag;
    }
    void show()
    {
        cout << "real: " << real << ", imag: " << imag << endl;
    }
    ~complex() {}
};
complex operator+(const complex &c1, const complex &c2)
{
    return complex(c1.real + c2.real, c1.imag + c2.imag);
}
ostream &operator<<(ostream &out, const complex &c)
{
    out << "real: " << c.real << ", imag: " << c.imag;
    return out;
}
istream &operator>>(istream &in, complex &c)
{
    in >> c.real >> c.imag;
    return in;
}
int main()
{
    complex c1(2, 3);
    complex c2(2, 3);
    complex c3 = c1 + c2;
    c3.show();
    complex c4 = c1 + 5;
    c4.show();
    complex c5 = 5 + c2;
    c5.show();
    // complex operator ++()
    complex c6 = ++c1;
    c6.show();
    c1.show();
    // complex operator ++(int)
    complex c7 = c2++;
    c7.show();
    c2.show();
    complex c8;
    c8 += c1;
    c8.show();
    cout << c8 << endl;
    cin >> c1;
    cout << c1 << endl;

    return 0;
}