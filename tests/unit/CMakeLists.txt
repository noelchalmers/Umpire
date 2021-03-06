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
###############################################################################
# Copyright (c) 2018,2019 Advanced Micro Devices, Inc.
###############################################################################

set (resource_manager_tests_depends
  umpire gtest)

if (ENABLE_HIP)
  set (resource_manager_tests_depends
    ${resource_manager_tests_depends}
    hip)
endif ()

blt_add_executable(
  NAME resource_manager_tests
  SOURCES resource_manager_tests.cpp
  DEPENDS_ON ${resource_manager_tests_depends})

blt_add_test(
  NAME resource_manager_tests
  COMMAND resource_manager_tests)

add_subdirectory(alloc)
add_subdirectory(op)
add_subdirectory(resource)
add_subdirectory(util)
