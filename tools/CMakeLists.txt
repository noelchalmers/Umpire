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

set (replay_depends
  umpire)

if (ENABLE_HIP)
  set (replay_depends
    ${replay_depends}
    hip)
endif ()

blt_add_executable(
  NAME replay
  SOURCES replay.cpp
  DEPENDS_ON ${replay_depends})
