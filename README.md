# photo-album

# Author: Justin Kirkegaard

# License:

Copyright 2020 Justin Kirkegaard

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## <ins>About</ins>

This project is a technology showcase for LEAN Techniques.  Detailed documentation is hosted by Github Pages [here](https://this-photo-album.github.io/photo-album-docs/index.html).

This project relies heavily on open source software and tools. Acknowledgements to 

* Build system using [CMake](https://cmake.org "CMake")
* Unit testing using [Catch2](https://github.com/catchorg/Catch2/ "Catch2")
* Code coverage reports using [LCOV](http://ltp.sourceforge.net/coverage/lcov.php "LCOV")
* Documentation using [Doxygen](http://www.doxygen.nl "Doxygen")
* [doxygen_dark_theme]( https://github.com/MaJerle/doxygen-dark-theme "doxygen_dark_theme" ) written by MaJerle 
* Continuous Integration using [Travis.CI](https://travis-ci.org/ "Travis.CI" )

## <ins>Instructions</ins>
Create a console application that displays photo ids and titles in an album. The photos are available in this online web
service:  <https://jsonplaceholder.typicode.com/photos>

<b>Hint:</b> Photos are filtered with a query string. This will return photos within albumId=3:  <https://jsonplaceholder.typicode.com/photos?albumId=3>

You can use any language
Any open source libraries
Unit tests are encouraged
Post your solution on any of the free code repositories and send us a link:
* https://github.com/
* https://gitlab.com/
* https://bitbucket.org/

Provide a README that contains instructions on how to build and run your application
Spend as much (or little) time as you'd like on this. Feel free to use any resources available.

```
Example:
> photo-album 2
[53] soluta et harum aliquid officiis ab omnis consequatur
[54] ut ex quibusdam dolore mollitia
...
> photo-album 3
[101] incidunt alias vel enim
[102] eaque iste corporis tempora vero distinctio consequuntur nisi nesciunt
```
## <ins>Building</ins>

CMake is the build system used for building the photo-album application.  To build the project, use the following commands: 
```
<photo-album project root>$ cmake -B build
<photo-album project root>$ cmake --build build
```
This will build the project without tests, coverage or generated documentation in the directory `<photo-album project root>/build`.

The generated target is a static library by default. To build a shared library instead of a static library, add the cmake option `-DBUILD_SHARED_LIBS=ON` to the generate (first) command.

Tests, coverage report and generated documentation can be enabled by setting the desired option as defined in the root CMakeLists.txt file. To generate the build with all options enabled, invoke the following command:  
```
    <photo-album project root>$ cmake -B build -DBUILD_TESTS=ON -DBUILD_COVERAGE_REPORT=ON -DBUILD_DOCUMENTATION=ON`  
```
## <ins>Usage</ins>
From the command line, and after building the project, invoke the following command:  
```
<photo-album project root>$ build/photo-album/photo-album <album_id> 
    where <album_id> is an integer >= 0.
```
 The application will:
* Initiate an HTTP connection with the photo service
* Construct and send a GET request with the specified album_id
* Receive the returned data
* Parse the returned data
* Print the parsed data to the console.

## <ins>Testing</ins>

Testing is accomplished using the Catch2 C++ testing framework. Tests can be built by setting the `BUILD_TESTS` option defined in the project's root CMakeLists.txt to `ON`. The tests are built and run with the following commands:
```
    <photo-album_root>$ cmake -B build -DBUILD_TESTS=ON
    <photo-album_root>$ cmake --build build
    <photo-album_root>$ build/test__all
```