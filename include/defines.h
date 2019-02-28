#ifndef __DEFINES
#define __DEFINES

struct filedesc {
  void *useless1[3];
  void *fd_rdir;
  void *fd_jdir;
};

struct proc {
  char useless[64];
  struct ucred *p_ucred;
  struct filedesc *p_fd;
};

struct thread {
  void *useless;
  struct proc *td_proc;
};

struct auditinfo_addr {
  char useless[184];
};

struct ucred {
  uint32_t useless1;
  uint32_t cr_uid;     // effective user id
  uint32_t cr_ruid;    // real user id
  uint32_t useless2;
  uint32_t useless3;
  uint32_t cr_rgid;    // real group id
  uint32_t useless4;
  void *useless5;
  void *useless6;
  void *cr_prison;     // jail(2)
  void *useless7;
  uint32_t useless8;
  void *useless9[2];
  void *useless10;
  struct auditinfo_addr useless11;
  uint32_t *cr_groups; // groups
  uint32_t useless12;
};

struct kernel_payload_args
{
  void* syscall_handler;
  uint64_t user_arg;
};

static inline __attribute__((always_inline)) uint64_t __readmsr(unsigned long __register)
{
  unsigned long __edx;
  unsigned long __eax;
  __asm__ ("rdmsr" : "=d"(__edx), "=a"(__eax) : "c"(__register));
  return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

char temp[5] = {0x00,0x00,60,0x00,0x00};

#endif
