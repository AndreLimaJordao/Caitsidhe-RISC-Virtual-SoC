//
// Created by andre on 29/12/2025.
//

#pragma once
#include <cstdint>

namespace utils {
    // Função para extrair um campo de bits de um valor: inst[msb:lsb]
    // Exemplo: get_field(0xAC, 7, 4) retorna 0xA (1010)
    constexpr uint32_t get_field(uint32_t value, int msb, int lsb) {
        uint32_t mask = ((1u << (msb - lsb + 1)) - 1) << lsb;
        return (value & mask) >> lsb;
    }

    // Função para extrair 1 bit de um valor
    // Exemplo: get_bit(0xAC, 5) retorna 1
    constexpr uint32_t get_bit(uint32_t value, int bit_pos) {
        return (value >> bit_pos) & 0x1;
    }

    // Função de extensão de sinal para um valor com 'bits' bits
    // Exemplo: sign_extend(0b111, 3) retorna 0xFFFFFFFF
    constexpr int32_t sign_extend(uint32_t value) {
        struct {
            int32_t value;
        } s;
        s.value = value;
        return s.value;
    }

    // Função para combinar bytes em uma palavra (little-endian)
    // Exemplo: combine_bytes(0x12, 0x34, 0x56, 0x78) retorna 0x12345678
    constexpr uint32_t combine_bytes(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0) {
        return (b3 << 24) | (b2 << 16) | (b1 << 8)  | (b0);
    }

}