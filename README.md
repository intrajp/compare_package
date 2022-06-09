compare_package

# Requirements

```
 You need these packages.

 autoconf
 intltool
 libtool

 How to build:

 $ ./autogen.sh
 $ ./configure
 $ make

Program Name: compare_package

  Compare 2 package versions.

  ./compare_package <package version a> <package version b> 

  (Ex)
  ./compare_package 2.2.10-1 2.2.10-2

  Return value

  0: same
  11: a is greater than b 
  12: b is greater than a 

# There is no install script please use in the current directory. 

# cleaning

 $ make clean-local
```
