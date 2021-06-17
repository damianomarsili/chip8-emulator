#ifndef CHIP_H
#define CHIP_H

#include <cstdint>
#include <string>

class Chip {
	public:
		uint8_t memory[0xFFF];
		uint8_t registers[16];
		uint16_t i_register;
		uint8_t delay_register;
		uint8_t sound_register;
		uint16_t PC;
		uint8_t SP;
		uint16_t stack[16];
		uint16_t opcode;

		Chip(std::string filename);
	private:
		void load_rom(std::string filename);

		void op_0nnn(); void op_00e0(); void op_00ee(); void op_1nnn();
		void op_2nnn(); void op_3xkk(); void op_4xkk(); void op_5xy0();
		void op_6xkk(); void op_7xkk(); void op_8xy0(); void op_8xy1();
		void op_8xy2(); void op_8xy3(); void op_8xy4(); void op_8xy5();
		void op_8xy6(); void op_8xy7(); void op_8xye(); void op_9xy0();
		void op_annn(); void op_bnnn(); void op_cxkk(); void op_dxyn();
		void op_ex9e(); void op_exa1(); void op_fx07(); void op_fx0a();
		void op_fx15(); void op_fx18(); void op_fx1e(); void op_fx29();
		void op_fx33(); void op_fx55(); void op_fx65(); 

};

#endif // CHIP_H
