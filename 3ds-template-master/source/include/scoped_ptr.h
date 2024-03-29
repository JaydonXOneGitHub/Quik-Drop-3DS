#ifndef SCOPED_PTR
#define SCOPED_PTR

template<typename PtrType>
class ScopedPtr
{
private:
    PtrType* ptr;

public:
    PtrType* operator->()
    {
        return ptr;
    }

    PtrType& Base()
    {
        return *ptr;
    }

    explicit ScopedPtr(PtrType* ptr) : ptr(ptr) {}
    ScopedPtr(const ScopedPtr&) = delete;
    ScopedPtr(const ScopedPtr&&) = delete;
    ~ScopedPtr() { delete ptr; }
};

template<typename PtrType>
PtrType& operator*(const ScopedPtr<PtrType>& scopedPtr)
{
    return scopedPtr.Base();
}

#endif