#ifndef ENCODER_H
#define ENCODER_H

#include "global_data.h"
#include "searchers/searcher.h"

#include <memory>

class Encoder
{
public:
	explicit Encoder(GlobalData &data);
	~Encoder() = default;

	void encode_and_solve();
	void encode_and_print_dimacs();

private:
	GlobalData &global_data;

	std::unique_ptr<Searcher> searcher;

	std::unique_ptr<Searcher> get_searcher();
};

#endif
