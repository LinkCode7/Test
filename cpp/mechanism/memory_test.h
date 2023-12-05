#ifndef MEMORY_TEST_H
#define MEMORY_TEST_H

// #define USING_MEMORY_MANAGEMENT

#ifdef USING_MEMORY_MANAGEMENT

    #include <cstdio>
    #include <cstdlib>
    #include <new>

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz)
{
    std::printf("1) new(size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void* ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}

// no inline, required by [replacement.functions]/3
void* operator new[](std::size_t sz)
{
    std::printf("2) new[](size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void* ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* ptr) noexcept
{
    std::puts("3) delete(void*)");
    std::free(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept
{
    std::printf("4) delete(void*, size_t), size = %zu\n", size);
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    std::puts("5) delete[](void* ptr)");
    std::free(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
    std::printf("6) delete[](void*, size_t), size = %zu\n", size);
    std::free(ptr);
}

#endif // USING_MEMORY_MANAGEMENT

#endif // !MEMORY_TEST_H
