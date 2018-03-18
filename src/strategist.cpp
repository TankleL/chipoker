/* ****************************************************************************
strategist.cpp
-------------------------------------------------------------------------------

Copyright (c) 2017, Tain L.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**************************************************************************** */

#include "prerequisites.h"
#include "strategist.h"

using namespace Chipoker;

Strategist::Strategist()
{
	type_tryers.push_back(Strategist::try_single);
	type_tryers.push_back(Strategist::try_pair);
}

std::vector<std::vector<Card>> Strategist::try_single(const std::vector<Card>& cards)
{
	std::vector<std::vector<Card>> possibles;
	for (const Card& card : cards)
	{
		std::vector<Card> single;
		single.push_back(card);
		possibles.push_back(std::move(single));
	}
	return std::move(possibles);
}

std::vector<std::vector<Card>> Strategist::try_pair(const std::vector<Card>& cards)
{
	std::vector<std::vector<Card>> possibles;
	if (cards.size() > 1)
	{// figure out the possible combos
		size_t i = 1;
		while (i < cards.size())
		{
			std::vector<Card>	pair;
			pair.push_back(cards[i - 1]);
			pair.push_back(cards[i]);

			if (Judger::pair(pair))
			{
				possibles.push_back(std::move(pair));
				i += 2;
				continue;
			}
			++i;
		}
	}
	return std::move(possibles);
}

void Strategist::solve(const std::vector<Card>& cards)
{

}