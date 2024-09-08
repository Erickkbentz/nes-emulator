#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

class CPU {
public:

    // Contants
    /**
     * Memory Size
     * 
     * The NES has 64KB of memory.
     */
    static const uint16_t MEMORY_SIZE = 64 * 1024;

    /**
     * Page Size
     * 
     * The NES has 256 bytes per page.
     */
    static const uint8_t PAGE_SIZE = 256;

    /**
     * NMI Vector
     * 
     * The Non-Maskable Interrupt (NMI) vector is located at memory address 0xFFFA.
     * The NMI vector is a 16-bit address that points to the location of the NMI handler.
     * NMIs are used for critical system events that need to be handled immediately.
     */
    static const uint16_t NMI_VECTOR = 0xFFFA;

    /**
     * Reset Vector
     * 
     * The Reset vector is located at memory address 0xFFFC.
     * The Reset vector is a 16-bit address that points to the location of the Reset handler.
     * The Reset handler is called when the CPU is reset.
     * 
     * Low byte: 0xFFFC
     * High byte: 0xFFFD
     */
    static const uint16_t RESET_VECTOR = 0xFFFC;

    /**
     * IRQ Vector
     * 
     * The Interrupt Request (IRQ) vector is located at memory address 0xFFFE.
     * The IRQ vector is a 16-bit address that points to the location of the IRQ handler.
     * IRQs are used for non-critical system events that can be handled later.
     */
    static const uint16_t IRQ_VECTOR = 0xFFFE;

    // Important Memory Regions
    static const uint16_t ZERO_PAGE_START = 0x0000;
    static const uint16_t ZERO_PAGE_END = 0x00FF;

    static const uint16_t STACK_START = 0x0100;
    static const uint16_t STACK_END = 0x01FF;

    static const uint16_t PPU_REGISTERS_START = 0x2000;
    static const uint16_t PPU_REGISTERS_END = 0x2007;

    static const uint16_t APU_IO_REGISTERS_START = 0x4000;
    static const uint16_t APU_IO_REGISTERS_END = 0x4017;

    /**
     * Accumulator
     * 
     * The accumulator is an 8-bit register that is used for arithmetic and logic operations.
     * The accumulator is the most important register in the CPU.
     */
    uint8_t A;   // Accumulator

    /**
     * X Index Register
     * 
     * The X index register is an 8-bit register that is used for arithmetic and logic operations.
     * The X register is used to hold counters and offsets for memory operations.
     */
    uint8_t X;   // X index register

    /**
     * Y Index Register
     * 
     * The Y index register is an 8-bit register that is used for arithmetic and logic operations.
     * The Y register is used to hold counters and offsets for memory operations.
     */
    uint8_t Y;   // Y index register

    /**
     * Stack Pointer
     * 
     * The stack pointer is an 8-bit register that points to the current location on the stack.
     * The stack pointer is initialized to 0xFF when the CPU is reset.
     * The stack exists in the memory range 0x0100 to 0x01FF.
     * The stack grows downwards so adding data to the stack will decrement the stack pointer.
     */
    uint8_t SP;

    /**
     * Program Counter
     * 
     * The program counter is a 16-bit register that holds the memory address of the next instruction to be executed.
     * 
     * The program counter is incremented after each instruction is fetched.
     * 
     */
    uint16_t PC; // Program Counter
    uint8_t P;   // Processor Status

    // Memory pointer
    uint8_t* memory;

    // Methods
    CPU(); // Constructor
    void Reset(); // Resets the CPU to its initial state
    void Execute(); // Main loop to execute instructions
    void ExecuteInstruction(uint8_t opcode); // Execute a single instruction

    // Memory access methods
    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);

