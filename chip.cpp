#include <string>
#include "chip.h"
#include <iostream>
#include <fstream>

// --- Initialization functions ---

Chip::Chip(std::string filename) {
	PC = 0x200;
	SP = 0;
	opcode = 0;
	delay_register = 0;
	sound_register = 0;

	uint8_t sprites[80] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // "0"
		0x20, 0x60, 0x20, 0x20, 0x70, // "1"
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // "2"
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // "3"
		0x90, 0x90, 0xF0, 0x10, 0x10, // "4"
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // "5"
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // "6"
		0xF0, 0x10, 0x20, 0x40, 0x40, // "7"
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // "8"
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // "9"
		0xF0, 0x90, 0xF0, 0x90, 0x90, // "A"
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // "B"
		0xF0, 0x80, 0x80, 0x80, 0xF0, // "C"
		0xE0, 0x90, 0x90, 0x90, 0xE0, // "D"
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // "E"
		0xF0, 0x80, 0xF0, 0x80, 0x80 // "F"
	};

	for (int x = 0; x < 80; x++) {
		memory[x] = sprites[x];
	}

	load_rom(filename);
}


void Chip::load_rom(std::string filename) {
	std::ifstream rom(filename, std::ios::binary | std::ios::ate);

	if (rom.is_open()) {
		std::streampos size = rom.tellg();
		char * buffer = new char[size];

		rom.seekg(0, std::ios::beg);
		rom.read(buffer, size);
		rom.close();

		for (long x = 0; x < size; x++) {
			memory[0x200 + x] = buffer[x];
		}

		delete buffer;
	}
}

// --- Opcode Functions ---

void Chip::op_0nnn() {
	// TODO: FIGURE OUT
}

void Chip::op_00e0() {
	// TODO: FIGURE OUT
}

void Chip::op_1nnn() {
	PC = opcode & 0x0FFF;
}

void Chip::op_2nnn() {
	SP++;
	stack[SP] = PC;
	PC = opcode & 0x0FFF;
}

void Chip::op_3xkk() {
	if (registers[opcode & 0x0F00] == opcode & 0x00FF) {
		PC += 2;
	}
}

void Chip::op_4xkk() {
	if (registers[opcode & 0x0F00] != opcode & 0x00FF) {
		PC += 2;
	}
}

void Chip::op_5xy0() {
	if (registers[opcode & 0x0F00] == registers[opcode & 0x00F0]) {
		PC += 2;
	}
}

void Chip::op_6xkk() {
	registers[opcode & 0x0F00] = opcode & 0x00FF;
}

void Chip::op_7xkk() {
	registers[opcode & 0x0F00] += opcode & 0x00FF;
}

void Chip::op_8xy0() {
	registers[opcode & 0x0F00] = registers[opcode & 0x00F0];
}

void Chip::op_8xy1() {
	registers[opcode & 0x0F00] |= registers[opcode & 0x00F0];
}

void Chip::op_8xy2() {
	registers[opcode & 0x0F00] &= registers[opcode & 0x00F0];
}

void Chip::op_8xy3() {
	registers[opcode & 0x0F00] ^= registers[opcode & 0x00F0];
}

void Chip::op_8xy4() {
	uint16_t temp = registers[opcode & 0x0F00] + registers[opcode & 0x00F0];
	if (temp > 255) {
		temp &= 0xFF;
		registers[0xF] = 1;
	} else {
		registers[0xF] = 0;
	}

	registers[opcode & 0x0F00] = temp;
}

void Chip::op_8xy5() {
	if (registers[opcode & 0x0F00] > registers[opcode & 0x00F0]) {
		registers[0xF] = 1;
	} else {
		registers[0xF] = 0;
	}

	registers[opcode & 0x0F00] -= registers[opcode & 0x00F0];
}

void Chip::op_8xy6() {
	if (registers[opcode & 0x0F00] & 0x1) {
		registers[0xF] = 1;
	} else {
		registers[0xF] = 0;
	}

	registers[opcode & 0x0F00] /= 2;
}

void Chip::op_8xy7() {
	if (registers[opcode & 0x0F00] < registers[opcode & 0x00F0]) {
		registers[0xF] = 1;
	} else { 
		registers[0xF] = 0;
	}

	registers[opcode & 0x0F00] = registers[opcode & 0x00F0] - registers[opcode & 0x0F00]; 
}

void Chip::op_8xye() {
	if (registers[opcode & 0x0F00] & 0xFFFF) {
		registers[0xF] = 1;
	} else {
		registers[0xF] = 0;
	}

	registers[opcode & 0x0F00] *= 2;
}





















