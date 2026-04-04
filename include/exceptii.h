#pragma once
#include <stdexcept>
#include<string>

class ExceptieFonduriInsuficiente : public std::runtime_error {
    public:
        ExceptieFonduriInsuficiente(const std::string& msg = "Fonduri insuficiente!") : std::runtime_error(msg) {}
};
 
class ExceptieCardBlocat : public std::runtime_error {
    public:
        ExceptieCardBlocat(const std::string& msg = "Cardul este blocat!") : std::runtime_error(msg) {}
};

class ExceptieSumaInvalida : public std::logic_error {
    public:
        ExceptieSumaInvalida(const std::string& msg = "Suma introdusa este invalida!") : std::logic_error(msg) {}
};

class ExceptieClientNegasit : public std::runtime_error {
    public:
        ExceptieClientNegasit(const std::string& msg = "Clientul nu a fost gasit!") : std::runtime_error(msg) {}
};

class ExceptieVarstaInvalida : public std::logic_error {
    public:
        ExceptieVarstaInvalida(const std::string& msg = "Varsta clientului este invalida!") : std::logic_error(msg) {}
};