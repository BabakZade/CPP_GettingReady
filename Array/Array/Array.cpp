#include "pch.h"
#include <iostream>
#include "Matrix.h"

int main()
{
    try
    {
        Matrix a(2, 2);
        a.setValues({ 1, 2, 3, 4 });

        Matrix b(2, 2);
        b.setValues({ 5, 6, 7, 8 });

        Matrix c = a + b;

        std::cout << "Matrix c:" << std::endl;
        std::cout << c.getValue(0, 0) << " " << c.getValue(0, 1) << std::endl;
        std::cout << c.getValue(1, 0) << " " << c.getValue(1, 1) << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}