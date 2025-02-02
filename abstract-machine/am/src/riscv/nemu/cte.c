#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    // switch (c->mcause) {
    //   default: ev.event = EVENT_ERROR; break;
    // }
    switch (c->mcause) {
    case 8:  // U-mode ecall
    case 9:  // S-mode ecall
    case 11: // M-mode ecall
      ev.event = EVENT_YIELD;
      c->mepc += 4;
      //printf("EVENT_YIELD\n"); 
      break;
    default:
      ev.event = EVENT_ERROR; 
    break;
    }
    //printf("Context pointer is %d\n",c);
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);
/*
handler is the pointer of function
*/
bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  // uintptr_t high = (uintptr_t)kstack.end;
  // high -= sizeof(Context); 
  // //high &= ~((uintptr_t)15);

  // Context *ctx = (Context *)high;
  // memset(ctx, 0, sizeof(Context));
  // ctx->mepc = (uintptr_t)entry;
  
  // ctx->gpr[10] = (uintptr_t)arg;    // x10 = a0
  // return ctx;
  // Context *c = (Context*) kstack.end - 1;
  // c->mepc = (uintptr_t)entry;
  // c->gpr[10] = (uintptr_t)arg;
  // return c;
  uintptr_t high = (uintptr_t)kstack.end;
  high -= sizeof(Context);
  Context *ctx = (Context *)high;
  memset(ctx, 0, sizeof(Context));
  ctx->mepc = (uintptr_t)entry;
  ctx->gpr[10] = (uintptr_t)arg;  // a0 = arg
  return ctx;

}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
