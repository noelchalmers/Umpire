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
set (example_depends umpire)

if (ENABLE_HIP)
  set (example_depends
    ${example_depends}
    hip)
endif ()

blt_add_executable(
  NAME malloc
  SOURCES malloc.cxx
  DEPENDS_ON 
    ${example_depends})

blt_add_executable(
  NAME strategy_example
  SOURCES strategy_example.cpp
  DEPENDS_ON
    ${example_depends})

if (ENABLE_FORTRAN)
  blt_add_executable(
    NAME allocator_c
    SOURCES allocator.c
    DEPENDS_ON
      ${example_depends}
  )
endif ()

blt_add_executable(
  NAME vector_allocator
  SOURCES vector_allocator.cpp
  DEPENDS_ON 
    ${example_depends})

if (ENABLE_STATISTICS)
  blt_add_executable(
    NAME statistics_example
    SOURCES statistics.cpp
    DEPENDS_ON ${example_depends})
endif()
