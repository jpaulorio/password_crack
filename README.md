# Password Crack
### Naive OpenCL implementation of a brute force password cracker.

To build the parallel version on Mac just:

**_gcc password-crack-parallel.c -o bin/password-crack-parallel -framework OpenCL_**

On Linux (Ubuntu):

 **_sudo apt install ocl-icd-opencl-dev_**
 
 **_gcc password-crack-parallel.c -o bin/password-crack-parallel -lOpenCL_**

To build the serial version on Mac or Linux just:

**_gcc password-crack.c -o bin/password-crack_**

Just run the generated binaries **from within the bin directory** and enter the password to be "cracked" when requested.

Parallel GPU version will start making a difference with a password with size 5.