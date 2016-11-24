
#include <iostream>
#include <sys/types.h>
#include <sys/xattr.h>
#include <cstring>
#include <CustomTools/Convert.h>

template <class T>
T get_attribute( std::string filename, std::string attribute, size_t bit_limit=32 )
{
    char value[bit_limit];
    memset(value, 0, sizeof(value));

    if ( !getxattr( filename.c_str(), attribute.c_str(), value, bit_limit, 0, XATTR_NOFOLLOW ) )
        throw "error: could not retrieve file attribute";

    return fromString<double>( std::string(value) );
}

int main(int argc, const char *argv[])
{
    try 
    {
        std::cout << "Frequency: " << get_attribute<double>( "file.dat", "frequency" ) << std::endl;
        std::cout << "      Sum: " << get_attribute<int>( "file.dat", "sum" ) << std::endl;
    } 
    catch ( const char *e ) 
    {
        std::cout << e << std::endl;
    }

    return 0;
}
