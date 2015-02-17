# password_crack
Naive OpenCL implementation of a brute force password cracker.

To build the parallel version on Mac just:

gcc password-crack-parallel.c -o password-crack-parallel -framework OpenCL

To build the serial version on Mac just:

gcc password-crack.c -o password-crack -framework OpenCL

Just run the generated binaries and enter the password to be "cracked" when requested.
