//
// Created by andre on 29/12/2025.
//

#pragma once
#include "../common/types.h"
#include "../common/utils.h"
#include "../memory/bus.h"
#include "regfile.h"
#include "alu.h"
#include "pipeline_regs.h"
#include <array>
#include <iostream>

class CPU {
    private:
        RegFile regFile;
        ALU alu;
        Bus& bus;
        cvsim::word_t pc;

        cvsim::IF_ID_Reg IF_ID_Curr, IF_ID_Next;
        cvsim::ID_EX_Reg ID_EX_Curr, ID_EX_Next;
        cvsim::EX_MEM_Reg EX_MEM_Curr, EX_MEM_Next;
        cvsim::MEM_WB_Reg MEM_WB_Curr, MEM_WB_Next;

        cvsim::IF_ID_Reg fetch(cvsim::addr_t address) {
            cvsim::word_t instruction = bus.read(address);
            cvsim::IF_ID_Reg if_id;
            if_id.instruction = instruction;
            if_id.pc = pc;
            if_id.valid = (instruction != 0x00000000);
            return if_id;
        }

        cvsim::ID_EX_Reg decode(cvsim::IF_ID_Reg if_id) {

        }

        cvsim::EX_MEM_Reg execute(cvsim::ID_EX_Reg id_ex) {

        }

    public:
        CPU(Bus& system_bus) : bus(system_bus), pc(cvsim::RESET_VECTOR) {}

        void reset() {
            regFile.reset();
            pc = cvsim::RESET_VECTOR;
            IF_ID_Curr = {};
            IF_ID_Next = {};
            ID_EX_Curr = {};
            ID_EX_Next = {};
            EX_MEM_Curr = {};
            EX_MEM_Next = {};
            MEM_WB_Curr = {};
            MEM_WB_Next = {};
        }

        void eval() {
            // Combinational logic
            IF_ID_Next = fetch(pc);
            ID_EX_Next = decode(IF_ID_Curr);
            EX_MEM_Next = execute(ID_EX_Curr);
        }

        void commit() {
            // Sequential logic
            IF_ID_Curr = IF_ID_Next;
            ID_EX_Curr = ID_EX_Next;
            EX_MEM_Curr = EX_MEM_Next;
            MEM_WB_Curr = MEM_WB_Next;
        }
};

