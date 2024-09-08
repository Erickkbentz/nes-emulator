#include "cpu.hpp"

CPU::CPU() {
    memory = new uint8_t[64 * 1024]; // 64KB of memory
    Reset();
}

CPU::~CPU() {
    delete[] memory;
}

void CPU::Reset() {
    // Initialize or reset registers and memory
    A = X = Y = 0;
    SP = 0xFF; // Stack pointer starts at the top of the stack
    
    /**
     * Set the PC to the address stored at the reset vector.
     * 
     * This is the address where the CPU will start executing instructions after a reset.
     * This is typically be the beginning of the program's startup or initialization code.
     */
    PC = Read(RESET_VECTOR) | (Read(RESET_VECTOR + 1) << 8);


    P = UNUSED_FLAG; // Default flags

    // Clear memory
    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}

uint8_t CPU::Read(uint16_t address) {
    return memory[address];
}

void CPU::Write(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void CPU::Execute() {
    while (true) {
        uint8_t opcode = Read(PC);
        PC++; // Move to next instruction
        ExecuteInstruction(opcode);
    }
}

void CPU::ExecuteInstruction(uint8_t opcode) {
    switch(opcode) {
        // ADC
        case 0x69:
            ADC(AddressingMode::Immediate);
            break;
        case 0x65:
            ADC(AddressingMode::ZeroPage);
            break;
        case 0x75:
            ADC(AddressingMode::ZeroPage_X);
            break;
        case 0x6D:
            ADC(AddressingMode::Absolute);
            break;
        case 0x7D:
            ADC(AddressingMode::Absolute_X);
            break;
        case 0x79:
            ADC(AddressingMode::Absolute_Y);
            break;
        case 0x61:
            ADC(AddressingMode::Indirect_X);
            break;
        case 0x71:
            ADC(AddressingMode::Indirect_Y);
            break;

        // AND
        case 0x29:
            AND(AddressingMode::Immediate);
            break;
        case 0x25:
            AND(AddressingMode::ZeroPage);
            break;
        case 0x35:
            AND(AddressingMode::ZeroPage_X);
            break;
        case 0x2D:
            AND(AddressingMode::Absolute);
            break;
        case 0x3D:
            AND(AddressingMode::Absolute_X);
            break;
        case 0x39:
            AND(AddressingMode::Absolute_Y);
            break;
        case 0x21:  
            AND(AddressingMode::Indirect_X);
            break;
        case 0x31:
            AND(AddressingMode::Indirect_Y);
            break;

        case 0x0A:
            ASL(AddressingMode::Accumulator);
            break;
        case 0x06:
            ASL(AddressingMode::ZeroPage);
            break;
        case 0x16:
            ASL(AddressingMode::ZeroPage_X);
            break;
        case 0x0E:
            ASL(AddressingMode::Absolute);
            break;
        case 0x1E:
            ASL(AddressingMode::Absolute_X);
            break;
    }
}