#pragma once

#include <functional>

template <typename T>
bool findEntity(T *collection, uint16_t size, T *result, std::function<bool(T)> itterator)
{
    uint16_t i = 0;

    if (size < 1)
        return false;

    while (i < size)
    {
        if (itterator(collection[i]))
        {
            *result = collection[i];
            return true;
        }
        i++;
    }

    return false;
}