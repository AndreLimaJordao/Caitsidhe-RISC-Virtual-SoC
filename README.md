# 🐱 Caitsidhe-V SoC (Virtual Implementation)

![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)
![Architecture](https://img.shields.io/badge/arch-RISC--V%20RV32I-red.svg)
![License](https://img.shields.io/badge/license-APACHE_2.0-green.svg)
![Status](https://img.shields.io/badge/status-Development-yellow.svg)

**Caitsidhe-V** (pronounced *Cat-Sith*) is a Cycle-Accurate RISC-V System-on-Chip simulator written in C++.
Caithsidhe-V is designed to **model hardware behavior**, including a bus interconnect and MMIO. It serves as a model for future Verilog implementation and as a sandbox playground for developing hardware accelerators and peripherals.

---

## Architecture

The system is designed around the RISC-V RV32I architecture, containing a CPU Core, the interconnect bus and peripherals.

```mermaid
graph TD;
    CPU[RISC-V CPU Core] -->|Address/Data| BUS[Interconnect Bus];
    BUS -->|0x8000_0000| RAM[Main Memory (RAM)];
    BUS -->|MMIO Access| To be added (Other Peripherals);
```