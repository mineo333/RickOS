#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "page.h"

uint32_t align = 0xfffff000;

void instantiate_pd_t(pd_t* pd_t_start, pte_t* pte_t_start, uint32_t num){ //pte_t_start is the first pte
  for(uint32_t i = 0; i<num; i++){
    *pd_t_start = (uint32_t)pte_t_start & 0xFFFFF000; // get 4kib aligned address
    *pd_t_start |= 0x3; //read intel manual Volume 3 page 115 (PDF)
    pte_t_start += 1024;
    pd_t_start++;
  }
}

void map_page(phys_addr_t paddr, virt_addr_t vaddr,  uint8_t rw, pd_t* pd_t_start){ //all pages that are identity mapped are supervisor. For rw, read is 0 read/write is 1
  vaddr = vaddr & 0xFFFFF000; //make 4 kib aligned
  uint32_t pd_offset = ((uint32_t)vaddr & 0xFFC00000) >> 22; //get top 10 bits
  uint32_t pte_offset = ((uint32_t)vaddr & 0x3FF000) >> 12; //get middle 10 bits
  pd_t* pd = pd_t_start + pd_offset;
  pte_t* pte_base = (pte_t*)(*pd & 0xFFFFF000); //this is the first pte in the pd
  pte_t* pte = pte_base + pte_offset; //this is the pte we need to manipulate
  *pte = paddr & 0xFFFFF000;

  *pte |= (0x1 | (rw << 1)) ; //read intel manual Volume 3 page 115 (PDF)



}


void paging_init(){ //identity maps 1st GiB
  uint32_t addr_lim = 0x4000000;//0xFFFFFFFF; //1 GiB. Increment by 0x1000 which is 4096 bytes.
  //uint32_t addr_count = 0x0;
  instantiate_pd_t(&pg_dir_start, &pg_table_start, 1024); //create 1GiB of pd_t
              //increment pd until we hit 256 as we need 256 pd_t to represent 1 GiB
  for(uint32_t addr_count = 0 ; addr_count <= addr_lim; addr_count += 0x1000){ //1024 ptes per pd_t. Identity map first 1MiB
    map_page(addr_count, addr_count, 1, &pg_dir_start); //identity map
  }

//  print_number(&pg_dir_start);
  load_cr3((uint32_t)&pg_dir_start);

}
