#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
extern Area heap;

static uintptr_t current_addr = 0;

void *malloc(size_t size) {
  /*The malloc() function allocates size bytes and returns a pointer to the allocated memory.  
  The memory is not initialized.  If size is 0, then malloc() returns either NULL, or a unique pointer
  value that can later be successfully passed to free().
*/
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
//#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))

  if (size == 0) return NULL; // 如果大小为0，返回NULL
  if (current_addr == 0) {
    current_addr = (uintptr_t)heap.start; // 初始化时将地址设置为堆的起始地址
  }
  
  // 对齐到4字节边界
  size = (size + 3) & ~0x3;

  // 检查堆空间是否足够
  if (current_addr + size > (uintptr_t)heap.end) {
    return NULL; // 堆空间不足
  }

  void *allocated_addr = (void*)current_addr;
  
  // 更新current_addr
  current_addr += size;

  return allocated_addr;

  //panic("Not implemented");
//#endif
  // malloc_init();
  // return NULL;
}

void free(void *ptr) {
}

#endif
#endif
