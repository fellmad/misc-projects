// hello.cpp by Bill Weinman <http://bw.org/>

#include <cstdio>

void message(const char *s)
{
    puts(s);
    fflush(stdout);
}

int main()
{
    message("Hello, World!");
}