#include <iostream>
#include <string>
#include "state_machine.h"

/**
 * Make a state machine that has transition functions/state
 * functions with the specializations being the states.
*/

using SentenceIterator = std::string::iterator;

struct Sentence 
{
public:
	std::string text = " ";
	int space_count = 0;
	int word_count = 0;
};

namespace Checkage
{
bool is_blank(char word)
{
	return (word == ' ');
}

bool is_alphabetic(char word)
{
	return (word >= 'a' && word <= 'z');
}
}

namespace Parser
{
// we want to send the SentenceIterator because then we will be able to 
// parse the whole string in one go

template<typename T>
void space(int *counter, T current);

template<typename T>
void word(int *counter, T current);

template<>
void space<SentenceIterator>(int *counter, SentenceIterator word)
{
	if(Checkage::is_blank(*word))
	{
		while(Checkage::is_blank(*word))
		{
			(*counter)++;
			++word;
		}
	}
}

template<>
void word<SentenceIterator>(int *counter, SentenceIterator word)
{
	if(!Checkage::is_blank(*word) && Checkage::is_alphabetic(*word))
	{
		while(!Checkage::is_blank(*word) && Checkage::is_alphabetic(*word))
		{
			(*counter)++;
			++word;
		}
	}
}
}

void sentence_create(Sentence *s)
{
	// https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/
	std::cout << "Write something here: ";
	std::getline(std::cin >> std::ws, (*s).text);
}

namespace StateMachine
{
template<typename T>
void start(T *s);

template<>
void start<Sentence>(Sentence *s)
{
	// because we will want to keep track
	// since we will be moving the pointer along
	// we will lose where it started
	SentenceIterator start = (*s).text.begin();
	SentenceIterator end = (*s).text.end();

	for(SentenceIterator it = start; it != end; ++it)
	{
		Parser::space(&((*s).space_count), it);
		Parser::word(&((*s).word_count), it);
	}
}
}

int main()
{
	Sentence sentence;

	// XXX: there is some weird bug where the word count
	// doubles or triples
	// i had, then, separated into different files this side project
	// i'll let the project "as-is" and go on with life
	// i don't know how or why that happened or if it continues to happen
	// to check for the bug, input "banana" and it will give more than seven letters
	// the problem is in sentence_create (the only in stream is this function)
	// but i don't know where and how to fix it
	sentence_create(&sentence);

	StateMachine::start(&sentence);

	std::cout << "In the given text '" << sentence.text << "' there are:\n";
	std::cout << sentence.space_count << " spaces\n";
	std::cout << sentence.word_count << " words\n";

	return 0;
}
