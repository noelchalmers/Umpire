//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
//
// Created by David Beckingsale, david@llnl.gov
// LLNL-CODE-747640
//
// All rights reserved.
//
// This file is part of Umpire.
//
// For details, see https://github.com/LLNL/Umpire
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////
#include "umpire/config.hpp"

#include "umpire/resource/DeviceResourceFactory.hpp"

#include "umpire/resource/DefaultMemoryResource.hpp"

#if defined(UMPIRE_ENABLE_CUDA)
#include "umpire/alloc/CudaMallocAllocator.hpp"
#endif

#if defined(UMPIRE_ENABLE_HIP)
#include "umpire/alloc/HipMallocAllocator.hpp"
#endif

namespace umpire {
namespace resource {

bool
DeviceResourceFactory::isValidMemoryResourceFor(const std::string& name)
{
  if (name.compare("DEVICE") == 0) {
    return true;
  } else {
    return false;
  }
}

std::shared_ptr<MemoryResource>
DeviceResourceFactory::create(const std::string& UMPIRE_UNUSED_ARG(name), int id)
{
#if defined(UMPIRE_ENABLE_CUDA)
  return std::make_shared<resource::DefaultMemoryResource<alloc::CudaMallocAllocator> >(Platform::cuda, "DEVICE", id);
#elif defined(UMPIRE_ENABLE_HIP)
  return std::make_shared<resource::DefaultMemoryResource<alloc::HipMallocAllocator> >(Platform::hip, "DEVICE", id);
 #endif
}

} // end of namespace resource
} // end of namespace umpire
