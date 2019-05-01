#ifndef _MEMORY_H
#define _MEMORY_H

// this is here so that, in the future, these functions could be swapped out
// (for example, if this were to run under userspace, it can't use kernel memory functions)

#include "memory/kmalloc.h"

#define ALLOC kmalloc
#define FREE kfree

#endif