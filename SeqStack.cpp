#include <iostream>
using namespace std;
class SeqStack
{
private:
    /* data */
    int *_pstack;
    int _top;
    int _capacity;

    /* fuction */
    void resize()
    {
        int *_newStack = new int[_capacity * 2];
        for (int i = 0; i < _capacity; i++)
        {
            _newStack[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = _newStack;
        _capacity *= 2;
        _newStack=nullptr;
    }

public:
    SeqStack(int capacity = 15)
    {
        _pstack = new int[capacity];
        _top = -1;
        _capacity = capacity;
    }
    ~SeqStack()
    {
        delete[] _pstack;
        _pstack = nullptr;
    }
    void push(int val)
    {
        if (full())
        {
            resize();
        }
        _pstack[++_top] = val;
    }
    void pop()
    {
        if (empty())
        {
            return;
        }
        _top--;
    }
    int top() const
    {
        return _pstack[_top];
    }
    bool empty() const
    {
        return _top == -1;
    }
    bool full() const
    {
        return _top == _capacity - 1;
    }
};

int main(int argc, char const *argv[])
{
    SeqStack stack_test(5);
    for (int i = 0; i < 5; i++)
    {
        stack_test.push(i);
    }

    stack_test.pop();

    if (!stack_test.empty())
    {
        cout << "Stack top element is" << stack_test.top() << endl;
    }
    return 0;
}