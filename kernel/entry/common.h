/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _COMMON_H
#define _COMMON_H

bool syscall_user_dispatch(struct pt_regs *regs);
int esignal_redirect(struct pt_regs *regs);
bool esignal_to_tracer(struct pt_regs *regs);
int wakeup_tracer(void);

#endif
