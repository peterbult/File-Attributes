// 
// FileAttributes.h
// CustomTools
//
// Created by PM Bult on 02-04-2014
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.1
//

#pragma once
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <cstring>
#include <CustomTools/Convert.h>

namespace {
    bool has_attribute( std::string filename, std::string attribute, size_t bit_limit=1024 )
    {
        char buffer[bit_limit];
        memset(buffer, 0, sizeof(buffer));

        int num = listxattr( filename.c_str(), buffer, bit_limit, 0 );
        if ( num < 0 ) throw "error: could not access file attributes";
        if ( num == 0 ) return false;

        std::string element;
        for (int i = 0; i < bit_limit; ++i) {
            if (buffer[i] == '\0' ) {
                if ( !element.empty() ) {
                    if ( element.compare(attribute) == 0 ) {
                        return true;
                    }
                    element.clear();
                }
            } else {
                element += buffer[i];
            }
        }

        return false;
    }

    template <class T>
    T get_attribute( std::string filename, std::string attribute, size_t bit_limit=32 )
    {
        char value[bit_limit];
        memset(value, 0, sizeof(value));

        if ( !getxattr( filename.c_str(), attribute.c_str(), value, bit_limit, 0, 0 ) )
            throw "error: could not retrieve file attribute";

        return fromString<T>( std::string(value) );
    }

    template <class T>
    void set_attribute( std::string filename, std::string attribute, T value )
    {
        const char *val_str = toString<T>(value).c_str();

        if ( setxattr( filename.c_str(), attribute.c_str(), val_str, strlen(val_str), 0, 0 ) )
            throw "error: could not set file attribute";

        return;
    }
}

