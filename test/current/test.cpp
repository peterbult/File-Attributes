

#include <iostream>
#include "../../src/FileAttributes.h"

int main(int argc, const char *argv[])
{
    try 
    {
        std::cout << "Testing [FileAttributes.h]" << std::endl;
        std::cout << std::endl;
        std::cout << "Creating [file.dat]" << std::endl;
        std::cout << std::endl;

        FILE *os = fopen( "file.dat", "w" );
        for ( int i = 0; i < 10; i++ ) fprintf( os, "%i\n", i+1 );
        fclose(os);

        std::cout << "Write attributes to [file.dat]" << std::endl;
        std::cout << std::endl;

        set_attribute<int>(         "file.dat", "count", 10 );
        set_attribute<double>(      "file.dat", "sum",   55.0 );
        set_attribute<std::string>( "file.dat", "type",  "list" );

        std::cout << "Testing for attributes in [file.dat]" << std::boolalpha << std::endl;
        std::cout << "file has [count]: " << has_attribute( "file.dat", "count" ) << std::endl;
        std::cout << "  file has [sum]: " << has_attribute( "file.dat", "sum" ) << std::endl;
        std::cout << " file has [type]: " << has_attribute( "file.dat", "type" ) << std::endl;
        std::cout << std::endl;

        std::cout << "Reading attributed from [file.dat]" << std::endl;
        int count        = get_attribute<int>(          "file.dat", "count" );
        double sum       = get_attribute<double>(       "file.dat", "sum" );
        std::string type = get_attribute<std::string>(  "file.dat", "type" );
        std::cout << "count: " << count << std::endl;
        std::cout << "  sum: " << sum << std::endl;
        std::cout << " type: " << type << std::endl;
    } 
    catch ( const char *e ) 
    {
        std::cout << e << std::endl;
    }

    return 0;
}
