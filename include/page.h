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

typedef uint32_t pd_t;
typedef uint32_t pte_t;
typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;
extern pte_t pg_table_start;
extern pte_t pg_table_end;
extern pd_t pg_dir_start;
extern pd_t pg_dir_end;
uint32_t align = 0xfffff000;
extern void load_cr3(uint32_t ptr);


/*
Thus function essentially setups the pd_ts for the first 1 GiB
*/
void instantiate_pd_t(pd_t* pd_t_start, pte_t* pte_t_start, uint32_t num){ //pte_t_start is the first pte
  for(uint32_t i = 0; i<num; i++){
    *pd_t_start = (uint32_t)pte_t_start & 0xFFFFF000; // get 4kib aligned address
    *pd_t_start |= 0x3; //read intel manual Volume 3 page 115 (PDF)
    pte_t_start += 1024;
    pd_t_start++;
  }
    print_number((uint32_t)pte_t_start);
    print_number((uint32_t)&pg_table_start);
    print_number((uint32_t)pd_t_start);
    print_number((uint32_t)&pg_dir_start);

}

void map_page(phys_addr_t paddr, virt_addr_t vaddr,  uint8_t rw, pd_t* pd_t_start){ //all pages that are identity mapped are supervisor. For rw, read is 0 read/write is 1
  vaddr = vaddr & 0xFFFFF000; //make 4 kib aligned
  uint32_t pd_offset = ((uint32_t)vaddr & 0xFFC00000) >> 22; //get top 10 bits
  uint32_t pte_offset = ((uint32_t)vaddr & 0x3FF000) >> 12; //get middle 10 bits
  pd_t* pd = pd_t_start + pd_offset;
  pte_t* pte_base = (pte_t*)(*pd & 0xFFFFF000);
  pte_t* pte = pte_base + pte_offset; //this is the pte we need to manipulate
  *pte = paddr & 0xFFFFF000;

  *pte |= 0x1;//(0x1 | (rw << 1)) ; //read intel manual Volume 3 page 115 (PDF)



}


void paging_init(){ //identity maps 1st GiB
  uint32_t addr_lim = 0x40000000; //1 GiB. Increment by 0x1000 which is 4096 bytes.
  //uint32_t addr_count = 0x0;
  instantiate_pd_t(&pg_dir_start, &pg_table_start, 1024); //create 1GiB of pd_t
              //increment pd until we hit 256 as we need 256 pd_t to represent 1 GiB
  for(uint32_t addr_count = 0x0 ; addr_count < addr_lim; addr_count += 0x1000){ //1024 ptes per pd_t. Identity map first 1MiB
    map_page(addr_count, addr_count, 0, &pg_dir_start);

  }

  print_number(&pg_dir_start);
  load_cr3((uint32_t)&pg_dir_start);

}
