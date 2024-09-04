#ifndef CURLPARSINGERROR_H
#define CURLPARSINGERROR_H

#include "../stdafx.h"

class CUrlParsingError : public std::invalid_argument
{
public:
    explicit CUrlParsingError(const std::string& message)
            : std::invalid_argument(message)
    {
    }

    ~CUrlParsingError() noexcept override = default;
};

#endif // CURLPARSINGERROR_H