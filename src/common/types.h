//
// Created by andre on 29/12/2025.
//

#ifndef TYPES_H
#define TYPES_H

#endif //TYPES_H

#pragma once
#include <cstdint>

namespace cvsim {
    // ===================================
    // Definições de tipos básicos
    // ===================================

    // Uma palavra (word) é definida como 32 bits (4 bytes) no RISC-V 32-bit
    using word_t = uint32_t;
    using sword_t = int32_t;
    using inst_t = uint32_t;

    // Uma meia palavra (half-word) é definida como 16 bits (2 bytes)
    using halfword_t = uint16_t;
    using shalfword_t = int16_t;

    // Um byte é definido como 8 bits
    using byte_t = uint8_t;
    using sbyte_t = int8_t;

    // Endereços de memória são representados como palavras de 32 bits
    using addr_t = uint32_t;

    // Endereço de banco de registradores (0 a 31 podem ser descritos com 5 bits, mas usamos 8 bits para alinhamento)
    using reg_addr_t = uint8_t;

    // ===================================
    // Constantes do processador
    // ===================================

    constexpr int XLEN = 32;                    // Limite de bits do registrador
    constexpr int NUM_REGS = 32;                // Número de registradores gerais
    constexpr int RESET_VECTOR = 0x80000000;    // Vetor de reset onde PC inicia
    constexpr addr_t MEM_SIZE = 64 * 1024;   // Tamanho da memória: 64kB
    // ===================================
    // Definições de instruções
    // ===================================

    enum class InstrType {
        R_TYPE,
        I_TYPE,
        S_TYPE,
        B_TYPE,
        U_TYPE,
        J_TYPE
    };

    enum class Opcode : uint8_t {
        LUI     = 0b0110111,
        AUIPC   = 0b0010111,
        JAL     = 0b1101111,
        JALR    = 0b1100111,
        BRANCH  = 0b1100011,
        LOAD    = 0b0000011,
        STORE   = 0b0100011,
        ALUI    = 0b0010011,
        ALUR    = 0b0110011,
        MISC_MEM= 0b0001111,
        SYSTEM  = 0b1110011
    };

    enum class Funct3 : uint8_t {
        BEQ  = 0b000,
        BNE  = 0b001,
        BLT  = 0b100,
        BGE  = 0b101,
        BLTU = 0b110,
        BGEU = 0b111,

        LB   = 0b000,
        LH   = 0b001,
        LW   = 0b010,
        LBU  = 0b100,
        LHU  = 0b101,

        SB   = 0b000,
        SH   = 0b001,
        SW   = 0b010,

        ADDI = 0b000,
        SLTI = 0b010,
        SLTIU= 0b011,
        XORI = 0b100,
        ORI  = 0b110,
        ANDI = 0b111,
        SLLI = 0b001,
        SRLI_SRAI = 0b101,

        ADD_SUB = 0b000,
        SLL     = 0b001,
        SLT     = 0b010,
        SLTU    = 0b011,
        XOR     = 0b100,
        SRL_SRA = 0b101,
        OR      = 0b110,
        AND     = 0b111
    };

    // ===================================
    // Estruturas auxiliares para decode
    // ===================================

    union DecodedInstr {
        struct {
            uint32_t opcode : 7;
            uint32_t rd     : 5;
            uint32_t funct3 : 3;
            uint32_t rs1    : 5;
            uint32_t rs2    : 5;
            uint32_t funct7 : 7;
        } r_type;

        struct {
            uint32_t opcode : 7;
            uint32_t rd     : 5;
            uint32_t funct3 : 3;
            uint32_t rs1    : 5;
            int32_t  imm    : 12;
        } i_type;

        struct {
            uint32_t opcode : 7;
            uint32_t imm4_0 : 5;
            uint32_t funct3 : 3;
            uint32_t rs1    : 5;
            uint32_t rs2    : 5;
            int32_t  imm11_5: 7;
        } s_type;

        struct {
            uint32_t opcode : 7;
            int32_t  imm11_5: 7;
            uint32_t funct3 : 3;
            uint32_t rs1    : 5;
            uint32_t rs2    : 5;
            int32_t  imm4_1 : 4;
            uint32_t imm12   : 1;
        } b_type;

        struct {
            uint32_t opcode : 7;
            uint32_t rd     : 5;
            int32_t  imm31_12:20;
        } u_type;

        struct {
            uint32_t opcode : 7;
            uint32_t rd     : 5;
            int32_t  imm19_12:8;
            int32_t  imm11   :1;
            int32_t  imm10_1:10;
        } j_type;

        inst_t raw;
    };
}