#pragma once

#include <list>

typedef void(*FuncPtr)();

namespace std
{
    class event
    {
    private:
        std::list<FuncPtr> functions;

    public:
        void operator+=(FuncPtr f)
        {
            Add(f);
        }

        void operator-=(FuncPtr f)
        {
            Remove(f);
        }

        void Add(FuncPtr f)
        {
            for (FuncPtr _f : functions)
            {
                if (_f == f)
                {
                    // Already here
                    return;
                }
            }
            functions.push_back(f);
        }

        void Remove(FuncPtr f)
        {
            bool canRemove = false;

            for (FuncPtr _f : functions)
            {
                if (_f == f)
                {
                    canRemove = true;
                    break;
                }
            }

            if (canRemove)
                functions.remove(f);
        }

        void Invoke()
        {
            for (FuncPtr f : functions)
            {
                f();
            }
        }

        void operator()()
        {
            for (FuncPtr f : functions)
            {
                f();
            }
        }

        void Clear()
        {
            functions.clear();
        }

        ~event()
        {
            functions.clear();
        }
    };
}
