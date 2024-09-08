#include "cpu.hpp"

/*
* ----------------------
* CPU Implementation
* ----------------------
*/

// Initialize CPU Constants
const uint16_t CPU::MEMORY_SIZE = 64 * 1024;
const uint8_t CPU::PAGE_SIZE = 256;

const uint16_t CPU::NMI_VECTOR = 0xFFFA;
const uint16_t CPU::RESET_VECTOR = 0xFFFC;
const uint16_t CPU::IRQ_VECTOR = 0xFFFE;

const uint16_t CPU::ZERO_PAGE_START = 0x0000;
const uint16_t CPU::ZERO_PAGE_END = 0x00FF;
const uint16_t CPU::STACK_START = 0x0100;
const uint16_t CPU::STACK_END = 0x01FF;
const uint16_t CPU::PPU_REGISTERS_START = 0x2000;
const uint16_t CPU::PPU_REGISTERS_END = 0x2007;
const uint16_t CPU::APU_IO_REGISTERS_START = 0x4000;
const uint16_t CPU::APU_IO_REGISTERS_END = 0x4017;

const uint8_t CPU::CARRY_FLAG = 0x01;
const uint8_t CPU::ZERO_FLAG = 0x02;
const uint8_t CPU::INTERRUPT_DISABLE_FLAG = 0x04;
const uint8_t CPU::DECIMAL_MODE_FLAG = 0x08;
const uint8_t CPU::BREAK_FLAG = 0x10;
const uint8_t CPU::UNUSED_FLAG = 0x20;
const uint8_t CPU::OVERFLOW_FLAG = 0x40;
const uint8_t CPU::NEGATIVE_FLAG = 0x80;


CPU::CPU() : memory(new uint8_t[CPU::MEMORY_SIZE]) {
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
    std::fill(memory, memory + 64 * 1024, 0);

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

void CPU::ADC(CPU::AddressingMode mode) {
    return;
}

void CPU::AND(CPU::AddressingMode mode) {
    return;
}

void CPU::ASL(CPU::AddressingMode mode) {
    return;
}