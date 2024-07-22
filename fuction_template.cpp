#include<iostream>
#include<cstring>
using namespace std;
template<typename T>
bool compare(T a,T b){
    cout<<"template fuction"<<endl;
    return a>b;
}
/*特例化函数*/
template<>
bool compare<const char *>(const char*a,const char*b){
    cout<<"特例化 fuction"<<endl;
    return strcmp(a,b)>0;
}
bool compare(const char *a,const char*b){
    cout<<"非模版 normal fuction"<<endl;
    return strcmp(a,b)>0;
}
int main() {
    compare<int>(10, 5);
    compare<double>(3.14, 2.71);
    compare<const char *>("hello", "world");
    compare('a','b');
    return 0;
}