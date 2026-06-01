#ifndef MMSL_ENCODER_H
#define MMSL_ENCODER_H

#include "searchers/mmsl_iterate.h"

class MMSLEncoder
{
public:
	MMSLEncoder();
	~MMSLEncoder();

	void encode_and_solve();
	void encode_and_print_dimacs();

private:
	MMSLIterate *mmsl_searcher = nullptr;

	void setup_searcher();
};

#endif
