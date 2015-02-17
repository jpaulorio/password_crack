# password_crack
Naive OpenCL implementation of a brute force password cracker.

To build the parallel version on Mac just:

gcc password-crack-parallel.c -o bin/password-crack-parallel -framework OpenCL

To build the serial version on Mac just:

gcc password-crack.c -o bin/password-crack -framework OpenCL

Just run the generated binaries inside bin directory and enter the password to be "cracked" when requested.
