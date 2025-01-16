#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <unistd.h> 

//#if !defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__)
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  char buffer[4096];  // 临时缓冲区
  va_list ap;
  va_start(ap, fmt);
  int result = vsnprintf(buffer, sizeof(buffer), fmt, ap);
  va_end(ap);
  for( int i = 0;i < strlen(buffer);i++){
    putch(buffer[i]);
  }
  //fputs(buffer, stdout);  // 将缓冲区输出到标准输出
  return result;
  //panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out, (size_t)-1, fmt, ap);  // 传递一个无限大长度
  //panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int result = vsprintf(out, fmt, ap);
  va_end(ap);
  return result;
  //panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}


static int int_to_str(int value, char *str, size_t max_len) {
    int pos = 0;
    char temp[20];
    int i = 0;

    if (value < 0) {
        if (pos < max_len - 1) {
            str[pos++] = '-';
        }
        value = -value;
    }

    do {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);

    while (i > 0 && pos < max_len - 1) {
        str[pos++] = temp[--i];
    }

    str[pos] = '\0';
    return pos;
}


// int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
//   size_t pos = 0;  // large of out(-1)

//   while (*fmt) {
//   if (*fmt == '%') {
//     fmt++;  //jump and fetch the following token
//     if (*fmt == 'd') {
//       int value = va_arg(ap, int);  // 提取整数参数
//       char buffer[20];
//       //int len = snprintf(buffer, sizeof(buffer), "%d", value);  // 将整数转为字符串
//       int len = int_to_str(value, buffer, sizeof(buffer));
//       for (int i = 0; i < len && pos < n - 1; i++) {
//       out[pos++] = buffer[i];
//       }
//     } else if (*fmt == 's') {
//       const char *str = va_arg(ap, const char *);  // 提取字符串参数
//       while (*str && pos < n - 1) {
//         out[pos++] = *str++;
//       }
//     }
//     // add more here
//   } else {
//   if (pos < n - 1) {
//     out[pos++] = *fmt;
//     }
//   }
//   fmt++;
//   }
//   out[pos] = '\0';  // 添加终止符
//   return pos;
//   //panic("Not implemented");
// }

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    size_t pos = 0;  // Position in the output string

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;  // Jump and fetch the following token

            // Initialize padding width and zero flag
            int width = 0;
            int zero_padding = 0;

            // Check for zero padding
            if (*fmt == '0') {
                zero_padding = 1;
                fmt++;
            }

            // Check for width specifier (e.g., 2 in %02d)
            if (*fmt >= '1' && *fmt <= '9') {
                width = *fmt - '0';
                fmt++;
                while (*fmt >= '0' && *fmt <= '9') {
                    width = width * 10 + (*fmt - '0');
                    fmt++;
                }
            }

            if (*fmt == 'd') {
                int value = va_arg(ap, int);  // Extract the integer argument
                char buffer[20];

                int len = int_to_str(value, buffer, sizeof(buffer));
                int padding = (width > len) ? width - len : 0;

                // If zero padding is specified, fill with '0'
                if (zero_padding) {
                    for (int i = 0; i < padding && pos < n - 1; i++) {
                        out[pos++] = '0';
                    }
                }

                // Copy the integer string
                for (int i = 0; i < len && pos < n - 1; i++) {
                    out[pos++] = buffer[i];
                }

            } else if (*fmt == 's') {
                const char *str = va_arg(ap, const char *);  // Extract the string argument
                while (*str && pos < n - 1) {
                    out[pos++] = *str++;
                }
            } else if (*fmt == 'c') {
                char ch = (char) va_arg(ap, int);  // Extract the char argument
                if (pos < n - 1) {
                    out[pos++] = ch;  // Copy the character to the output buffer
                }
            }
            
            // Add more format specifiers here if needed
        } else {
            if (pos < n - 1) {
                out[pos++] = *fmt;
            }
        }
        fmt++;
    }

    out[pos] = '\0';  // Add the null terminator
    return pos;
}
#endif
