#include <window.hpp>

bool cryptdata::less()
{
    return this->current < this->capacity;
}

bool cryptdata::maximum()
{
    return this->current == this->capacity;
}

bool cryptdata::overflow()
{
    return this->current > this->capacity;
}

size_t cryptdata::difference()
{
    return this->capacity - this->current;
}

size_t cryptdata::rdifference()
{
    return this->current - this->capacity;
}
