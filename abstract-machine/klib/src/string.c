#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  const char *str = s;
  while (*str)
  {
    str++;
  }
  return str - s;
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  char *original_dst = dst;

  do {
      *dst = *src;
      dst++;
      src++;
  } while (*(src - 1) != '\0'); 

  return original_dst;
  //panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;
  //if (n == 0) return 
  for (i = 0; i < n && src[i] != '\0'; i++)
    dst[i] = src[i];
  for ( ; i < n; i++)
    dst[i] = '\0';
  return dst;
  //not to reach
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  size_t i;
  for(i = 0;dst[i]!='\0';i++);
  size_t j;
  for(j = 0;src[j]!='\0';j++){
    dst[i+j] = src[j];
  }
  dst[i+j] = '\0';
  return dst;
  //panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return (unsigned char)*s1 - (unsigned char)*s2;
  //panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  if (n == 0) {
    return 0;
  }

  while (n-- > 0 && *s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }

  if (n == (size_t)-1) {
    return 0;
  }
  return (unsigned char)*s1 - (unsigned char)*s2;
  //panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  unsigned char *ptr = (unsigned char *)s;
  unsigned char value = (unsigned char)c;

  while (n-- > 0) {
    *ptr++ = value;
  }
  return s;
  //panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  unsigned char *d = (unsigned char *)dst;
  const unsigned char *s = (const unsigned char *)src;

  // 创建临时缓冲区来存储 src 的内容
  unsigned char temp[n];
    
  // 将 src 的内容复制到临时缓冲区
  for (size_t i = 0; i < n; i++) {
      temp[i] = s[i];
  }

  // 将临时缓冲区的内容复制到 dst
  for (size_t i = 0; i < n; i++) {
    d[i] = temp[i];
  }

  return dst;
  //panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *d = (unsigned char *)out;
  const unsigned char *s = (const unsigned char *)in;

  // 逐字节复制 in 到 out
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return out;
  //panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] - p2[i];
      }
    }

  return 0;
  //panic("Not implemented");
}

#endif
