/* ****************************************************************************
judger.h
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


#ifndef CHIPOKER_JUDGER_H
#define CHIPOKER_JUDGER_H

#include "prerequisites.h"
#include "card.h"

namespace Chipoker
{
	class Judger
	{
	public:
		static bool pair(const std::vector<Card>& cards);
		static bool joker_pair(const std::vector<Card>& cards);
		static bool triple(const std::vector<Card>& cards);
		static bool quadruple(const std::vector<Card>& cards);
		static bool triple_with_single(const std::vector<Card>& cards);
		static bool triple_with_pair(const std::vector<Card>& cards);
		static bool quadruple_with_pair(const std::vector<Card>& cards);
		static bool single_straight(const std::vector<Card>& cards);
		static bool double_straight(const std::vector<Card>& cards);
		static bool triple_straight(const std::vector<Card>& cards);
		static bool airplane(const std::vector<Card>& cards);

		static bool legal_cards(const std::vector<Card>& cards);
		static bool legal_cards(const std::vector<Card>& old_cards, const std::vector<Card>& new_cards);
		static bool to_follow(const std::vector<Card>& old_cards, const std::vector<Card>& new_cards);
	};

	inline bool Judger::pair(const std::vector<Card>& cards)
	{
		if (cards.size() != 2)
			return false;

		if (cards[0].get_value() == cards[1].get_value() ||
			(cards[0] == Card::black_joker && cards[1] == Card::red_joker) ||
			(cards[0] == Card::red_joker && cards[1] == Card::black_joker))
			return true;
		return false;
	}

	inline bool Judger::joker_pair(const std::vector<Card>& cards)
	{
		if ((cards[0] == Card::black_joker && cards[1] == Card::red_joker) ||
			(cards[0] == Card::red_joker && cards[1] == Card::black_joker))
			return true;
		return false;
	}

	inline bool Judger::triple(const std::vector<Card>& cards)
	{
		if (cards.size() != 3)
			return false;

		if (cards[0].get_value() == cards[1].get_value() &&
			cards[1].get_value() == cards[2].get_value())
			return true;
		return false;
	}

	inline bool Judger::quadruple(const std::vector<Card>& cards)
	{
		if (cards.size() != 4)
			return false;
		if (cards[0].get_value() == cards[1].get_value() &&
			cards[1].get_value() == cards[2].get_value() &&
			cards[2].get_value() == cards[3].get_value())
			return true;
		return false;
	}

	inline bool Judger::triple_with_single(const std::vector<Card>& cards)
	{
		if (cards.size() != 4)
			return false;

		if (cards[0].get_value() == cards[1].get_value() &&
			cards[1].get_value() == cards[2].get_value())
			return true;
		return false;
	}

	inline bool Judger::triple_with_pair(const std::vector<Card>& cards)
	{
		if (cards.size() != 5)
			return false;

		if (cards[0].get_value() == cards[1].get_value() &&
			cards[1].get_value() == cards[2].get_value() &&
			cards[3].get_value() == cards[4].get_value())
			return true;
		return false;
	}

	inline bool Judger::quadruple_with_pair(const std::vector<Card>& cards)
	{
		if (cards.size() != 6)
			return false;

		if (cards[0].get_value() == cards[1].get_value() &&
			cards[1].get_value() == cards[2].get_value() &&
			cards[2].get_value() == cards[3].get_value() &&
			cards[4].get_value() == cards[5].get_value())		
			return true;		
		return false;
	}

	inline bool Judger::single_straight(const std::vector<Card>& cards)
	{
		if (cards.size() < 5)
			return false;

		for (size_t i = 1; i < cards.size(); ++i)
		{
			if ((int)cards[i].get_value() - (int)cards[i - 1].get_value() != 1)
				return false;
			if (cards[i].get_value() == Card::c2)
				return false;
		}
		return true;
	}

	inline bool Judger::double_straight(const std::vector<Card>& cards)
	{
		if (cards.size() < 6)
			return false;
		if (cards.size() % 2 != 0)
			return false;

		for (size_t i = 1; i < cards.size(); i += 2)
		{
			if (cards[i].get_value() != cards[i - 1].get_value())
				return false;
		}
		return true;
	}

	inline bool Judger::triple_straight(const std::vector<Card>& cards)
	{
		if (cards.size() < 6)
			return false;
		if (cards.size() % 3 != 0)
			return false;

		for (size_t i = 2; i < cards.size(); i += 3)
		{
			if (cards[i].get_value() != cards[i - 1].get_value() ||
				cards[i - 1].get_value() != cards[i - 2].get_value())
				return false;
		}
		return true;
	}

	inline bool Judger::airplane(const std::vector<Card>& cards)
	{
		if (cards.size() != 8 && cards.size() != 10)
			return false;

		for (size_t i = 2; i < 6; i += 3)
		{
			if (cards[i].get_value() != cards[i - 1].get_value() ||
				cards[i - 1].get_value() != cards[i - 2].get_value())
				return false;
		}

		if (cards.size() == 8)		
			return true;

		// cards.size() == 10
		if (cards[7].get_value() == cards[6].get_value() &&
			cards[9].get_value() == cards[8].get_value())
			return true;
		return false;
	}

	inline bool Judger::legal_cards(const std::vector<Card>& cards)
	{
		switch (cards.size())
		{
		case 0:
			return false;

		case 1:
			return true;
			
		default:
			if (pair(cards))
				return true;
			if (triple(cards))
				return true;
			if (triple_with_single(cards))
				return true;
			if (triple_with_pair(cards))
				return true;
			if (single_straight(cards))
				return true;			
			if (double_straight(cards))
				return true;
			if (triple_straight(cards))
				return true;
			if (quadruple_with_pair(cards))
				return true;
			if (airplane(cards))
				return true;
			return false;
		}
		return true;
	}

	inline bool Judger::to_follow(const std::vector<Card>& old_cards, const std::vector<Card>& new_cards)
	{
		return true;
	}
} // namespace Chipoker

#endif // CHIPOKER_JUDGER_H