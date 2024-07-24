#include <iostream>
using namespace std;
namespace me
{
    /*容器的空间配置器allocateor做四件事 内存分配/释放  对象构造/析构*/
    template <typename T>
    class Allocator
    {
    public:
        T *allocate(size_t size)
        {
            return static_cast<T *>(::operator new(size * sizeof(T)));
        }
        void deallocate(T *ptr)
        {
            ::operator delete(ptr);
        }
        void construct(T *ptr, const T &value)
        {
            new (ptr) T(value);
        }
        void destroy(T *ptr)
        {
            ptr->~T();
        }
    };

    template <typename T = int, typename Alloc = Allocator<T>>
    class vector
    {
    public:
        vector(int size = 10)
        {
            _first = _allocator.allocate(size);
            _last = _first;
            _end = _first + size;
        }
        vector(const vector<T> &other)
        {
            _first = _allocator.allocate(other.size());
            int len = other._last - other._first;
            for (int i = 0; i < len; i++)
            {
                _allocator.construct(_first + i, other._first[i]);
            }
            _last = _first + len;
            _end = _first + other.size();
        }
        vector<T> &operator=(const vector<T> &other)
        {
            if (this != &other)
            {
                if (_first != nullptr)
                {
                    for (T *p = _first; p != _last; ++p)
                    {
                        _allocator.destroy(p);
                    }
                    _allocator.deallocate(_first);
                }
                _first = _allocator.allocate(other.size());
                int len = other._last - other._first;
                for (int i = 0; i < len; i++)
                {
                    _allocator.construct(_first + i, other._first[i]);
                }
                _last = _first + len;
                _end = _first + other.size();
            }
            return *this;
        }
        void push_back(const T &value)
        {
            if (full())
            {
                expand();
            }
            _allocator.construct(_last, value);
            _last++;
        }
        void pop_back()
        {
            if (empty())
            {
                return;
            }
            _last--;
            _allocator.destroy(_last);
        }
        T back() const
        {
            return *(_last - 1);
        }
        bool empty() const
        {
            return _first == _last;
        }
        bool full() const
        {
            return _last == _end;
        }
        int size() const { return _end - _first; }
        ~vector()
        {
            for (T *p = _first; p != _end; ++p)
            {
                _allocator.destroy(p);
            }
            _allocator.deallocate(_first);
            _first = _last = _end = nullptr;
        }
        T &operator[](int index) const
        {
            if (index < 0 || index >= size())
                throw std::out_of_range("index out of range");
            return _first[index];
        }
        class iterator
        {
        public:
            iterator(T *ptr = nullptr) : _ptr(ptr) {}
            bool operator!=(const iterator &other) const { return _ptr!= other._ptr; }
            void operator++() { ++_ptr; }
            T& operator*() const { return *_ptr; }
        private:
            T *_ptr;
        };
        iterator begin() const { return iterator(_first); }
        iterator end() const { return iterator(_last); }
    private:
        T *_first;
        T *_last;
        T *_end;
        Alloc _allocator;
        void expand()
        {
            int newSize = size() * 2;
            T *newData = _allocator.allocate(newSize);
            int len = _last - _first;
            for (int i = 0; i < len; i++)
            {
                _allocator.construct(newData + i, _first[i]);
            }
            for (T *p = _first; p != _last; ++p)
            {
                _allocator.destroy(p);
            }
            _first = newData;
            _last = _first + len;
            _end = _first + newSize;
        }
    };
}

int main()
{

    me::vector<int> v1(5);
    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
    }
    while (!v1.empty())
    {
        cout << v1.back() << " ";
        v1.pop_back();
    }
    cout << endl;
    me::vector<int> v2(v1);
    v1.push_back(10);
    cout << v2.back() << endl;
    cout<<v2[1]<<endl;
    me::vector<int> v3(10);
    for(int i=0;i<v3.size();i++){
        v3.push_back(rand()%100);
    }
    me::vector<int>::iterator it = v3.begin();
    for(;it!=v3.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
    for(auto p:v3){
        cout<<p<<" ";
    }
    return 0;
}