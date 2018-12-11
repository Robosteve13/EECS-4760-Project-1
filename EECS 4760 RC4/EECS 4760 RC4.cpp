//////////////////////////////////////////////////////////////////////////
//	EECS 4760: Computer Security										//
//	Programming Lab #1													//
//	Created by: Adam Savel												//
//																		//
//	 The goal of this project is to implement both the RC4 algorithm	//
//	for encryption and decryption and a command line interface for		//
//	passing files through the encryption/decryption algorithm.			//
//																		//
//	 RC4 is a method of encryption/decryption that implements our		//
//	theoretical 'One-Time Pad' example.  At RC4's core is a 256-byte	//
//	array, known as 'the State', or 'S'.  Since S is 256 values long,	//
//	and each is a byte, each value can be viewed as either a data byte, //
//	or as a location within the array, and the algorithm takes 			//
//	advantage of this flexibility of interpretation.					//
//																		//
//	 There are three distinct phases to RC4's operation:				//
//		1. Initialization												//
//		2. Key Schedule Generation										//
//		3. Operation													//
//																		//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <fstream>

int validateInput(int, char* argv[]);

int main(int argc, char *argv[])
{	//	 main(int argc, char *argv[]): contains the implementation of the
	//	command-line interface for the RC4 algorithm.
	//	

	//	Process overview:
	//	 0. Read the input
	//	 1. Check for valid input
	//		a. Validate key format
	//		b. Validate infile format
	//		c. Validate outfile format
	//	 2. Determine what to do based on given input
	//		a. Check if infile is to be a file or stream of hex
	//		b. Check if outfile is to be a file or stream of hex
	//	 3. Initialize RC4 algorithm with supplied key
	//		a. Read the input stream
	//		b. Produce output stream
	//	 4.	Output result is desired manner

	std::cout << "" << std::endl;

	//	Step 1(a - c):
	if (validateInput(argc, argv) != 0)
	{
		std::cin.get();
		return 0;
	}

	//	Step 2:
	bool fileInput = (strlen(argv[2]) == 1);
	bool fileOutput = (strlen(argv[3]) == 1);

	//	Step 3 and 4:


	std::cin.get();

    return 0;
}

int validateInput(int argc, char* argv[])
{	//	 validateInput(int argc, char* argv[]): takes the input arguments
	//	and determines if they are acceptable.  If the input is less than
	//	acceptable, display the issue and return an error value.
	//
	//	 Returns and int where the value determines the outcome of the
	//	check:
	//		 0: Input is fine
	//		-1: Input is less than beuno

	// Check for correct number of arguments
	bool numGood = (argc == 4);


	// Check key
	size_t keyLen = strlen(argv[1]);
	bool keyGood = false;

	// - Check key format == '<key no spaces>'
	if (argv[1][0] == argv[1][keyLen - 1] && argv[1][0] == '\'')
	{
		for (int i = 0; i < keyLen; i++)
		{
			if (argv[1][i] < ' ') break;
			if (i + 1 == keyLen) keyGood = true;
		}
	}

	// - Check key format == "<key>"
	else if (argv[1][0] == argv[1][keyLen - 1] && argv[1][0] == '\"') keyGood = true;

	// - Check key format == <key in HEX>
	else
	{
		if (keyLen % 2 == 0)
		{
			for (int i = 0; i < keyLen; i++)
			{
				//	If the current char is lowercase... make it uppercase!
				if (argv[1][i] >= 'a' && argv[1][i] <= 'z') argv[1][i] = toupper(argv[1][i]);

				if (argv[1][i] < '0') break;
				if (argv[1][i] > '9' && argv[1][i] < 'A') break;
				if (argv[1][i] > 'F') break;
				if (i + 1 == keyLen) keyGood = true;
			}
		}
	}

	// Check infile expression
	bool infileGood = false;
	size_t infileLen = strlen(argv[2]);
	std::fstream test(argv[2], std::ios::binary | std::ios::in);
	
	if (infileLen == 1 && argv[2][0] == '-') infileGood = true;
	else if (test) infileGood = true;
	test.close();

	// Check outfile expression
	bool outfileGood;
	size_t outfileLen = strlen(argv[3]);
	test.open(argv[3], std::ios::binary | std::ios::out);

	if (infileLen == 1 && argv[3][0] == '-') outfileGood = true;
	else if (test.is_open()) outfileGood = true;
	test.close();


	//	Display the proper error
	if (!numGood)
	{
		std::cout << "Invalid number of inputs." << std::endl;
		std::cout << "RC4 <key> <infile> <outfile>" << std::endl;
		return -1;
	}
	if (!keyGood)
	{
		std::cout << "Invalid Key." << std::endl;
		std::cout << "RC4 <key> <infile> <outfile>" << std::endl;
		std::cout << "Key must be in one of the following formats:" << std::endl;
		std::cout << "	- \'<key with no spaces>\'" << std::endl;
		std::cout << "	- \"<key>\"" << std::endl;
		std::cout << "	- <hex value>" << std::endl;
		return -1;
	}
	if (!infileGood)
	{
		std::cout << "Invalid infile expression." << std::endl;
		std::cout << "RC4 <key> <infile> <outfile>" << std::endl;
		std::cout << "Must either be a valid file specification or \'-\' to indicate standard input" << std::endl;
		return -1;
	}
	if (!outfileGood)
	{
		std::cout << "Invalid outfile expression" << std::endl;
		std::cout << "RC4 <key> <infile> <outfile>" << std::endl;
		std::cout << "Must either be a valid file specification or \'-\' to indicate standard input" << std::endl;
		return -1;
	}

	return 0;
}
