#include <cstdio>
#include <dlfcn.h>

namespace
{

class LibraryGuard
{
public:
    LibraryGuard(const char *path)
    : _path(path)
    , _handle(dlopen(path, RTLD_NOW))
    {
        if (!_handle)
            perr("LibraryGuard()");
    }

    ~LibraryGuard()
    {
        const int ret = dlclose(_handle);
        if (ret)
            perr("~LibraryGuard()");
    }

    template<typename T>
    T sym(const char *const symbol)
    {
        void *const p = dlsym(_handle, symbol);
        if (!p)
        {
            perr("sym()");
        }
        return reinterpret_cast<T>(p);
    }

private:

    void perr(const char *const msg)
    {
        std::fprintf(stderr, "%s: %s: %s\n", _path, msg, dlerror());
    }

    const char *const _path;
    void *const _handle;
};

} // namespace

typedef int (*func_t) (int);

int main()
{
    LibraryGuard ence("libence.dylib");
    func_t func = ence.sym<func_t>("func");
    if (func)
    {
        std::printf("one: %d\n", func(69));
    }
    return 0;
}
