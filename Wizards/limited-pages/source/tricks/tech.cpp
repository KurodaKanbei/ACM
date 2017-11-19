O3优化
#define __ __attribute__ ((optimize("-O3")))
#define _ __ __inline __attribute__ ((__gnu_inline__, __always_inline__, __artificial__))

汇编开栈
#pragma comment(linker, "/STACK:256000000")

int __size = 256 << 20;
char* __p__ = (char *) malloc(__size__) + __size__;

int main() {
	__asm__("movl %0, %%esp\n" :: "r"(__p__));
	return 0;
}
