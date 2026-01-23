// memcpy的实现

// C语言中 "memcpy函数 - void *memcpy(void *dest, const void *src, size_t count)" 是最基础和常见的内存/数据拷贝函数。

// 但是当dest与src地址有重叠的时候，"memcpy函数" 会因为自我覆盖而导致无法正确拷贝，这时需要 "memmove" 函数来完成正确的拷贝。

// 请设计实现memmove函数 - "void *memmove(void *dest, const void *src, size_t count)", 解决dest与src地址有重叠时正确拷贝的问题。
#include <stdio.h>
#include <stddef.h>  
void* memmove(void* dest, const void* src, size_t count) {
    // 这个代码我很好理解
    if(count == 0) {
        // 移动0个那就不需要
        return NULL;
    }
    char* dest_t = (char*)dest;
    const char* src_t = (const char*)src;

    if(dest_t == src_t) return dest;
    else if(dest_t < src_t) {
        //在前面 那可以直接从前往后拷贝就行了
        for(int i = 0; i < count; i++) {
            dest_t[i] = src_t[i];
        }
    }
    else {
        for(int i = count - 1; i >= 0; i--) {
            dest_t[i] = src_t[i];
        }
    }
    return dest;
}


// void *memmove(void *dest, const void *src, size_t count) {
       // 这个版本也没有问题的 为什么昨天代码没有a出来
       // 那个ai不好用还是豆包好用 写的代码我tm看不懂槽
//     // 空指针保护
//     if (dest == NULL || src == NULL || count == 0) {
//         return dest;
//     }
//     printf("this is second\n");
//     char *d = (char *)dest;
//     const char *s = (const char *)src;

//     // 判断内存是否重叠：dest 在 src 区间内（src < dest < src + count）
//     if (d > s && d < s + count) {
//         // 从后往前拷贝，避免覆盖未拷贝的源数据
//         d += count - 1;
//         s += count - 1;
//         while (count--) {
//             *d-- = *s--;
//         }
//     } else {
//         // 无重叠或 dest 在 src 之前，从前往后拷贝
//         while (count--) {
//             *d++ = *s++;
//         }
//     }

//     return dest;
// }


int main() {
    // 测试场景1：内存重叠（dest在src后面）
    char buf[10] = "123456789";
    printf("原数据：%s\n", buf);
    // 拷贝buf[0~4]（"12345"）到buf[2~6]，预期结果："121234589"
    memmove(buf + 2, buf, 5);
    printf("重叠拷贝后：%s\n", buf);

    // 测试场景2：无重叠
    char src[] = "abcdef";
    char dest[10] = {0};
    memmove(dest, src, 6);
    printf("无重叠拷贝后：%s\n", dest); // 预期：abcdef

    // 测试场景3：dest在src前面（无重叠）
    char buf2[10] = "987654321";
    memmove(buf2, buf2 + 2, 5); // 拷贝"76543"到buf2[0~4]
    printf("dest在src前拷贝后：%s\n", buf2); // 预期：765434321

    return 0;
}