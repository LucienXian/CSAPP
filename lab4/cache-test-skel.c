/*
YOUR NAME HERE
CSE 351 - Spring 2017
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 16 bytes 
    cache size = 65536 bytes
    associativity = 3
mystery1:
    block size = 4 bytes
    cache size = 16384 bytes
    associativity = 5
mystery2:
    block size = 8 bytes
    cache size = 32768 bytes
    associativity = 9
mystery3:
    block size = 256 bytes
    cache size = 1048576 bytes
    associativity = 257
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address.
 * You should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  int num = 0;
  flush_cache();
  access_cache(0);
  while(access_cache(num)){
	num++;
  }
  return num;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  addr_t addr = 0;
//  flush_cache();
  while(TRUE){
	flush_cache();
 	addr += block_size;
	for (int i=0; i<addr; i++) access_cache(i);
	if (!access_cache(0)) return addr-block_size;
  }
//  return -1;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  int num = 0;
  while(TRUE){
	flush_cache();
	num++;
	for (int i=0; i<num; i++) access_cache(i*cache_size);
	if (!access_cache(0)) return num;
  }
//  return -1;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
