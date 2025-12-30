//
// Created by andre on 29/12/2025.
//

#ifndef RAM_H
#define RAM_H

#endif //RAM_H

#pragma once
#include "../common/types.h"
#include <vector>
#include <cstring>
#include <iostream>

class RAM {
    private:
        std::vector<uint8_t> data;

    public:
        RAM(size_t size) {
            data.resize(size, 0); // Inicializa a RAM com zeros
        }

        uint32_t size() {
            return data.size();
        }

        cvsim::word_t read_word_aligned(cvsim::addr_t addr) const {
            if (addr + 4 > data.size()) {
                std::cerr << "[RAM] Erro: Leitura fora dos limites de memória em endereço! ADDR: " << std::hex << addr << std::dec << std::endl;
                return 0;
            }
            if (addr % 4 != 0) {
                std::cerr << "[RAM] Aviso: Leitura em endereço não alinhado! ADDR: " << std::hex << addr << std::dec << std::endl;
            }
            cvsim::word_t value = 0;
            // Copia os 4 bytes da RAM para a variável value para o endereço alinhado
            cvsim::addr_t aligned_addr = addr & ~0x3;
            std::memcpy(&value, &data[aligned_addr], sizeof(cvsim::word_t));
            return value;
        }

        void write_word_masked(cvsim::addr_t addr, cvsim::word_t value, uint8_t wstrb) {
            if (addr + 4 > data.size()) {
                std::cerr << "[RAM] Erro: Escrita fora dos limites de memória em endereço! ADDR: " << std::hex << addr << std::dec << std::endl;
                return;
            }
            if (addr % 4 != 0) {
                std::cerr << "[RAM] Aviso: Escrita em endereço não alinhado! ADDR: " << std::hex << addr << std::dec << std::endl;
            }
            // Escrita byte a byte com base no wstrb (strobe) para o endereço alinhado
            cvsim::addr_t aligned_addr = addr & ~0x3;
            if (wstrb & 0b0001) data[aligned_addr + 0] = (value >> 0) & 0xFF;
            if (wstrb & 0b0010) data[aligned_addr + 1] = (value >> 8) & 0xFF;
            if (wstrb & 0b0100) data[aligned_addr + 2] = (value >> 16) & 0xFF;
            if (wstrb & 0b1000) data[aligned_addr + 3] = (value >> 24) & 0xFF;
        }

        // Método para carregar um programa na RAM a partir de um vetor de bytes
        void load_binary(const std::vector<uint8_t>& program, cvsim::addr_t start_addr) {
            if (start_addr + program.size() > data.size()) {
                std::cerr << "[RAM] Erro: Programa excede os limites de memória ao carregar! START ADDR: " << std::hex << start_addr << std::dec << std::endl;
                return;
            }
            std::memcpy(&data[start_addr], program.data(), program.size());
        }
};