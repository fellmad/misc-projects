#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>

int main()
{
    std::printf("Strings:\n");

    const char* s = "Hello";
    std::printf("\t.%10s.\n\t.%-10s.\n\t.%*s.\n", s, s, 10, s);

    std::printf("Characters:\t%c %%\n", 65);

    std::printf("Integers\n");
    std::printf("Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1);
    std::printf("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    std::printf("Octal:\t%o %#o %#o\n", 10, 10, 4);

    std::printf("Floating point\n");
    std::printf("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    std::printf("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    std::printf("Scientific:\t%E %e\n", 1.5, 1.5);
    std::printf("Hexadecimal:\t%a %A\n", 1.5, 1.5);

    //    std::printf("Special values:\t0/0=%g 1/0=%g\n", 0. / 0, 1. / 0);  // compile error C2124
    {
        float f {1.0};
        int intzero {0};
        auto r1 {0.0 / intzero};
        auto r2 {1.0 / intzero};
        std::printf("Special values:\t0/0=%g 1/0=%g\n", r1, r2);
    }

    std::printf("Variable width control:\n");
    std::printf("right-justified variable width: '%*c'\n", 5, 'x');
    int r = std::printf("left-justified variable width : '%*c'\n", -5, 'x');
    std::printf("(the last printf printed %d characters)\n", r);

    // fixed-width types
    std::uint32_t val = std::numeric_limits<std::uint32_t>::max();
    std::printf("Largest 32-bit value is %" PRIu32 " or %#" PRIx32 "\n", val, val);

    {
        // http://en.cppreference.com/w/cpp/numeric/math/nan
        double f1 = std::nan("1");
        std::uint64_t f1n;
        std::memcpy(&f1n, &f1, sizeof f1);
        std::cout << "nan(\"1\") = " << f1 << " (" << std::hex << f1n << ")\n";

        double f2 = std::nan("2");
        std::uint64_t f2n;
        std::memcpy(&f2n, &f2, sizeof f2);
        std::cout << "nan(\"2\") = " << f2 << " (" << std::hex << f2n << ")\n";
    }
}