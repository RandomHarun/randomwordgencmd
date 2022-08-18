/* 
Random Word Generator Command-Line Tool
Author: Phillip Haarhaus, 2022
Motivation: https://xkcd.com/936/
This is a learning project. It is intended for personal use, i.e. not to be integrated into some larger automated process. It is not tested to be rigorous against unforseen inputs. Accidental file overwriting may occur. Use at your own risk.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include "sodium.h"

struct wordliststruct {
	uint32_t wordcount;
	uint16_t biggestword;
} wordliststats;

uint32_t randombytes_uniform(const uint32_t upper_bound);

//I expect one word per line but I don't want to check for / prevent that not being the case and it shouldn't matter ultimately.
void getwordliststats(std::ifstream *wordlist)
{
	std::string word;
	uint32_t wordcount = 0;
	uint32_t biggestword = 0;

	while (std::getline(*wordlist, word))
	{
		++wordcount;
		if (word.size() > biggestword)
		{
			biggestword = word.size();
		}
	}

	wordliststats.wordcount = wordcount;
	wordliststats.biggestword = biggestword;
}

std::string generaterandomword(std::string randomword, std::string *wordlistarray, uint32_t arrayelementcount)
{
	uint32_t randomnumber = randombytes_uniform(arrayelementcount);

	randomword = wordlistarray[randomnumber];

	return randomword;
}

int main(int argc, char **argv)
{
	std::string usagestring = "Usage:\n[-h] or no argument to display this help info.\n[-i wordlist] path to wordlist text file. 1 word per line. Will try to open a \"wordlist.txt\" in the same folder as the executable by default.\n[-o output-file] path to output file. if none given, output will be to the console.\n[-n count] number of random words to generate, default is 1.\n[-d delimiter] delimiting string between output words(can be single character), newline by default.\n[-v] Enable verbose display. (more information about chosen settings and odds of the calculated sequence being guessed.)\n";
	std::string wordlistpath;
	std::string outputpath;
	std::string delimiter;
	std::string line;
	bool verboselogging = 0;
	uint64_t wordstogenerate = 1;
	std::ifstream wordlist;
	std::ofstream outputfile;
	
		
	//output usage info if no command line arguments are given
	if (argc == 1)
	{
		std::cout << usagestring << "\n";
	}
		
	//handle command line arguments, skipping the 0th, because that will always be the path of the executing application and not useful for this purpose.
	for (int cmdlineargcount = 1; cmdlineargcount < argc; cmdlineargcount++)
	{
		std::string currentargv = argv[cmdlineargcount];
		
		if (currentargv == std::string("-h"))
		{
			std::cout << usagestring << "\n";
		}
		else if (currentargv == std::string("-i"))
		{
			wordlistpath = argv[cmdlineargcount + 1];
		}
		else if (currentargv == std::string("-o"))
		{
			outputpath = argv[cmdlineargcount + 1];
		}
		else if (currentargv == std::string("-n"))
		{
			wordstogenerate = atoi(argv[cmdlineargcount + 1]);
		}
		else if (currentargv == std::string("-d"))
		{
			delimiter = argv[cmdlineargcount + 1];
		}
		else if (currentargv == std::string("-v"))
		{
			verboselogging = 1;
		}
	}
	
	//open filestream for input file,checking first if no custom file was given and trying to open the default or custom file and if that fails, exit.
	if (wordlistpath == std::string(""))
	{
		wordlist.open(".\\wordlist.txt");
	}
	else
	{
		wordlist.open(wordlistpath);
	}

	if (!wordlist)
	{
		std::cout << "The wordlist file was not found or could not be opened." << "\n";
		return 0;
	}

	getwordliststats(&wordlist);

	std::string *wordlistarray = new std::string[wordliststats.wordcount];
	
	wordlist.clear();
	wordlist.seekg(0, std::ios::beg);

	uint32_t arrayindexiterator = 0; //this will double as the array element count once the array is filled.

	for (; arrayindexiterator < wordliststats.wordcount; arrayindexiterator++)
	{
		getline(wordlist, line);
		wordlistarray[arrayindexiterator] = line;
	}

	wordlist.close();
		
	if (verboselogging) {
		std::cout << "Verbose Display enabled." << "\n";
		std::cout << "\n";
		
		if (wordlistpath == std::string(""))
		{
			std::cout << "The wordlist path is: " << "not given. Using default wordlist.txt in current path if it exists." << "\n";
		}
		else 
		{
			std::cout << "The wordlist path is: " << wordlistpath << "\n";
		}
		
		if (outputpath == std::string(""))
		{
			std::cout << "The output filepath is: " << "not given. Output will be to the console." << "\n";
		}
		else
		{
			std::cout << "The output filepath is: " << outputpath << "\n";
		}

		std::cout << "The number of words to generate is: " << wordstogenerate << "\n";

		if (delimiter == std::string(""))
		{
			std::cout << "The delimiter is: " << "not given. Default CLRF aka newline will be used." << "\n";
		}
		else
		{
			std::cout << "The delimiter is: " << delimiter << "\n";
		}
				
		std::cout << "\n";
		
		double decimalodds = pow(1 / double(wordliststats.wordcount), wordstogenerate); //This might be bad for large wordlists but I don't know how to make it better.

		std::cout << "The wordlist is of size: " << wordliststats.wordcount << ".\nIf any word is equally likely to occur, the chance of randomly guessing the sequence of generated words is 1/wordlist-size^word-count, in this case:" << "\n";
		std::cout << decimalodds << "\n";
		std::cout << "\n";

		if (outputpath == std::string(""))
		{
			std::cout << "The randomly generated words are these:" << "\n";
		}		
	}

	//if outputpath was not defined in command line arguments, output to the console, otherwise output to the defined file.
	if (outputpath == std::string(""))
	{
		if (delimiter == std::string("") and argc != 1)
		{
			for (unsigned int generatedwords = 0; generatedwords < wordstogenerate; generatedwords++)
			{
				line = generaterandomword(line, wordlistarray, arrayindexiterator);
				std::cout << line << "\n";
			}			
		}
		else if (argc != 1)
		{
			for (unsigned int generatedwords = 0; generatedwords < wordstogenerate; generatedwords++)
			{
				line = generaterandomword(line, wordlistarray, arrayindexiterator);
				std::cout << line << delimiter;
			}
		}
	}
	else
	{
		outputfile.open(outputpath);

		if (!outputfile)
		{
			std::cout << "The output file could not be opened. The application will try to create a file (but not folders) and overwrite existing ones so this is probably an invalid path or a permissions issue." << "\n";
			wordlist.close();
			return 0;
		}

		if (delimiter == std::string("") and argc != 1)
		{
			for (unsigned int generatedwords = 0; generatedwords < wordstogenerate; generatedwords++)
			{
				line = generaterandomword(line, wordlistarray, arrayindexiterator);
				outputfile << line << "\n";
			}			
		}
		else if (argc != 1)
		{
			for (unsigned int generatedwords = 0; generatedwords < wordstogenerate; generatedwords++)
			{
				line = generaterandomword(line, wordlistarray, arrayindexiterator);
				outputfile << line << delimiter;
			}			
		}

		outputfile.close();
	}	
	
	return 0;
}