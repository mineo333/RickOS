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


typedef uint32_t pd_t;
typedef uint32_t pte_t;
typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;

//setup extern variables

extern pte_t pg_table_start;
extern pte_t pg_table_end;
extern pd_t pg_dir_start;
extern pd_t pg_dir_end;
extern void load_cr3(uint32_t ptr);

//function headers


void instantiate_pd_t(pd_t* pd_t_start, pte_t* pte_t_start, uint32_t num);

void map_page(phys_addr_t paddr, virt_addr_t vaddr,  uint8_t rw, pd_t* pd_t_start);

void paging_init();



/*
Thus function essentially setups the pd_ts for the first 1 GiB
*/
