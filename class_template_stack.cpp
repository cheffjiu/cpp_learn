#include <iostream>
using namespace std;

template <typename T>
class SeqStack
{
public:
    //SeqStack(int capacity = 10) : _pstack(new T[capacity]), _top(-1), _capacity(capacity) {}
    SeqStack(int capacity = 10, int top = -1) : _pstack(new T[capacity]), _top(top), _capacity(capacity) {}    
    
    SeqStack(const SeqStack<T> &stack){
        _pstack = new T[stack._capacity];
        _top = stack._top;
        _capacity = stack._capacity;
        for (int i = 0; i <= _top; i++)
            _pstack[i] = stack._pstack[i];
    }
    ~SeqStack(){
        delete[]_pstack;
        _pstack = nullptr;
    }
    SeqStack<T>& operator=(const SeqStack<T>&other){
        if(this!=&other){
            delete[]_pstack;
            _pstack=new T[other._capacity];
            _top=other._top;
            _capacity=other._capacity;
            for(int i=0;i<=_top;++i){
                _pstack[i]=other._pstack[i];
            }
            return *this;
        }
        return *this;
    }
    
    void push(const T &value){
        if(full()){
            expand();
        }
        _pstack[++_top]=value;
    }
    void pop(){
        if(empty()){
            return ;
        }
        _top--;
    }
    T& top()const{
        return _pstack[_top];
    }
    bool empty()const{
        return _top==-1;

    }
    bool full()const{
        return _top==_capacity-1;
    }
private:
    T *_pstack;
    int _top;
    int _capacity;
    void expand(){
        T *_pNewStack=new T[_capacity*2];
        for(int i=0;i<=_top;i++){
            _pNewStack[i]=_pstack[i];
        }
        delete[] _pstack;
        _pstack=_pNewStack;
        _capacity=_capacity*2;
        _pNewStack=nullptr;
    }
};
int main(int argc, const char * argv[]) {
    SeqStack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    while(!stack.empty()){
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;

    return 0;
}