#include "cpu.hpp"  // Include the header for the CPU class
#include <gtest/gtest.h>

TEST(CPUTest, ConstructorInitializesCorrectly) {
    CPU cpu;
    // Check that memory is allocated
    ASSERT_NE(cpu.memory, nullptr) << "Memory allocation failed";

    // Check initial values of the registers
    EXPECT_EQ(cpu.A, 0) << "Accumulator not initialized to 0";
    EXPECT_EQ(cpu.X, 0) << "X register not initialized to 0";
    EXPECT_EQ(cpu.Y, 0) << "Y register not initialized to 0";
    EXPECT_EQ(cpu.SP, 0xFF) << "Stack Pointer not initialized to 0xFF";
    EXPECT_EQ(cpu.P, CPU::UNUSED_FLAG) << "Processor status not initialized correctly";
}
