//
// Created by andre on 29/12/2025.
//

#pragma once
#include "../common/types.h"

namespace cvsim {

    struct IF_ID_Regs {
        addr_t pc;
        inst_t instruction;

        bool valid;
    };

    struct ID_EX_Reg {
        addr_t pc;
        inst_t instruction;
        word_t rs1_val;
        word_t rs2_val;
        word_t imm;
        reg_addr_t rd;
        Opcode opcode;
        InstrType instr_type;

        bool WB[2];      // [0] = RegWrite, [1] = MemtoReg
        bool M[3];       // [0] = MemRead, [1] = MemWrite, [2] = Branch
        bool EX[3];      // [0] = ALUSrc, [1] = ALUOp1, [2] = ALUOp0

        bool valid;
    };

    struct EX_MEM_Reg {
        addr_t pc;
        inst_t instruction;
        word_t alu_result;
        word_t rs2_val;
        reg_addr_t rd;

        bool WB[2];             // [0] = RegWrite, [1] = MemtoReg
        bool M[3];              // [0] = MemRead, [1] = MemWrite, [2] = Branch

        bool valid;
    };

    struct MEM_WB_Reg {
        addr_t pc;
        inst_t instruction;
        word_t mem_data;
        word_t alu_result;
        reg_addr_t rd;

        bool WB[2];             // [0] = RegWrite, [1] = MemtoReg

        bool valid;
    };
}