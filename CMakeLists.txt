cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(coremark)

target_compile_options(app PRIVATE "-fno-asm")
target_compile_options(app PRIVATE "-fsigned-char")

target_compile_options(app PRIVATE "-D USE_CRC_TABLE")
target_compile_options(app PRIVATE "-D NDEBUG")
target_compile_options(app PRIVATE "-D HOST_EXAMPLE_CODE=1")
target_compile_options(app PRIVATE "-D HAVE_SYS_STAT_H=1")
target_compile_options(app PRIVATE "-D USE_NATIVE_PTHREAD=1")
target_compile_options(app PRIVATE "-D GCC_INLINE_MACRO=1")
target_compile_options(app PRIVATE "-D NO_RESTRICT_QUALIFIER=1")

if(CONFIG_64BIT)
  target_compile_options(app PRIVATE "-D EE_SIZEOF_LONG=8")
  target_compile_options(app PRIVATE "-D EE_SIZEOF_PTR=8")
  target_compile_options(app PRIVATE "-D EE_PTR_ALIGN=8")
endif()

# Debug facilities
# target_compile_options(app PRIVATE "-D REPORT_THMALLOC_STATS=1")
# target_compile_options(app PRIVATE "-D BMDEBUG=1")
# target_compile_options(app PRIVATE "-D THDEBUG=1")
# target_compile_options(app PRIVATE "-D VERBOSE=1")

set_ifndef(W_WORKERS_NUM 4)
target_compile_options(app PRIVATE "-D W_WORKERS_NUM=${W_WORKERS_NUM}")

set_ifndef(C_CONTEXT_NUM 4)
target_compile_options(app PRIVATE "-D C_CONTEXT_NUM=${C_CONTEXT_NUM}")

set_ifndef(I_ITERATION_NUM 1)
target_compile_options(app PRIVATE "-D I_ITERATION_NUM=${I_ITERATION_NUM}")

# MITH headers
include_directories(mith/include)
include_directories(mith/al/include)

# MITH sorces
FILE(GLOB mith_sources mith/al/src/*.c mith/src/*.c)
target_sources(app PRIVATE ${mith_sources})

# Input arguments
target_sources(app PRIVATE main-args.c)

# CoreMark Pro sources
if(CONFIG_CMP_COREMARK)
  FILE(GLOB app_sources benchmarks/core/*.c)
  target_sources(app PRIVATE ${app_sources})
  target_sources(app PRIVATE workloads/core/core.c)
endif()