private:

    // Flags
    static const uint8_t CARRY_FLAG = 0x01;
    static const uint8_t ZERO_FLAG = 0x02;
    static const uint8_t INTERRUPT_DISABLE_FLAG = 0x04;
    static const uint8_t DECIMAL_MODE_FLAG = 0x08;
    static const uint8_t BREAK_FLAG = 0x10;
    static const uint8_t UNUSED_FLAG = 0x20;
    static const uint8_t OVERFLOW_FLAG = 0x40;
    static const uint8_t NEGATIVE_FLAG = 0x80;

    // Addressing modes
    enum class AddressingMode {
        Immediate,
        ZeroPage,
        ZeroPage_X,
        Absolute,
        Absolute_X,
        Absolute_Y,
        Indirect_X,
        Indirect_Y,
        Accumulator,
    };


    // Instructions
    /**
     * ADC - Add with Carry
     * 
     * This instruction adds the contents of a memory location to the accumulator together with the carry bit.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */ 
    void ADC(AddressingMode mode);


    /**
     * AND - AND Memory with Accumulator
     * 
     * This instruction performs a logical AND on the contents of a memory location and the accumulator.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void AND(AddressingMode mode);


    /**
     * ASL - Arithmetic Shift Left
     * 
     * This instruction shifts all bits in either the accumulator or memory one position to the left.
     * 
     * Addressing modes:
     * - Accumulator
     * - Zero Page
     */
    void ASL(AddressingMode mode); // Shift memory

    /**
     * BCC - Branch if Carry Clear
     * 
     * This instruction tests the carry flag and branches if it is clear.
     * 
     * Addressing modes:
     * - Relative
     */
    void BCC(); // Relative addressing


    /**
     * BCS - Branch if Carry Set
     * 
     * This instruction tests the carry flag and branches if it is set.
     * 
     * Addressing modes:
     * - Relative
     */
    void BCS(); // Relative addressing


    /**
     * BEQ - Branch if Equal
     * 
     * This instruction tests the zero flag and branches if it is set.
     * 
     * Addressing modes:
     * - Relative
     */
    void BEQ(); // Relative addressing


    /**
     * BIT - Bit Test
     * 
     * This instructions is used to test if one or more bits are set in a target memory location.
     * 
     * Addressing modes:
     * - Absolute
     * - Zero Page
     */
    void BIT(AddressingMode mode);
    

    /**
     * BMI - Branch if Minus
     * 
     * This instruction tests the negative flag and branches if it is set.
     * 
     * Addressing modes:
     * - Relative
     */
    void BMI();


    /**
     * BNE - Branch if Not Equal
     * 
     * This instruction tests the zero flag and branches if it is clear.
     * 
     * Addressing modes:
     * - Relative
     */
    void BNE();


    /**
     * BPL - Branch if Positive
     * 
     * This instruction tests the negative flag and branches if it is clear.
     * 
     * Addressing modes:
     * - Relative
     */
    void BPL();


    /**
     * BRK - Force Interrupt
     * 
     * This instruction forces the generation of an interrupt request.
     * 
     * Addressing modes:
     * - Implied
     */
    void BRK();


    /**
     * BVC - Branch if Overflow Clear
     * 
     * This instruction tests the overflow flag and branches if it is clear.
     * 
     * Addressing modes:
     * - Relative
     */
    void BVC();


    /**
     * BVS - Branch if Overflow Set
     * 
     * This instruction tests the overflow flag and branches if it is set.
     * 
     * Addressing modes:
     * - Relative
     */
    void BVS();


    /**
     * CLC - Clear Carry Flag
     * 
     * This instruction clears the carry flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void CLC();


    /**
     * CLD - Clear Decimal Mode
     * 
     * This instruction clears the decimal mode flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void CLD();


    /**
     * CLI - Clear Interrupt Disable
     * 
     * This instruction clears the interrupt disable flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void CLI();


    /**
     * CLV - Clear Overflow Flag
     * 
     * This instruction clears the overflow flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void CLV();


    /**
     * CMP - Compare Memory with Accumulator
     * 
     * This instruction compares the contents of a memory location with the accumulator.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void CMP(AddressingMode mode);


    /**
     * CPX - Compare Memory and Index X
     * 
     * This instruction compares the contents of a memory location with the index X register.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Absolute
     */
    void CPX(AddressingMode mode);


    /**
     * CPY - Compare Memory and Index Y
     * 
     * This instruction compares the contents of a memory location with the index Y register.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Absolute
     */
    void CPY(AddressingMode mode);


    /**
     * DEC - Decrement Memory by One
     * 
     * This instruction subtracts one from the value held at a specified memory location.
     * 
     * Addressing modes:
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     */
    void DEC(AddressingMode mode);


    /**
     * DEX - Decrement Index X by One
     * 
     * This instruction subtracts one from the X register.
     * 
     * Addressing modes:
     * - Implied
     */
    void DEX();

    
    /**
     * DEY - Decrement Index Y by One
     * 
     * This instruction subtracts one from the Y register.
     * 
     * Addressing modes:
     * - Implied
    */
   void DEY();


   /**
    * EOR - Exclusive OR
    * 
    * This instruction performs an exclusive OR on the contents of a memory location with the accumulator.
    * 
    * Addressing modes:
    * - Immediate
    * - Zero Page
    * - Zero Page with X index
    * - Absolute
    * - Absolute with X index
    * - Absolute with Y index
    * - Indirect with X index
    * - Indirect with Y index
    */
    void EOR(AddressingMode mode);
    

    /**
     * INC - Increment Memory by One
     * 
     * This instruction adds one to the value held at a specified memory location.
     * 
     * Addressing modes:
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     */
    void INC(AddressingMode mode);


    /**
     * INX - Increment Index X by One
     * 
     * This instruction adds one to the X register.
     * 
     * Addressing modes:
     * - Implied
     */
    void INX();


    /**
     * INY - Increment Index Y by One
     * 
     * This instruction adds one to the Y register.
     * 
     * Addressing modes:
     * - Implied
     */
    void INY();


    /**
     * JMP - Jump to New Location
     * 
     * This instruction transfers program control to a new location.
     * 
     * Addressing modes:
     * - Absolute
     * - Indirect
     */
    void JMP(AddressingMode mode);


    /**
     * JSR - Jump to New Location Saving Return Address
     * 
     * This instruction saves the current program counter on the stack and transfers control to a new location.
     * 
     * Addressing modes:
     * - Absolute
     */
    void JSR(AddressingMode mode);


    /**
     * LDA - Load Accumulator with Memory
     * 
     * This instruction loads the accumulator with a value from memory.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void LDA(AddressingMode mode);


    /**
     * LDX - Load Index X with Memory
     * 
     * This instruction loads the X register with a value from memory.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with Y index
     * - Absolute
     * - Absolute with Y index
     */
    void LDX(AddressingMode mode);


    /**
     * LDY - Load Index Y with Memory
     * 
     * This instruction loads the Y register with a value from memory.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     */
    void LDY(AddressingMode mode);

    
    /**
     * LSR - Logical Shift Right
     * 
     * This instruction shifts all bits in either the accumulator or memory one position to the right.
     * 
     * Addressing modes:
     * - Accumulator
     * - Zero Page
     * - Zero Page with X index
     * 
     * - Absolute with X index
     * - Absolute
     * - Absolute with X index
     */
    void LSR(AddressingMode mode);


    /**
     * NOP - No Operation
     * 
     * This instruction performs no operation.
     * 
     * Addressing modes:
     * - Implied
     */
    void NOP();

    
    /**
     * ORA - OR Memory with Accumulator
     * 
     * This instruction performs a logical OR on the contents of a memory location and the accumulator.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void ORA(AddressingMode mode);


    /**
     * PHA - Push Accumulator on Stack
     * 
     * This instruction pushes the contents of the accumulator onto the stack.
     * 
     * Addressing modes:
     * - Implied
     */
    void PHA();


    /**
     * PHP - Push Processor Status on Stack
     * 
     * This instruction pushes the processor status register onto the stack.
     * 
     * Addressing modes:
     * - Implied
     */
    void PHP();


    /**
     * PLA - Pull Accumulator from Stack
     * 
     * This instruction pulls the contents of the accumulator from the stack.
     * 
     * Addressing modes:
     * - Implied
     */
    void PLA();


    /**
     * PLP - Pull Processor Status from Stack
     * 
     * This instruction pulls the processor status register from the stack.
     * 
     * Addressing modes:
     * - Implied
     */
    void PLP();


    /**
     * ROL - Rotate Left
     * 
     * This instruction rotates all bits in either the accumulator or memory one position to the left.
     * 
     * Addressing modes:
     * - Accumulator
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     */
    void ROL(AddressingMode mode);


    /**
     * ROR - Rotate Right
     * 
     * This instruction rotates all bits in either the accumulator or memory one position to the right.
     * 
     * Addressing modes:
     * - Accumulator
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     */
    void ROR(AddressingMode mode);


    /**
     * RTI - Return from Interrupt
     * 
     * This instruction pulls the processor status register from the stack and restores the processor status.
     * 
     * Addressing modes:
     * - Implied
     */
    void RTI();

    
    /**
     * RTS - Return from Subroutine
     * 
     * This instruction pulls the program counter from the stack and restores the program counter.
     * 
     * Addressing modes:
     * - Implied
     */
    void RTS();


    /** 
     * SBC - Subtract with Carry
     * 
     * This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit.
     * 
     * Addressing modes:
     * - Immediate
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void SBC(AddressingMode mode); // Immediate


    /**
     * SEC - Set Carry Flag
     * 
     * This instruction sets the carry flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void SEC();


    /**
     * SED - Set Decimal Flag
     * 
     * This instruction sets the decimal mode flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void SED();


    /**
     * SEI - Set Interrupt Disable
     * 
     * This instruction sets the interrupt disable flag.
     * 
     * Addressing modes:
     * - Implied
     */
    void SEI();


    /**
     * STA - Store Accumulator in Memory
     * 
     * This instruction stores the contents of the accumulator in memory.
     * 
     * Addressing modes:
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     * - Absolute with X index
     * - Absolute with Y index
     * - Indirect with X index
     * - Indirect with Y index
     */
    void STA(AddressingMode mode);


    /**
     * STX - Store Index X in Memory
     * 
     * This instruction stores the contents of the X register in memory.
     * 
     * Addressing modes:
     * - Zero Page
     * - Zero Page with Y index
     * - Absolute
     */
    void STX(AddressingMode mode);


    /**
     * STY - Store Index Y in Memory
     * 
     * This instruction stores the contents of the Y register in memory.
     * 
     * Addressing modes:
     * - Zero Page
     * - Zero Page with X index
     * - Absolute
     */
    void STY(AddressingMode mode);


    /**
     * TAX - Transfer Accumulator to Index X
     * 
     * This instruction transfers the contents of the accumulator to the X register.
     * 
     * Addressing modes:
     * - Implied
     */
    void TAX();


    /**
     * TAY - Transfer Accumulator to Index Y
     * 
     * This instruction transfers the contents of the accumulator to the Y register.
     * 
     * Addressing modes:
     * - Implied
     */
    void TAY();


    /**
     * TSX - Transfer Stack Pointer to Index X
     * 
     * This instruction transfers the contents of the stack pointer to the X register.
     * 
     * Addressing modes:
     * - Implied
     */
    void TSX();


    /**
     * TXA - Transfer Index X to Accumulator
     * 
     * This instruction transfers the contents of the X register to the accumulator.
     * 
     * Addressing modes:
     * - Implied
     */
    void TXA();


    /**
     * TXS - Transfer Index X to Stack Register
     * 
     * This instruction transfers the contents of the X register to the stack pointer.
     * 
     * Addressing modes:
     * - Implied
     */
    void TXS();


    /**
     * TYA - Transfer Index Y to Accumulator
     * 
     * This instruction transfers the contents of the Y register to the accumulator.
     * 
     * Addressing modes:
     * - Implied
     */
    void TYA();

    // Flag manipulation
    void SetFlag(uint8_t flag, bool value);
    bool GetFlag(uint8_t flag);


    // Addressing mode methods
    uint8_t Immediate(); // Immediate addressing returns the immediate value (single byte)
    uint16_t Absolute(); // Absolute addressing returns a 16-bit address
    uint8_t ZeroPage(); // Zero Page addressing returns a single byte address
    uint8_t ZeroPage_X(); // Zero Page with X index returns a single byte address
    uint8_t ZeroPage_Y(); // Zero Page with Y index returns a single byte address
    uint16_t Absolute_X(); // Absolute with X index returns a 16-bit address
    uint16_t Absolute_Y(); // Absolute with Y index returns a 16-bit address
    uint16_t Indirect_X(); // Indirect with X index returns a 16-bit address
    uint16_t Indirect_Y(); // Indirect with Y index returns a 16-bit address

};
#endif // CPU_H
