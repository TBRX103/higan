#include <pce/pce.hpp>

namespace higan::PCEngine {

CPU cpu;
#include "io.cpp"
#include "irq.cpp"
#include "timer.cpp"
#include "serialization.cpp"

auto CPU::main() -> void {
  if(irq.pending()) return interrupt(irq.vector());
  instruction();
}

auto CPU::step(uint clocks) -> void {
  Thread::step(clocks);
  timer.step(clocks);
  synchronize(vdc0);
  synchronize(vdc1);
  synchronize(vce);
  synchronize(psg);
  for(auto peripheral : peripherals) synchronize(*peripheral);
}

auto CPU::power() -> void {
  HuC6280::power();
  Thread::create(system.colorburst() * 2.0, [&] {
    while(true) scheduler.synchronize(), main();
  });

  r.pc.byte(0) = read(0x00, 0x1ffe);
  r.pc.byte(1) = read(0x00, 0x1fff);

  for(auto& byte : ram) byte = 0x00;
  irq = {};
  timer = {};
  io = {};
}

auto CPU::lastCycle() -> void {
  irq.poll();
}

}
