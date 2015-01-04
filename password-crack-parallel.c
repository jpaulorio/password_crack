//gcc password-crack-parallel.c -o password-crack-parallel -framework OpenCL
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

#define PASSWORD_SIZE (4)
#define LAST_CHAR (127)

unsigned long ipow(int base, int exp)
{
    unsigned long result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

int main ()
{
  char build_c[4096];
  time_t t1;
  time_t t2;

  size_t maxKernelWorkGroupSize;

  int passwordSize = PASSWORD_SIZE;
  int lastChar = LAST_CHAR;

  printf("Type a password: ");

  char password[PASSWORD_SIZE + 1];
  char crackedPassword[PASSWORD_SIZE + 1];

  scanf("%s", &password);

  time(&t1);
  printf("Cracking password\n");
  unsigned long maxScanSize = ipow(LAST_CHAR + 1, PASSWORD_SIZE);
  //printf("maxScanSize->%lu\n", maxScanSize);
////////////////////

  cl_device_id device_id = NULL;
  cl_context context = NULL;
  cl_command_queue command_queue = NULL;
  cl_mem memobjInput = NULL;
  cl_mem memobjOutput = NULL;
  cl_program program = NULL;
  cl_kernel kernel = NULL;
  cl_platform_id platform_id = NULL;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret;
 
  FILE *fp;
  char fileName[] = "./password-crack.cl";
  char *source_str;
  size_t source_size;

  /* Load the source code containing the kernel*/
  fp = fopen(fileName, "r");
  if (!fp) {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }
  source_str = (char*)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);
 
  /* Get Platform and Device Info */
  ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
 
  /* Create OpenCL context */
  context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
  /* Create Command Queue */
  command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 
  /* Create Memory Buffer */
  memobjInput = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(char) * (PASSWORD_SIZE+1), NULL, &ret);
  memobjOutput = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(char) * (PASSWORD_SIZE+1), NULL, &ret);

  // Copy the lists A and B to their respective memory buffers
  ret = clEnqueueWriteBuffer(command_queue, memobjInput, CL_TRUE, 0, sizeof(char) * (PASSWORD_SIZE+1), password, 0, NULL, NULL);
 
  /* Create Kernel Program from the source */
  program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
 
  /* Build Kernel Program */
  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 
 if ( ret != CL_SUCCESS ) {
                printf( "Error on buildProgram " );
                printf("\n Error number %d", ret);
                fprintf( stdout, "\nRequestingInfo\n" );
                clGetProgramBuildInfo( program, device_id, CL_PROGRAM_BUILD_LOG, 4096, build_c, NULL );
                printf( "Build Log for %s_program:\n%s\n", "example", build_c );
        }

  /* Create OpenCL Kernel */
  kernel = clCreateKernel(program, "passwordCrack", &ret);
 
  // print max kernel work group size
  clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE,
          sizeof(maxKernelWorkGroupSize), &maxKernelWorkGroupSize, NULL);
  printf("Max kernel work group size: %lu\n", maxKernelWorkGroupSize);


  /* Set OpenCL Kernel Arguments */
  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobjInput);
  ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&memobjOutput);
  ret = clSetKernelArg(kernel, 2, sizeof(unsigned long), (void *)&maxScanSize);  
  ret = clSetKernelArg(kernel, 3, sizeof(int), (void *)&passwordSize);  
  ret = clSetKernelArg(kernel, 4, sizeof(int), (void *)&lastChar);
  
  /* Set kernel dimensions */
  size_t globalThreads[1] = {512*512};
  size_t localThreads[1] = {512};
 
  /* Execute OpenCL Kernel */  
  clEnqueueNDRangeKernel(command_queue, kernel, 1, 0, globalThreads, localThreads, 0, 0, 0);

  /* Copy results from the memory buffer */
  ret = clEnqueueReadBuffer(command_queue, memobjOutput, CL_TRUE, 0, (PASSWORD_SIZE + 1) * sizeof(char), &crackedPassword, 0, NULL, NULL);  

  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(memobjInput);
  ret = clReleaseMemObject(memobjOutput);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
 
  free(source_str);
 
////////////////////  

  printf("\nPassword is: %s\n", crackedPassword);

  time(&t2);
  printf("total time: %lu\n", t2-t1);

  return 0;
}