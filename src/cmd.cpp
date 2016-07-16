#include "compiler.h"
#include "error.h"

#include <vector>
#include <iostream>
#include "string.h"

/**
 * \brief Display following options control optimizations
 */

void Compiler::displayOptimizersHelp (int argc, char *argv[]) {

	std::vector<Option> options;

	options.push_back ({"-O<number>", "Set optimization level to <number>"});
	options.push_back ({"-Ofast"    , "Optimize for speed disregarding exact standards"});
	options.push_back ({""          , "compliance"});

	// Print
	std::cout << "The following options control optimizations:" << std::endl;

	for (auto const &option : options) {

		std::cout.width (28);
		std::cout << std::left << "  "+option.name << option.text << std::endl;

	}

}

/**
 * \brief Display main help information
 */

void Compiler::displayMainHelp (int argc, char *argv[]) {

	std::vector<Option> options;

	options.push_back ({"--help"               , "Display this information"});
	options.push_back ({"--emit={asm|llvm|cpp}", "Display generated code"});
	options.push_back ({"--version"            , "Display compiler version"});
	options.push_back ({"-v"                   , "Display the programs invoked by the compiler"});
	options.push_back ({"-o <file>"            , "Place the output into <file>"});

	// Print
	std::cout << "Usage: " << argv[0] << " [options] file..." << std::endl;
	std::cout << "Options:" << std::endl;

	for (auto const &option : options) {

		std::cout.width (28);
		std::cout << std::left << "  "+option.name << option.text << std::endl;

	}

}

/**
 * \brief Parse command line
 */

void Compiler::parseCmd (int argc, char *argv[]) {

	for (int i = 1; i < argc; ++i) {

		if (strcmp(argv[i], "--help") == 0) {

			displayMainHelp (argc, argv);
			exit(0);

		} else if (strcmp(argv[i], "--help=optimizers") == 0) {

			displayOptimizersHelp (argc, argv);

		} else if (strcmp(argv[i], "--emit=asm") == 0) {

		} else if (strcmp(argv[i], "--emit=llvm") == 0) {

		} else if (strcmp(argv[i], "--emit=cpp") == 0) {

		} else if (strcmp(argv[i], "-o") == 0) {

			++i;

			if (i < argc) output = argv[i];
			//else return Error<int>(no_input_file);

			continue;

		} else {
			input = argv[1];
		}

	}

	//
	loadMessages();

}
