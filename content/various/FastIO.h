/**
 * Author: shjohw12
 * Description: Fast IO
 */
#pragma once

#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>

// 00~99
const char dgt[] = "00010203040506070809101112131415161718...";
const int BUF_SZ = 1 << 20;
char readbuf[BUF_SZ], writebuf[BUF_SZ];
char* INPUT = readbuf, * OUTPUT = writebuf;

// mmap
inline void get(signed& n) {
	n = 0;
	bool flag = false;
	if (*INPUT == '-') {
		flag = true;
		++INPUT;
	}
	for (char i = *INPUT++; i & 16; n = (n << 1) + (n << 3) + (i & 15), i = *INPUT++);
	if (flag) {
		n = -n;
	}
}

// write
inline void put(int n) {
	int SZ = OUTPUT - writebuf;
	if (BUF_SZ - SZ < 25) {
		write(1, writebuf, SZ);
		OUTPUT = writebuf;
	}
	if (n == 0) {
		*OUTPUT++ = '0';
		return;
	}
	if (n < 0) {
		*OUTPUT++ = '-';
		n = -n;
	}
	char* tmp = OUTPUT;
	for (int i = (n % 100) << 1; n > 99; n /= 100, i = (n % 100) << 1) {
		*OUTPUT++ = dgt[i | 1];
		*OUTPUT++ = dgt[i];
}
	if (n > 9) {
		n <<= 1;
		*OUTPUT++ = dgt[n | 1];
		*OUTPUT++ = dgt[n];
	}
	else if (n > 0) {
		*OUTPUT++ = n | 48;
	}
	reverse(tmp, OUTPUT);
}

// in main function
struct stat stt; fstat(0, &stt);
INPUT = (char*)mmap(0, stt.st_size, PROT_READ, MAP_SHARED, 0, 0);

int TC; get(TC);
while (TC--) {
	int a, b;
	get(a); get(b);
	put(a + b); *OUTPUT++ = '\n';
}

write(1, writebuf, OUTPUT - writebuf);
