#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {
//you write this
//grab the lock while you are working with the shm_table 
  acquire(&(shm_table.lock));
  int exists = 0;
//empty entry in the shm_table
  int entry = -1;
  struct proc* h = myproc(); 
  //In either case, return the virtual address through the second parameter of the system call.
  uint va = PGROUNDUP(h->sz);
  *pointer = (char*) va;  int i;
  for (i = 0; i < 64; i++) {
    //check segment id
    //shm_open looks through the shm_table to see if this segment id already exists
    if (shm_table.shm_pages[i].id == id) {
      exists = 1;
      break;
    }
    else if (shm_table.shm_pages[i].id == 0) {
      entry = i;
    }
  }
  if (exists == 0) {
    shm_table.shm_pages[entry].id = id; //initialize id to id passed to us
    shm_table.shm_pages[entry].frame = kalloc(); //store its address in frame (we got our physical page)
    shm_table.shm_pages[entry].refcnt = 1;
    //store its address in frame (we got our physical page)
    memset(shm_table.shm_pages[entry].frame, 0, PGSIZE); 
    mappages(h->pgdir,(void*)va , PGSIZE, V2P(shm_table.shm_pages[entry].frame),PTE_U|PTE_W);
  
  }
  //In either case, return the virtual address through the second parameter of the system call.
  // uint va = PGROUNDUP(h->sz);
  // *pointer = (char*) va;
  else {
    mappages(h->pgdir,(void*)va , PGSIZE, V2P(shm_table.shm_pages[i].frame),PTE_U|PTE_W);
  }
  shm_table.shm_pages[i].refcnt++; //we set the refcnt to 1
  release(&(shm_table.lock));
 
  return va; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!
  acquire(&(shm_table.lock));
  int i;
  int exists = 0;
  for (i = 0; i < 64; i++) {
    if (shm_table.shm_pages[i].id == id) {
      exists = 1;
      break;
    }
  }
  if (exists == 1) {
    if (shm_table.shm_pages[i].refcnt-- == 0) {
      shm_table.shm_pages[i].id = 0;
      shm_table.shm_pages[i].frame = 0;
    } 
  }
  
  release(&(shm_table.lock));
  return 0; //added to remove compiler warning -- you should decide what to return
}
