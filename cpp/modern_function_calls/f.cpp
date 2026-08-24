// cl.exe /std:c++latest f.cpp

#include <string_view>

// struct
// {
//     [[nodiscard]] auto operator[](
//         std::string_view what, std::string_view name) const -> std::string
//     {
//         return std::string{what} + ", " + std::string{name} + "!";
//     }
// } say_d_to;

// say_d_to["Goodbye", "Tony"]; // -> "Goodbye, Tony!"

[[nodiscard]] auto say_a_to(
    std::string_view what, std::string_view name)
    -> std::string
{
    return std::string{what} + ", " + std::string{name} + "!";
}

int main()
{
    say_a_to("Hi", "Kate"); // -> "Hi, Kate!"
}