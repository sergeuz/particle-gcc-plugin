/*
 * Copyright (C) 2017 Particle Industries, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "util/string.h"
#include "common.h"

#include <exception>

namespace particle {

class Error: public std::exception {
public:
    Error();
    explicit Error(std::string msg);

    template<typename... ArgsT>
    explicit Error(const std::string& fmt, ArgsT&&... args);

    const std::string& message() const;

    virtual const char* what() const noexcept override;

private:
    std::string msg_;
};

} // namespace particle

inline particle::Error::Error() {
}

inline particle::Error::Error(std::string msg) :
        msg_(std::move(msg)) {
}

template<typename... ArgsT>
inline particle::Error::Error(const std::string& fmt, ArgsT&&... args) :
        msg_(format(fmt, std::forward<ArgsT>(args)...)) {
}

inline const std::string& particle::Error::message() const {
    return msg_;
}

inline const char* particle::Error::what() const noexcept {
    return msg_.data();
}
