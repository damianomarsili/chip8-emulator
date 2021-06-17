#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "chip.h"


int main() {
	std::string rom_name;
	std::cout << "Please enter ROM filename" << std::endl;
	std::cin >> rom_name;
	Chip c = Chip(rom_name); 
	std::cout << "all good " << std::endl;
	return 0;
}
