#ifndef ENCODER_H
#define ENCODER_H

#include "searchers/searcher.h"

class Encoder
{
public:
	Encoder();
	~Encoder();

	void encode_and_solve();
	void encode_and_print_dimacs();

private:
	Searcher *searcher = nullptr;

	void setup_searcher();
};

#endif
