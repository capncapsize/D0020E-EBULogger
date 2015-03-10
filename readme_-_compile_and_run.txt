The complete system to read and log data from the EBU
through eth.

Non-standard libs:
mongoc.h
	MongoDB C API
bson.h
	Binary JSON document

How to fresh INSTALL the libraries:
//Get dependencies
$sudo apt-get install git gcc automake autoconf libtool

//Build mongo-c-driver
$git clone https://github.com/mongodb/mongo-c-driver.git
$cd monog-c-drive
$./autogen.sh
$make
$sudo make install

//Set GCC-linker path
$LD_LIBRARY_PATH=/usr/local/lib
$export LD_LIBRARY_PATH

How to COMPILE a solution with libmongoc and libbson.
$gcc -o <filename> <filename>.c $(pkg-config --cflags --libs libmongoc-1.0)

Then RUN with
./<filename>

References:
https://github.com/mongodb/libbson/blob/master/src/bson/bson.h
