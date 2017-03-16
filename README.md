# e8yesearch
e8yes search engine.

### English Corpus Used
http://www.anc.org/data/masc/downloads/data-download/

### Reqired libraries
Unix environment is assumed.

###### CPPCMS
Download the CPPCMS source code from:
https://sourceforge.net/projects/cppcms/files/cppcms/1.0.5/

run the following (Assuming you have cmake installed):
```
cmake -G "Unix Makefiles"
make
make test
make install
```

Note: "make install" requires root privilege.

###### boost
```
apt-get install libboost-dev
apt-get install libboost-test-dev
```

###### Eigen
```
apt-get install libeigen3-dev
```

###### Xerces-C++
```
apt-get install libxerces-c-dev
```

###### JSON Spirit
Download the source code from:
https://github.com/cierelabs/json_spirit

run the following
```
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
# Now install the include files and libraries to the system path
cp libjson.a /usr/local/lib
cd ..
cp ciere /usr/local/include
```

(Some of the commands may require root privilege, unix environment is assumed).
