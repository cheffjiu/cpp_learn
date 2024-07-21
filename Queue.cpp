#include <iostream>
using namespace std;
class Queue
{
public:
    Queue(int size = 10)
    {
        _pQueue = new int[size];
        _front = _rear = 0;
        _capacity = size;
    }
    Queue(const Queue &other)
    {
        _capacity = other._capacity;
        _front = other._front;
        _rear = other._rear;
        _pQueue = new int[_capacity];
        for (int i = _front; i != _rear; i = (i + 1) % _capacity)
        {
            _pQueue[i] = other._pQueue[i];
        }
    }
    Queue &operator=(const Queue &other)
    {
        if (this != &other)
        {
            delete[] _pQueue;
            _capacity = other._capacity;
            _front = other._front;
            _rear = other._rear;
            _pQueue = new int[_capacity];
            for (int i = _front; i != _rear; i = (i + 1) % _capacity)
            {
                _pQueue[i] = other._pQueue[i];
            }
            return *this;
        }
        return *this;
    }
    ~Queue()
    {
        delete[] _pQueue;
        _pQueue = nullptr;
    }
    void enqueue(int value)
    {
        if (full())
        {
            resize();
        }
        _pQueue[_rear] = value;
        _rear = (_rear + 1) % _capacity;
    }
    void dequeue()
    {
        if (empty())
        {
            return;
        }
        _front = (_front + 1) % _capacity;
    }
    int front() const
    {
        if (empty())
        {
            return -1;
        }
        return _pQueue[_front];
    }
    bool full() const
    {
        return (_rear + 1) % _capacity == _front;
    }
    bool empty() const
    {
        return _front == _rear;
    }

private:
    int *_pQueue;
    int _front;
    int _rear;
    int _capacity;
    void resize()
    {
        int *pNewQueue = new int[_capacity * 2];
        int index = 0;
        for (int i = _front; i < _rear; i = (i + 1) % _capacity)
        {
            pNewQueue[index++] = _pQueue[i];
        }
        delete[] _pQueue;
        _pQueue = pNewQueue;
        _front = 0;
        _rear = index;
        _capacity *= 2;
    }
};
int main(int argc, char const *argv[])
{

    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5); 
    cout << "Front: " << q.front() << endl;
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl;
    Queue q2(q);
    cout << "Front of q2: " << q2.front() << endl;
    q2 = q;
    cout << "Front of q2 after assignment: " << q2.front() << endl;

    return 0;
}