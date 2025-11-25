#pragma once

#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <string>

struct operation {
    virtual size_t execute(const std::string& fileName) = 0;
    virtual ~operation() = default;
};

#endif
