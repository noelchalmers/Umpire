.. _tutorial::

===============
Umpire Tutorial
===============

This tutorial introduces the Umpire library and its components, and shows you
how to get up and running using Umpire in your own code. To get started, make
sure you have Umpire built and installed, and take a look at the Basic Usage
section of the Geting Started document.

-----------------
Basic Allocations
-----------------

Allocation memory using Umpire is done through ``Allocator`` objects. These
objects control how and where the memory is allocated, and are constructed and
stored by the ``ResourceManager``. Depending on how you configured Umpire, a
number of default allocators will always be available. For example:

.. code-block:: cpp

  auto& rm = umpire::ResourceManager::getInstance();
  umpire::Allocator allocator = rm.getAllocator(umpire::resource::Host);

will grab the default allocator for host memory. You can use this to allocate
and deallocate memory, which will be accessible by the CPU:

.. code-block:: cpp

  double* my_data = allocator.allocate(100*sizeof(double*));

  // use my_data

  allocator.deallocate(my_data);

If you built Umpire with ``-DENABLE_CUDA=On``, then three other allocators will
be available:

.. code-block:: cpp

  umpire::Allocator device_allocator = rm.getAllocator(umpire::resource::Device);

  umpire::Allocator unified_allocator = rm.getAllocator(umpire::resource::UnifiedMemory);

  umpire::Allocator pinned_allocator = rm.getAllocator(umpire::resource::PinnedMemory);

These allocators can be used to allocate and deallocate data in exactly the
same way as the host allocator. However, the accessibility of this data will
vary depending on the system. Please see the 

---------------------
Requesting Allocators
---------------------

As well as requesting the default allocators by the ``resource::``-prefixed
type, they can also be requested by name and id. The default allocators all
have uppercase names:

.. code-block:: cpp

  umpire::Allocator allocator = rm.getAllocator("HOST");

If you don't know the name of an Allocator, you can find out:

.. code-block:: cpp

  std::cout << "Allocator name is: " << allocator.getName() << std::endl;

Allocators also have a unique integer id:

.. code-block:: cpp

  std::cout << "Allocator id is: " << allocator.getId() << std::endl;

This id can also be used to request the Allocator from the ResourceManager:

.. code-block:: cpp

  // allocator_by_id and allocator are the same
  umpire::Allocator allocator_by_id = rm.getAllocator(allocator.getId());

In summary, here are the available Allocators:

==== ==== ===========
Name Enum Description
==== ==== ===========
Host ``resource::Host`` Uses the default system allocator (malloc) to allocate CPU memory
Device ``resource::Device`` Uses cudaMalloc to allocate memory on the default CUDA device
Pinned ``resource::PinnedMemory`` Uses cudaMallocHost to allocate CPU memory that can be accessed by CPU or GPUs
Unified ``resource::UnifiedMemory`` Uses cudaMallocManaged to allocate memory accessible to CPU and GPUs
==== ==== ===========


------------
Deallocation
------------

It is an error to try and deallocate a pointer with a different Allocator than
the one used to allocate it. However, if you need to deallocate a pointer and
you don't know where it came from, you can just use the ResourceManager:

.. code-block:: cpp

  double* my_random_ptr;

  // allocate my_random_ptr anywhere

  rm.deallocate(my_random_ptr);


Note that performing the deallocation this way will incur some overhead, since
the ResourceManager needs to identify the correct Allocator to perform the
deallocation

---------------------
Allocation Strategies
---------------------

Umpire supports building Allocators using ``AllocationStrategy`` objects,
letting you make allocations with various pooling mechanisms to help improve
application performance. New allocators can be created using the
ResourceManager's makeAllocator call:

.. code-block:: cpp

  umpire::Allocator pool_alloc = rm.makeAllocator(
    "my_pool", 
    "POOL", 
    {0,0,0}, 
    {rm.getAllocator("HOST")});

----------
Operations
----------

.. code-block:: cpp

  auto& rm = umpire::ResourceManager::getInstance();
  rm.copy();

