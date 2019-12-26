/*
** EPITECH PROJECT, 2019
** Exception.hpp
** File description:
**
*/

#ifndef MY_BABEL_EXCEPTION_HPP
#define MY_BABEL_EXCEPTION_HPP

class CannotLoadResource : public std::exception
{
    public:
        explicit CannotLoadResource(std::string  filename = "") noexcept
                : _filename {std::move(filename)} {};
        [[nodiscard]] const char *what() const noexcept override { return (_filename.c_str()); }
    private:
        std::string _filename;
};

#endif //MY_BABEL_EXCEPTION_HPP
