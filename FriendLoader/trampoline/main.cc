#include "channel.h"
#include "int.h"
#include "trampoline.h"

Idt idt;

void panic();

// callback test
void callback(H2F &h2f, F2H &f2h) {
  h2f.Return(0);
  f2h.SendSignal(1);
}

// print request test
void print(H2F &h2f, F2H &f2h) {
  h2f.Return(0);
  f2h.WriteString("abc\n");
}

// execute binary
void exec_bin(H2F &h2f, F2H &f2h) {
  uint64_t address;
  h2f.Read(0, address);
  // TODO check address
  h2f.Return(0);
  asm volatile("call *%0"::"r"(address));
}

void rw_memory(H2F &h2f, F2H &f2h) {
  static const uint32_t kRead = 0;
  static const uint32_t kWrite = 1;
  
  uint32_t type;
  uint64_t address_;
  uint64_t size;
  uint8_t *buf = h2f.GetRawPtr<uint8_t>() + 2048;
  
  h2f.Read(0, type);
  h2f.Read(8, address_);
  h2f.Read(16, size);

  if (address_ + 2048 / sizeof(uint64_t) >= 1024 * 1024 * 1024 /* 1GB */) {
    // avoid accessing to page unmapped region
    h2f.Return(-1);
    return;
  }
  
  uint8_t *address = reinterpret_cast<uint8_t *>(address_);
  if (type == kRead) {
    for(int i = 0; i < size; i++) {
      buf[i] = address[i];
    }
  } else if (type == kWrite) {
    for(int i = 0; i < size; i++) {
      address[i] = buf[i];
    }
  } else {
    h2f.Return(-1);
    return;
  }
  
  h2f.Return(0);
}

extern "C" void trampoline_main() {
  H2F h2f;
  F2H f2h;
  idt.SetupGeneric();
  idt.SetupProc();

  while(true) {
    switch (h2f.WaitNewSignal()) {
    case 0:
      panic();
    case 1:
      callback(h2f, f2h);
      break;
    case 2:
      print(h2f, f2h);
      break;
    case 3:
      exec_bin(h2f, f2h);
      break;
    case 4:
      rw_memory(h2f, f2h);
      break;
    }
  }
}

void panic() {
  while (true) {
    asm volatile("cli;hlt;nop;");
  }
}
