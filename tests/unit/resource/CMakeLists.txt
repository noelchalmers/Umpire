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

if (ENABLE_GMOCK)
	set (resource_tests_depends
	  umpire umpire_resource umpire_util umpire gtest gmock)

	if (ENABLE_HIP)
	  set (resource_tests_depends
	    ${resource_tests_depends}
	    hip)
	endif ()

  blt_add_executable(
    NAME resource_tests
    SOURCES resource_tests.cpp
    DEPENDS_ON ${resource_tests_depends})

  blt_add_test(
    NAME resource_tests
    COMMAND resource_tests)
endif ()
