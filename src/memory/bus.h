//
// Created by andre on 29/12/2025.
//

#ifndef BUS_H
#define BUS_H

#endif //BUS_H

#pragma once
#include "ram.h"

namespace MemoryMap {
    constexpr cvsim::addr_t RAM_BASE = 0x80000000;
    // TODO: Adicionar os endereços de outros dispositivos ou periféricos aqui
}

class Bus {
    private:
        RAM& ram;

    public:
        Bus(RAM& ram_instance) : ram(ram_instance) {}

        cvsim::word_t read(cvsim::addr_t addr) {
            if (addr >= MemoryMap::RAM_BASE && addr < (MemoryMap::RAM_BASE + ram.size())) {
                return ram.read_word_aligned(addr - MemoryMap::RAM_BASE);
            }
            // TODO: Adicionar outros dispositivos ou periféricos aqui
            std::cerr << "[Bus] Erro: Leitura de endereço não mapeado! ADDR: " << std::hex << addr << std::dec << std::endl;
            return 0;
        }

        void write(cvsim::addr_t addr, cvsim::word_t data, uint8_t wstrb) {
            if (addr >= MemoryMap::RAM_BASE && addr < (MemoryMap::RAM_BASE + ram.size())) {
                ram.write_word_masked(addr - MemoryMap::RAM_BASE, data, wstrb);
                return;
            }
            // TODO: Adicionar outros dispositivos ou periféricos aqui
            std::cerr << "[Bus] Erro: Escrita em endereço não mapeado! ADDR: " << std::hex << addr << std::dec << std::endl;
        }
};