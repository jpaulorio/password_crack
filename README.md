# password_crack
## Naive OpenCL implementation of a brute force password cracker.

To build the parallel version on Mac just:

**_gcc password-crack-parallel.c -o bin/password-crack-parallel -framework OpenCL_**

To build the serial version on Mac just:

**_gcc password-crack.c -o bin/password-crack -framework OpenCL_**

Just run the generated binaries from within the bin directory and enter the password to be "cracked" when requested.