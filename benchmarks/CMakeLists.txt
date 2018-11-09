##############################################################################
# Copyright (c) 2018, Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory
#
# Created by David Beckingsale, david@llnl.gov
# LLNL-CODE-747640
#
# All rights reserved.
#
# This file is part of Umpire.
#
# For details, see https://github.com/LLNL/Umpire
# Please also see the LICENSE file for MIT license.
##############################################################################

set (stress_test_depends umpire)
set (benchmark_depends umpire gbenchmark)

if (ENABLE_HIP)
  set (stress_test_depends
    ${stress_test_depends}
    hip)
  set (benchmark_depends
    ${benchmark_depends}
    hip)
endif ()

blt_add_executable(
  NAME allocator_stress_test
  SOURCES allocator_stress_test.cpp
  DEPENDS_ON ${stress_test_depends}
  OUTPUT_DIR ${UMPIRE_BENCHMARK_OUTPUT_DIR})

blt_add_executable(
  NAME copy_stress_test
  SOURCES copy_stress_test.cpp
  DEPENDS_ON ${stress_test_depends}
  OUTPUT_DIR ${UMPIRE_BENCHMARK_OUTPUT_DIR})

blt_add_executable(
  NAME allocator_benchmarks
  SOURCES allocator_benchmarks.cpp
  DEPENDS_ON ${benchmark_depends}
  OUTPUT_DIR ${UMPIRE_BENCHMARK_OUTPUT_DIR})

blt_add_executable(
  NAME debuglog_benchmarks
  SOURCES debuglog_benchmarks.cpp
  DEPENDS_ON ${benchmark_depends}
  OUTPUT_DIR ${UMPIRE_BENCHMARK_OUTPUT_DIR})

blt_add_benchmark(
  NAME allocator_benchmarks
  COMMAND allocator_benchmarks)

blt_add_executable(
  NAME copy_benchmarks
  SOURCES copy_benchmarks.cpp
  DEPENDS_ON ${benchmark_depends}
  OUTPUT_DIR ${UMPIRE_BENCHMARK_OUTPUT_DIR})

blt_add_benchmark(
  NAME copy_benchmarks
  COMMAND copy_benchmarks)
