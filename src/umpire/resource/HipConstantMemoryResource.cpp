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

#include "umpire/resource/HipConstantMemoryResource.hpp"

#include "umpire/ResourceManager.hpp"
#include "umpire/util/Macros.hpp"

#include <memory>
#include <sstream>

__constant__ char umpire_internal_device_constant_memory[64*1024];

namespace umpire {
namespace resource {

HipConstantMemoryResource::HipConstantMemoryResource(const std::string& name, int id, MemoryResourceTraits traits) :
  MemoryResource(name, id, traits),
  m_current_size(0l),
  m_highwatermark(0l),
  m_platform(Platform::hip),
  m_offset(0),
  m_ptr(nullptr)
{
  // hipError_t error = hipGetSymbolAddress((void**)&m_ptr, umpire_internal_device_constant_memory);

  // if (error != hipSuccess) {
  //   UMPIRE_ERROR("hipGetSymbolAddress failed with error: " << hipGetErrorString(error));
  // }
  m_ptr = &umpire_internal_device_constant_memory;
}

void* HipConstantMemoryResource::allocate(size_t bytes)
{
  char* ptr = static_cast<char*>(m_ptr) + m_offset;
  m_offset += bytes;

  void* ret = static_cast<void*>(ptr);

  if (m_offset > 1024 * 64)
  {
    UMPIRE_ERROR("Max total size of constant allocations is 64KB, current size is " << m_offset - bytes << "bytes");
  }

  ResourceManager::getInstance().registerAllocation(
      ret, new util::AllocationRecord{ret, bytes, this->shared_from_this()});

  m_current_size += bytes;
  if (m_current_size > m_highwatermark)
    m_highwatermark = m_current_size;

  UMPIRE_LOG(Debug, "(bytes=" << bytes << ") returning " << ret);

  return ret;
}

void HipConstantMemoryResource::deallocate(void* ptr)
{
  UMPIRE_LOG(Debug, "(ptr=" << ptr << ")");

  util::AllocationRecord* record = ResourceManager::getInstance().deregisterAllocation(ptr);
  m_current_size -= record->m_size;

  if ( (static_cast<char*>(m_ptr) + (m_offset - record->m_size))
      == static_cast<char*>(ptr)) {
    m_offset -= record->m_size;
  } else {
    UMPIRE_ERROR("HipConstantMemory deallocations must be in reverse order");
  }

  delete record;
}

long HipConstantMemoryResource::getCurrentSize() noexcept
{
  UMPIRE_LOG(Debug, "() returning " << m_current_size);
  return m_current_size;
}

long HipConstantMemoryResource::getHighWatermark() noexcept
{
  UMPIRE_LOG(Debug, "() returning " << m_highwatermark);
  return m_highwatermark;
}

Platform HipConstantMemoryResource::getPlatform() noexcept
{
  return m_platform;
}

} // end of namespace resource
} // end of namespace umpire
