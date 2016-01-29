
## File Attributes

This tool provides a set of functions for easy access to the extended
file attributes on Mac OS X. 

#### Usage
Say you have a file for which you know that an `encoding` keyword should
be stored as an extended attribute. It is easy to check that this keyword
is really present

```cpp
string filename = my_file.dat;

if ( has_attribute( filename, "encoding" ) ) {
    /* do something... */
}
```

If the keyword is indeed found, read out by using

```cpp
auto encoding = get_attribute<string>( filename, "encoding" );
```

Now, after fiddling with the file for a bit, suppose you want to add a
checksum

```cpp
unsigned int checksum = 56569;

set_attribute( filename, "checksum", checksum );
```

#### Another example

Suppose you have a few numeric arrays which you want to write to a
binary file. It might be useful to store some of the data properties in
the file attributes, so that you'll be able to decipher the binary
later on.

```cpp
string filename = "my_binary.dat";

vector<float> my_data_1( 120 );
vector<float> my_data_2( 64 );

// Store data as binary

set_attribute( filename, "format", "float32" );
set_attribute( filename, "arrays", 2 );
set_attribute( filename, "size1", my_data_1.size() );
set_attribute( filename, "size2", my_data_2.size() );

```

#### Note
This tools works as a wrapper around some of the functions of OS X's
version of the BSD `xattr` tool (see [man page][apple-xattr] for more
information).

Because extended file attributes are platform depended (both on OS and
file system...) they are not very portable nor very robust. I wouldn't
rely on them for anything vital, nonetheless, on occasion they are 
useful to add some extra info to binary files.

[apple-xattr]: https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man1/xattr.1.html

