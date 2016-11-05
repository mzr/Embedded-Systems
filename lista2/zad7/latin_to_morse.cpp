#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#define latin_extended 0
#define numbers 0
#define interpunction_and_symbols 0

// . 	kropka
// - 	kreska
// ' ' 	odstep miedzy literami
// / 	odstep miedzy wyrazami

std::string morse_letter(const char & letter)
{
	try {
		if(letter == 'a') return ".-";
		if(letter == 'b') return "-...";
		if(letter == 'c') return "-.-.";
		if(letter == 'd') return "-..";
		if(letter == 'e') return ".";
		if(letter == 'f') return "..-.";
		if(letter == 'g') return "--.";
		if(letter == 'h') return "....";
		if(letter == 'i') return "..";
		if(letter == 'j') return ".---";
		if(letter == 'k') return "-.-";
		if(letter == 'l') return ".-..";
		if(letter == 'm') return "--";
		if(letter == 'n') return "-.";
		if(letter == 'o') return "---";
		if(letter == 'p') return ".--.";
		if(letter == 'q') return "--.-";
		if(letter == 'r') return ".-.";
		if(letter == 's') return "...";
		if(letter == 't') return "-";
		if(letter == 'u') return "..-";
		if(letter == 'v') return "...-";
		if(letter == 'w') return ".--";
		if(letter == 'x') return "-..-";
		if(letter == 'y') return "-.--";
		if(letter == 'z') return "--..";

	#if numbers
		//wersja pełna

		if(letter == '1') return ".----";
		if(letter == '2') return "..---";
		if(letter == '3') return "...--";
		if(letter == '4') return "....-";
		if(letter == '5') return ".....";
		if(letter == '6') return "-....";
		if(letter == '7') return "--...";
		if(letter == '8') return "---..";
		if(letter == '9') return "----.";
		if(letter == '0') return "-----";

	#endif

	#if interpunction_and_symbols

		if(letter == '.') return ".-.-.-";
		if(letter == ',') return "--..--";
		if(letter == '\'') return ".----.";
		if(letter == '"') return ".-..-.";
		if(letter == '_') return "..--.-";
		if(letter == ':') return "---...";
		if(letter == ';') return "-.-.-.";
		if(letter == '?') return "..--..";
		if(letter == '!') return "-.-.--"; // lub --..--
		if(letter == '-') return "-....-";
		if(letter == '+') return ".-.-.";
		if(letter == '/') return "-..-.";
		if(letter == '(') return "-.--.";
		if(letter == '_') return "-.--.-";
		if(letter == '=') return "-...-";
		if(letter == '@') return ".--.-.";

	#endif

	#if latin_extended

		//bez ch i e z daszkiem

		if(letter == 'ą') return ".-.-";
		if(letter == 'ć') return "-.-..";
		if(letter == 'ę') return "..-..";
		if(letter == 'ł') return ".-..-";
		if(letter == 'ń') return "--.--";
		if(letter == 'ó') return "---.";
		if(letter == 'ś') return "...-...";
		if(letter == 'ż') return "--..-.";
		if(letter == 'ź') return "--..-";

	#endif	

		throw std::invalid_argument( "wrong_letter" );
	}
	catch( const std::exception & e )
	{
		std::cout << e.what();
	}
}

std::string morse_word(const std::string & word)
{
	std::string output;
	auto it = word.begin();

	for( it ; it != word.end() - 1; it++)
		output += morse_letter(*it) + " ";

	output += morse_letter(*it);

	return output;
}

std::string morse_text(const std::string & text)
{
	std::string output;
	std::istringstream buf(text);

	for(std::string word; buf >> word; )
		output += morse_word(word) + "/"; 

	output.pop_back();
	return output;
}

int main()
{
	std::cout << morse_text("");
	return 0;
}