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
        vector(int size = 10){
            _first=_allocator.allocate(size);
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
           // verify(_last - 1, _last);
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
           // friend class vector<T, Alloc>;
            iterator(T *ptr = nullptr) : _ptr(ptr) {}
#if 0
            iterator(vector<T, Alloc> *pVec = nullptr, T *ptr = nullptr) : _pVec(pVec), _ptr(ptr)
            {
                Iterator_Base *itb = new Iterator_Base(this, _pVec->_head._next);
                _pVec->_head._next = itb;
            }
#endif
            bool operator!=(const iterator &it) const
            {
                /*  if (_pVec == nullptr || _pVec != it._pVec)
                 {
                     throw("iterator incompatible vectors");
                 } */
                return _ptr != it._ptr;
            }

            void operator++()
            {
                /* if (_pVec == nullptr)
                {
                    throw("iterator incompatible vectors");
                } */
                ++_ptr;
            }
            T &operator*() const
            {
                /* if (_pVec == nullptr)
                {
                    throw("iterator incompatible vectors");
                } */
                return *_ptr;
            }

        private:
            //  vector<T, Alloc> *_pVec;
            T *_ptr;
        };
        iterator begin() const { return iterator(_first); }
        iterator end() const { return iterator(_last); }
#if 0
        iterator begin() const { return iterator(this, _first); }
        iterator end() const { return iterator(this, _last); }
        void verify(T *first, T *last) const
        {
            Iterator_Base *pre = &this->_head;
            Iterator_Base *it = this->_head._next;
            while (it != nullptr)
            {
                if (it->_cur->_ptr >= first && it->_cur->ptr <= last)
                {
                    it->_cur->_pVec = nullptr;
                    pre->_next = it->_next;
                    delete it;
                    it = pre->_next;
                }
                else
                {
                    pre = it;
                    it = it->_next;
                }
            }
        }
        iterator insert(iterator it, const T &value)
        {
            /* 不考虑扩容
               不考虑it._ptr的指针合法性
             */
            verify(it._ptr - 1, _last);
            T *p = _last;
            while (p > it._ptr)
            {
                _allocator.construct(p, *(p - 1));
                _allocator.destroy(p - 1);
                p--;
            }

            _allocator.construct(p, value);
            _last++;
            return iterator(this, p);
        }
        iterator erase(iterator it)
        {
            /* 不考虑it._ptr的指针合法性
               保证最后一个元素可以安全删除
               注意it._ptr在vector中可能不是_first
             */
            verify(it._ptr - 1, _last);
            T *p = it._ptr;
            while (p < _last - 1)
            {
                _allocator.destroy(p);
                _allocator.construct(p, *(p + 1));

                p++;
            }
            _allocator.destroy(p);
            _last--;
            return iterator(this, it._ptr);
        }
#endif
    private:
        T *_first;
        T *_last;
        T *_end;
        Alloc _allocator;
#if 0
        struct Iterator_Base
        {
            Iterator_Base(iterator *c = nullptr, Iterator_Base *n = nullptr) : _cur(c), _next(n) {}
            iterator *_cur;
            Iterator_Base *_next;
        };
        Iterator_Base _head;
#endif
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
    cout << v2[1] << endl;
    me::vector<int> v3(10);
    for (int i = 0; i < v3.size(); i++)
    {
        v3.push_back(rand() % 100);
    }
    me::vector<int>::iterator it = v3.begin();
    for (; it != v3.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (auto p : v3)
    {
        cout << p << " ";
    }
#if 0
    me::vector<int> vec(30);
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec.push_back(i * 2);
    }
    me::vector<int> vec1(vec);
    auto it2 = vec.begin();
    for (; it != vec.end(); ++it2)
    {
        if (*it2 % 2 == 0)
        {
            it2 = vec.insert(it2, *it2 - 1);
            ++it2;
        }
    }
    auto it3 = vec1.begin();
    while (it3 != vec1.end())
    {
        if (*it3 % 2 == 0)
        {
            it3 = vec1.erase(it3);
        }
        else
        {
            ++it3;
        }
    }
#endif
    return 0;
}