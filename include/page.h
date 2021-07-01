/*
Documentation:
In paging there are 2 data structures: the page table entry and the page directory. Each page directory can point to 1024 page entires. Each page obviously points to a 4 KiB block in physical memory.
The reason for this 1024 limitation is that the address in the pd_t is 4KiB aligned meaning that each pd has 4KiB to work in. And, due to the fact that each pte is 4 bytes, each page directory can hold a total of 1024 ptes.

Thus, doing the math, we come to the following numbers

There are 256 ptes in a MiB.

Thus, each page directory can map 4 MiB (256*4 = 1024).

Thus, you need 256 page directories to map 1 GiB of address space (1024 MiB in GiB).

Thus, a 4 GiB address spaces fits cleanly into 4KiB of page directories or 1024 page directories.

Putting everything together, we realize that the page table for a 4 GiB address space will be at minimum 4 KiB + 4 KiB * 1024 * 1024(4 KiB for the page directories data structures and 4 KiB per set of page table entires).

Thus, you need a little over 1 MiB to map the entire 4 GiB address space. Not bad.


A good way to think about it is that a pd_t represents a page of pte_t.


*/


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint32_t phys_addr_t;
extern struct pte_t pg_table_start;
extern struct pte_t pg_table_end;
extern struct pd_t pg_dir_start;
extern struct pd_t pg_dir_end;

uint32_t align = 0xfffff000;
struct pte_t{
  uint16_t access:9;
  uint8_t avail:2;
  uint32_t phys_addr:20;
}__attribute__ ((packed));

struct pd_t{
  uint16_t access:9;
  uint8_t avail:2;
  phys_addr_t pte_addr:20;
}__attribute__ ((packed));


void instantiate_pd_t(struct pd_t* pd_t_start, struct pte_t* pte_t_start, uint32_t num){
  for(uint32_t i = 0; i<num; i++, pd_t_start++, pte_t_start += 1024/*A pte_t is 4 bytes so incrementing this by 1024 will increment it by a page*/){
    pd_t_start->pte_addr = (uint32_t)pte_t_start >> 12; // shift by 12 because this is a 4kb aligned address
  }
}

struct pte_t* identity_map_page(struct pd_t* pd, uint32_t pte_offset, phys_addr_t addr, uint32_t access_byte){ //all pages that are identity mapped are supervisor.
  if(addr % 4096 != 0){ //check if 4 kib aligned
    return NULL;
  }
  return NULL;

}

void paging_init(){ //identity maps 1st GiB
  struct pd_t* pd_ptr = &pg_dir_start;
  uint32_t addr_lim = 0x40000000; //1 GiB. Increment by 0x1000 which is 4096 bytes.
  uint32_t addr_count = 0x0;
  for(uint32_t pd_count = 0 ; pd_count<256; pd_count++,pd_ptr++){ //increment pd until we hit 256 as we need 256 pd_t to represent 1 GiB
    for(uint32_t pte_offset_count = 0 ; pte_offset_count < 1024; pte_offset_count++){


      addr_count += 0x1000;
    }
  }

}
