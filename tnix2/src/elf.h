#include "common.h"
#include <elf.h>
#include "fs.h"
#include "paging.h"
#include "kheap.h"
int exec(char *path);