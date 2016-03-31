#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    const size_t PAGE_SIZE = (size_t)getpagesize();
    printf("PAGE_SIZE %zu\n", PAGE_SIZE);
    size_t cnt = 0;
    size_t result = 0;
    size_t i = ULONG_MAX;
    while (i != 0) {
    	size_t len = i - (i % PAGE_SIZE);
    	char* p = mmap(NULL, len, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    	if (p != MAP_FAILED) {
    		cnt += 1;
    		result += len;
    	} else {
    		i /= 2;		
    	}
    }
    printf("result %zu\n", result);
    printf("alloc %zu\n", cnt);

    return 0;
}
