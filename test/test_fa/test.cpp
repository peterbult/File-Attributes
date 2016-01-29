

#include <iostream>
#include <sys/types.h>
#include <sys/xattr.h>
#include <CustomTools/Convert.h>

bool has_attribute( std::string filename, std::string attribute, size_t bit_limit=1024 )
{
    char buffer[bit_limit];
    memset(buffer, 0, sizeof(buffer));

    int num = listxattr( filename.c_str(), buffer, bit_limit, XATTR_NOFOLLOW );
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

int main(int argc, const char *argv[])
{
    try 
    {
        std::cout << std::boolalpha;
        std::cout << "file has [frequency]: " << has_attribute( "file.dat", "frequency" ) << std::endl;
        std::cout << "      file has [sum]: " << has_attribute( "file.dat", "sum" ) << std::endl;
        std::cout << "    file has [count]: " << has_attribute( "file.dat", "count" ) << std::endl;
    } 
    catch ( const char *e ) 
    {
        std::cout << e << std::endl;
    }

    return 0;
}
