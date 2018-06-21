btCHange
=========

A simple Qt5 program to display the BTC/EUR currencies change each 10 secs.

### Getting Started

Create the Makefile by running:
```
qmake
```

Compile the project by running:
```
make
```
Execute by running:
```
./btCHange
```

### Tests
To test the functionality of the project:

```
cd test && qmake ../btCHange.pro "CONFIG +=test"
```

then do a make:
```
make
```

and finally running the test:
```
./btCHangeTests
```
