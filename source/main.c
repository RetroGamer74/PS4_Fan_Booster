#include "ps4.h"
#include "defines.h"

#define	KERN_XFAST_SYSCALL	0x1C0	// 5.05
#define KERN_PRISON_0		0x10986A0
#define KERN_ROOTVNODE		0x22C1A70


int kernel_payload(struct thread *td, struct kernel_payload_args* args)
{
  struct ucred* cred;
  struct filedesc* fd;

  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void* kernel_base = &((uint8_t*)__readmsr(0xC0000082))[-KERN_XFAST_SYSCALL];
  uint8_t* kernel_ptr = (uint8_t*)kernel_base;
  void** got_prison0 =   (void**)&kernel_ptr[KERN_PRISON_0];
  void** got_rootvnode = (void**)&kernel_ptr[KERN_ROOTVNODE];

  cred->cr_uid = 0;
  cred->cr_ruid = 0;
  cred->cr_rgid = 0;
  cred->cr_groups[0] = 0;

  cred->cr_prison = *got_prison0;
  fd->fd_rdir = fd->fd_jdir = *got_rootvnode;

  // escalate ucred privs, needed for access to the filesystem ie* mounting & decrypting files
  void *td_ucred = *(void **)(((char *)td) + 304); // p_ucred == td_ucred
	
  // sceSblACMgrIsSystemUcred
  uint64_t *sonyCred = (uint64_t *)(((char *)td_ucred) + 96);
  *sonyCred = 0xffffffffffffffff;
	
  // sceSblACMgrGetDeviceAccessType
  uint64_t *sceProcType = (uint64_t *)(((char *)td_ucred) + 88);
  *sceProcType = 0x3801000000000013; // Max access
	
  // sceSblACMgrHasSceProcessCapability
  uint64_t *sceProcCap = (uint64_t *)(((char *)td_ucred) + 104);
  *sceProcCap = 0xffffffffffffffff; // Sce Process

  return 0;
}

void systemMessage(char* msg) {
        char buffer[512];
        sprintf(buffer, "%s\n\n\n\n\n\n\n", msg);
        sceSysUtilSendSystemNotificationWithText(0x81, buffer);
}

int _main(struct thread *td)
{
   initKernel();
   initLibc();
   initPthread();
   syscall(11,kernel_payload, td); // jailbreak to use system notifications

   initSysUtil();

   int fan_accesible=0;

   int fd = 0;
   fd = open("/dev/icc_fan", O_RDONLY, 0);
   if (fd <= 0)
   {
      fan_accesible=0;
   }
   else
   {
      fan_accesible=1;
   }

   if(fan_accesible == 1)
   {
   	char data[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // swap 60 with whatever temp threshold you want

	data[5] = temp[2];
   	int ret = ioctl(fd, 0xC01C8F07, data);
   	close(fd);

//	sprintf(msg,"Fan Booster set to %c degress celsius",temp[2]);
	systemMessage("Fan Booster has been set");

   }
   else
	systemMessage("Fan Booster couldn't be set");
   

   return 0;
}
