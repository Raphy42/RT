//
// Created by Raphaël Dantzer on 07/07/16.
//

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
# include <OpenCL/cl.h>
#else
# include <CL/cl.h>
#endif

#define VECTOR_SIZE 1024

const char *saxpy_kernel = =