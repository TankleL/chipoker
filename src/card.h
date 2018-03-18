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

	protected:
		static std::map<int, std::string>	m_code2name;
		static std::map<std::string, int>	m_name2code;
		static bool							m_mapinited;
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
		int color = m_card & 0xf0;
		return (Types)color;
	}

	inline Card::Types Card::get_value() const
	{
		int value = m_card & 0x0f;
		return (Types)value;
	}

	inline Card::Types Card::gen_card(Types color, Types value)
	{
		assert(color >= 0x10 && color <= 0x60);		

		return static_cast<Types>(color | value);
	}

	inline std::string Card::get_name() const
	{
		std::string result;

		if (m_card == 0x5f || m_card == 0x6f)
		{
			result = m_code2name[m_card];
		}
		else
		{
			std::string color_name;
			Types color = get_color();

			if (color >= diamond && color <= spade)
				color_name = m_code2name[color];

			std::string value_name;
			Types value = get_value();
			value_name = m_code2name[value];


			result.append(color_name);
			result.append(" ");
			result.append(value_name);
		}

		return result;
	}
} // namespace Chipoker

#endif // CHIPOKER_CARD_H