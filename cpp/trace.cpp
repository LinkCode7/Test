using namespace std;

#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)

void log(const TCHAR* format, ...)
{
    /*std::string cstr;
    if (format)
    {
            va_list args;
            va_start(args, format);
            cstr.FormatV(format, args);
            va_end(args);
    }
    fprintf(stderr, "%s\r\n", cstr);*/
}

#ifndef NDEBUG // debug mode
class tracer
{
public:
    tracer(const char* file, int line) : m_file(file), m_line(line) {}

    void operator()(const char* fmt, ...)
    {
        //// print the file name and line number
        // fprintf(stderr, "%s (%d): \r\n", m_file, m_line);

        // va_list ap;
        // va_start(ap, fmt);
        // vfprintf(stderr, fmt, ap);
        // va_end(ap);

        // fprintf(stderr, "\r\n"); // print the new-line character
    }

private:
    // copy-ctor and operator=
    tracer(const tracer&);
    tracer& operator=(const tracer&);

private:
    const char* m_file;
    int         m_line;
};
    #define TRACE (tracer(__FILE__, __LINE__))

#else // NDEBUG

    #define TRACE (void)

#endif // NDEBUG

//////////////////////////////////////////////////////////////////////////
void testTrace()
{
    // 1
    cout << endl << endl << endl;
#ifndef NDEBUG
    tracer(__FILE__, __LINE__)("%x", 123);
#endif
    cout << endl;
    // Equivalent to: tracer(__FILE__, __LINE__)("%s %s", "Happy debugging.","hello");
    TRACE("%s %s", "Happy debugging.", "hello");

    // 2
    cout << endl << endl << endl;
    debug("%s,%s", "4", "5");

    //// 3
    // cout << endl << endl << endl;
    // std::string str("%s %s"), str1("Firse"), str2("Second");
    // log(str, str1, str2);
}
