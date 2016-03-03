#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef unsigned int ui32;
typedef unsigned long long int ui64;
typedef unsigned char ui8;

ui32 mod(ui8 *num, ui32 len, ui32 p);

int test1();

int main() {
    srand(time(NULL));
    printf ("test1: %s\n", test1() ? "FAILED" : "PASSED");
	return 0;
}

int test1() {
    ui64 p,q,r,num,y,bnum;
    p = rand() & 0xffffffff;
    q = rand() & 0xffffffff;
    r = rand() % p;
    num = p*q + r;
    bnum = ((num & 0xffffffffLL) << 32) + ((num & ~0xffffffffLL)>>32);
    y = mod((ui8*)&num, 8, p);
    printf("p: %llX, q: %llX, r: %llX, num: %llX, bnum: %llX, y: %llX\n", p, q, r, num, bnum, y);
    return (y != r);
}

/**
  num is a big nummber of length 'len'
  returns a (num % p)
 
 
  we use the fact that a*b (mod p) == [a (mod p) * b (mod p)] (mod p)
  and a+b (mod p) == [a (mod p) + b (mod p)] (mod p)
  */
ui32 mod(ui8 *num, ui32 len, ui32 p) {
    ui64 y=0, t = 1;
    ui32 i;
    ui32 x;
    for(i=0; i<len; i++) {
        x = num[i];
        y = (y+(x*t)) % p;
        t = (t<<8) % p;
        printf("x[%lX]: %lX, t: %llX, p: %lX, y: %llX\n", i, x, t, p, y);
    }
    return y;
}

//ui32 mod(ui8 *num, ui32 len, ui32 p) {
//	ui64 y;
//	ui32 i, _len;
//	ui32 x;
//	ui32 *_num;
//	if (len % 4 != 0) {
//		int t = len % 4;
//		memcpy(((ui8*)&y)+(4-t), num, t);
//		_num = (ui32*)(num+t);
//		_len = (len-t)/4;
//	} else {
//		y = 0;
//		_num = (ui32*)num;
//		_len = len/4;
//	}
//	for(i=0; i<_len; i++) {
//		x = _num[i];
//        printf("x[%lX]: %lX\n", i, x);
//		y = ((y<<32)+x) % p;
//	}
//	return y;
//}
