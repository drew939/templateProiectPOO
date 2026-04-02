#pragma once
#include <stdexcept>


class ExceptieFonduriInsuficiente : public std::runtime_error {
public:
    explicit ExceptieFonduriInsuficiente(
        const std::string& msg = "Fonduri insuficiente!")
        : std::runtime_error(msg) {}
};
 
class ExceptieCardBlocat : public std::runtime_error {
public:
    explicit ExceptieCardBlocat(
        const std::string& msg = "Cardul este blocat!")
        : std::runtime_error(msg) {}
};

class ExceptieSumaInvalida : public std::logic_error {
public:
    explicit ExceptieSumaInvalida(
        const std::string& msg = "Suma introdusa este invalida (negativa sau zero)!")
        : std::logic_error(msg) {}
};

