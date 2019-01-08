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
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018,2019 Advanced Micro Devices, Inc.
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_HipMallocAllocator_HPP
#define UMPIRE_HipMallocAllocator_HPP

#include <hip/hip_runtime.h>

namespace umpire {
namespace alloc {

/*!
 * \brief Uses hipMalloc and hipFree to allocate and deallocate memory on
 *        AMD GPUs.
 */
struct HipMallocAllocator {
  /*!
   * \brief Allocate bytes of memory using hipMalloc
   *
   * \param bytes Number of bytes to allocate.
   * \return Pointer to start of the allocation.
   *
   * \throws umpire::util::Exception if memory cannot be allocated.
   */
  void* allocate(size_t size)
  {
    void* ptr = nullptr;
    hipError_t error = ::hipMalloc(&ptr, size);
    UMPIRE_LOG(Debug, "(bytes=" << size << ") returning " << ptr);
    if (error != hipSuccess) {
      UMPIRE_ERROR("hipMalloc( bytes = " << size << " ) failed with error: " << hipGetErrorString(error));
    } else {
      return ptr;
    }
  }

  /*!
   * \brief Deallocate memory using hipFree.
   *
   * \param ptr Address to deallocate.
   *
   * \throws umpire::util::Exception if memory cannot be free'd.
   */
  void deallocate(void* ptr)
  {
    UMPIRE_LOG(Debug, "(ptr=" << ptr << ")");
    hipError_t error = ::hipFree(ptr);
    if (error != hipSuccess) {
      UMPIRE_ERROR("hipFree( ptr = " << ptr << " ) failed with error: " << hipGetErrorString(error));
    }
  }
};

} // end of namespace alloc
} // end of namespace umpire

#endif // UMPIRE_HipMallocAllocator_HPP
