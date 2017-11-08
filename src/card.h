/* ****************************************************************************
card.h
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

#ifndef CHIPOKER_CARD_H
#define CHIPOKER_CARD_H

#include "prerequisites.h"

namespace Chipoker
{
	class Card
	{
	public:
		enum Types : int
		{
			unknown = 0
			, ace = 0x0C
			, c2 = 0x0D
			, c3 = 0x01
			, c4 = 0x02
			, c5 = 0x03
			, c6 = 0x04
			, c7 = 0x05
			, c8 = 0x06
			, c9 = 0x07
			, c10 = 0x08
			, jack = 0x09
			, queen = 0x0A
			, king = 0x0B
			, diamond = 0x10
			, club = 0x20
			, heart = 0x30
			, spade = 0x40
			, black_joker = 0x5f
			, red_joker = 0x6f
		};
		
	public:
		Card();
		Card(const Types& card);

		bool operator<(const Card& rhs) const;
		bool operator>(const Card& rhs) const;
		bool operator==(const Card& rhs) const;
		
	public:
		static Types gen_card(Types color, Types value);

	public:
		Types get_color() const;
		Types get_value() const;
		std::string get_name() const;

	public:
		int m_card;
	}; // class Card


	inline Card::Card() :
		m_card(spade | ace)
	{}

	inline Card::Card(const Types& card) :
		m_card(card)
	{}

	inline bool Card::operator<(const Card& rhs) const
	{		
		if ((m_card & 0x0f) < (rhs.m_card & 0x0f))
			return true;
		else if ((m_card & 0x0f) == (rhs.m_card & 0x0f))
			if ((m_card & 0xf0) < (rhs.m_card & 0xf0))
				return true;
			else
				return false;
		else
			return false;
	}

	inline bool Card::operator>(const Card& rhs) const
	{
		if ((m_card & 0x0f) > (rhs.m_card & 0x0f))
			return true;
		else if ((m_card & 0x0f) == (rhs.m_card & 0x0f))
			if ((m_card & 0xf0) > (rhs.m_card & 0xf0))
				return true;
			else
				return false;
		else
			return false;
	}

	inline bool Card::operator==(const Card& rhs) const
	{
		return m_card == rhs.m_card;
	}

	inline Card::Types Card::get_color() const
	{
		switch (m_card & 0xf0)
		{
		case 0x10:
			return Types::diamond;
		case 0x20:
			return Types::club;
		case 0x30:
			return Types::heart;
		case 0x40:
			return Types::spade;
		default:
			return Types::unknown;
		}
	}

	inline Card::Types Card::get_value() const
	{
		switch (m_card & 0x0f)
		{
		case 0x0C:
			return Types::ace;
		case 0x0D:
			return Types::c2;
		case 0x01:
			return Types::c3;
		case 0x02:
			return Types::c4;
		case 0x03:
			return Types::c5;
		case 0x04:
			return Types::c6;
		case 0x05:
			return Types::c7;
		case 0x06:
			return Types::c8;
		case 0x07:
			return Types::c9;
		case 0x08:
			return Types::c10;
		case 0x09:
			return Types::jack;
		case 0x0A:
			return Types::queen;
		case 0x0B:
			return Types::king;
		default:
			return Types::unknown;
		}
	}

	inline Card::Types Card::gen_card(Types color, Types value)
	{
		assert(color >= 0x10 && color <= 0x60);		

		return static_cast<Types>(color | value);
	}

	inline std::string Card::get_name() const
	{
		switch (m_card)
		{
		case 0x5f:
			return "black joker";

		case 0x6f:
			return "red joker";

		default:
			break;
		}

		std::string color_name;
		Types color = get_color();
		switch (color)
		{
		case Chipoker::Card::diamond:
			color_name = "diamond";
			break;

		case Chipoker::Card::club:
			color_name = "club";
			break;

		case Chipoker::Card::heart:
			color_name = "heart";
			break;

		case Chipoker::Card::spade:
			color_name = "spade";
			break;

		default:
			return "unknown";
		}

		std::string value_name;
		Types value = get_value();
		switch (value)
		{
		case Chipoker::Card::ace:
			value_name = "ace";
			break;

		case Chipoker::Card::c2:
			value_name = "2";
			break;

		case Chipoker::Card::c3:
			value_name = "3";
			break;

		case Chipoker::Card::c4:
			value_name = "4";
			break;

		case Chipoker::Card::c5:
			value_name = "5";
			break;

		case Chipoker::Card::c6:
			value_name = "6";
			break;

		case Chipoker::Card::c7:
			value_name = "7";
			break;

		case Chipoker::Card::c8:
			value_name = "8";
			break;

		case Chipoker::Card::c9:
			value_name = "9";
			break;

		case Chipoker::Card::c10:
			value_name = "10";
			break;

		case Chipoker::Card::jack:
			value_name = "jack";
			break;

		case Chipoker::Card::queen:
			value_name = "queen";
			break;

		case Chipoker::Card::king:
			value_name = "king";
			break;

		default:
			return "unknown";
		}

		std::string result;
		result.append(color_name);
		result.append(" ");
		result.append(value_name);

		return result;
	}
} // namespace Chipoker

#endif // CHIPOKER_CARD_H