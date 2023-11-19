#include "../arch/x86/include/asm/irq_vectors.h"

struct esignal {
  // handler table
  void* handler_table[NR_VECTORS];
  // signal stack address
  void* esignal_stack;
};
