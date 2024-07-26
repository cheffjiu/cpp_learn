#include <iostream>
#include <cstdlib>
template <typename T>
class Queue
{
private:
    struct QueueItem
    {
        T _data;
        QueueItem *_next;
        static const int POOL_ITEM_SIZE = 1000;
        static QueueItem *_itemPool;
        QueueItem(T data) : _data(data), _next(nullptr) {}
        void *operator new(size_t size)
        {
            if (_itemPool == nullptr)
            {
                _itemPool = (QueueItem *)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];

                QueueItem *p = _itemPool;
                for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p)
                {
                    p->_next = p + 1;
                }
                p->_next = nullptr;
            }
            QueueItem *cur = _itemPool;
            _itemPool = cur->_next;
            return cur;
        }
        void operator delete(void *ptr)
        {
            QueueItem *p = static_cast<QueueItem *>(ptr);
            p->_next = _itemPool;
            _itemPool = p;
        }
    };
    QueueItem *_front;
    QueueItem *_rear;

public:
    Queue() : _front(nullptr), _rear(nullptr)
    {
        _front = _rear = new QueueItem(0);
    }
    ~Queue()
    {
        QueueItem *cur = _front;
        while (cur != nullptr)
        {
            _front = _front->_next;
            delete cur;
            cur = _front;
        }
    }
    void push(const T &val)
    {
        QueueItem *new_item = new QueueItem(val);
        _rear->_next = new_item;
        _rear = new_item;
    }
    void pop()
    {
        if (empty())
            return;
        QueueItem *temp = _front->_next;
        _front->_next = _front->_next->_next;
        if (_front->_next == nullptr)
            _rear = _front;
        delete temp;
    }
    T front() const
    {
        return _front->_next->_data;
    }
    bool empty() const
    {
        return _front->_next == nullptr;
    }
};
template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;
int main()
{
    Queue<int> que;
    /* 这个for（）不断的进行了QueueItem对象的构造析构，频繁的对内存进行操作，
    产生一个想法：构建一个QueueItem的对象池 */
    for (int i = 0; i < 10000; ++i)
    {
        que.push(i);
        que.pop();
    }
    std::cout << "que.empty()" <<que.empty()<< std::endl;
    return 0;
}