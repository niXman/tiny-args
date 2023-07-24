
// ----------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2022-2023 niXman (github dot nixman at pm dot me)
// This file is part of TinyArgs(github.com/niXman/named-args) project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ----------------------------------------------------------------------------

#include <named-args/named-args.hpp>

#include <string>
#include <cassert>
#include <cstring>

/*************************************************************************************************/

struct {
    NAMEDARGS_ARG(fname, std::string);
    NAMEDARGS_ARG(ipaddr, std::string);
    NAMEDARGS_ARG(mode, int);
} const holders;

/*************************************************************************************************/

template<typename ...Args>
NAMEDARGS_FUNC_ENABLE(Args..., holders.fname)
(bool) process_data(Args &&...a) {
    auto args = std::make_tuple(std::forward<Args>(a)...);

    // required arg
    auto name = namedargs::get(holders.fname, args);

    // the default value will be used if `mode` was not specified
    auto mode = namedargs::get(holders.mode, holders.mode = 'e', args);

    return !name.empty() && mode == 'e';
}

template<typename ...Args>
NAMEDARGS_FUNC_ENABLE(Args..., holders.ipaddr)
(bool) process_data(Args &&...a) {
    auto args = std::make_tuple(std::forward<Args>(a)...);

    // required arg
    auto ipaddr = namedargs::get(holders.ipaddr, args);

    // the default value will be used if `mode` was not specified
    auto mode = namedargs::get(holders.mode, holders.mode = 'e', args);

    return !ipaddr.empty() && mode == 'e';
}

/*************************************************************************************************/

int main(int argc, char **argv) {
    assert(argc == 3);

    bool src_is_ip = std::isalnum(argv[1][0]);

    bool ok = src_is_ip
        ? process_data(
             holders.ipaddr = argv[1]
            ,holders.mode   = argv[2][0])
        : process_data(
             holders.fname = argv[1]
            ,holders.mode = argv[2][0])
    ;
    assert(ok);

    return ok;
}

/*************************************************************************************************/
