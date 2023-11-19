#include "esignal.h"

#include <linux/compiler_types.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/types.h>

#include "asm/thread_info.h"

int esignal_redirect(struct pt_regs *regs) {
  void __user *user_stack_pointer;
  clear_thread_flag(TIF_ESIGNAL);
  unsigned long copynr;
  int trap_nr;

  // get rip and rsp
  user_stack_pointer = (void *)regs->sp;
  // skip red zone
  user_stack_pointer -= 128;

  // pushing original rsp and rip
  user_stack_pointer -= sizeof(unsigned long);
  copynr = copy_to_user(user_stack_pointer, &regs->sp, sizeof(unsigned long));
  if (copynr != sizeof(unsigned long)) return -1;

  user_stack_pointer -= sizeof(unsigned long);
  copynr = copy_to_user(user_stack_pointer, &regs->ip, sizeof(unsigned long));
  if (copynr != sizeof(unsigned long)) return -1;

  // overwrite rsp and rip
  trap_nr = current->thread.trap_nr;
  regs->sp = (unsigned long)current->thread.esignal->esignal_stack;
  regs->ip = (unsigned long)current->thread.esignal->handler_table[trap_nr];
  return 0;
}


