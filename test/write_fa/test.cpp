

#include <iostream>
#include <sys/types.h>
#include <sys/xattr.h>
#include <cstring>
#include <CustomTools/Convert.h>

template <class T>
void set_attribute( std::string filename, std::string attribute, T value )
{
    const char *val_str = toString<T>(value).c_str();

    if ( setxattr( filename.c_str(), attribute.c_str(), val_str, strlen(val_str), 0, XATTR_NOFOLLOW ) )
        throw "error: could not set file attribute";

    return;
}

int main(int argc, const char *argv[])
{
    try 
    {
        set_attribute( "file.dat", "frequency", 0.0625 );
        set_attribute( "file.dat", "sum", 402 );
    } 
    catch ( const char *e ) 
    {
        std::cout << e << std::endl;
    }

    return 0;
}
