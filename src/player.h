/* ****************************************************************************
player.h
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

#ifndef CHIPOKER_PLAYER_H
#define CHIPOKER_PLAYER_H

#include "prerequisites.h"
#include "card.h"
#include "judger.h"

namespace Chipoker
{
	class Player
	{
	public:
		Player();
		virtual ~Player();

	public:
		void add_card(const Card& card);
		void arrange_card();

		std::string show_cards() const;

	public:
		bool try_single(std::vector<Card>& possibles) const;
		bool try_pair(std::vector<std::vector<Card>>& possibles) const;
		bool try_triple(std::vector<std::vector<Card>>& possibles) const;
		bool try_single_straight(std::vector<std::vector<Card>>& possibles) const;
		bool try_double_straight(std::vector<std::vector<Card>>& possibles) const;

	public:
		virtual void on_turn(std::vector<Card>& new_cards);
		virtual bool on_turn(std::vector<Card>& new_cards, const std::vector<Card>& old_cards);

	protected:
		std::vector<Card>	m_cards;
	}; // class Player


	inline Player::Player()
	{}

	inline Player::~Player()
	{}

	inline void Player::add_card(const Card& card)
	{
		m_cards.push_back(card);
	}

	inline std::string Player::show_cards() const
	{
		std::string result;
		for (auto& card : m_cards)
		{
			result.append("[");
			result.append(card.get_name());
			result.append("]");
		}
		return result;
	}

	inline void Player::arrange_card()
	{
		std::sort(m_cards.begin(), m_cards.end());
	}

	inline bool Player::try_single(std::vector<Card>& possibles) const
	{
		if (m_cards.size() <= 0)
			return false;

		possibles = m_cards;
		return true;
	}

	inline bool Player::try_pair(std::vector<std::vector<Card>>& possibles) const
	{
		possibles.clear();
		if (m_cards.size() <= 1)
			return false;

		{// figure out the possible combos
			size_t i = 1;
			while (i < m_cards.size())
			{
				std::vector<Card>	pair;
				pair.push_back(m_cards[i - 1]);
				pair.push_back(m_cards[i]);

				if (Judger::pair(pair))
				{
					possibles.push_back(std::move(pair));
					i += 2;
					continue;
				}
				++i;
			}
		}

		if (possibles.size() > 0)
			return true;
		return false;
	}

	inline bool Player::try_triple(std::vector<std::vector<Card>>& possibles) const
	{
		possibles.clear();
		if (m_cards.size() <= 2)
			return false;

		{// figure out the possible combos
			size_t i = 2;
			while (i < m_cards.size())
			{
				std::vector<Card>	triple;
				triple.push_back(m_cards[i - 2]);
				triple.push_back(m_cards[i - 1]);
				triple.push_back(m_cards[i]);

				if (Judger::triple(triple))
				{
					possibles.push_back(std::move(triple));
					i += 3;
					continue;
				}
				++i;
			}
		}

		if (possibles.size() > 0)
			return true;
		return false;
	}

	inline bool Player::try_single_straight(std::vector<std::vector<Card>>& possibles) const
	{
		possibles.clear();
		if (m_cards.size() <= 4)
			return false;

		{// figure out the longest straghts
			std::vector<Card>	straight;
			size_t i = 1;
			while (i < m_cards.size())
			{
				if (m_cards[i].get_value() == m_cards[i - 1].get_value() + 1 &&
					m_cards[i].get_value() != Card::c2 &&
					m_cards[i-1].get_value() != Card::c2)
				{
					straight.push_back(m_cards[i]);
					++i;
					continue;
				}
				else if (m_cards[i].get_value() == m_cards[i - 1].get_value() &&
						m_cards[i].get_value() != Card::c2 &&
						m_cards[i - 1].get_value() != Card::c2)
				{
					++i;
					continue;
				}
				else
				{
					if (straight.size() >= 5)
					{
						possibles.push_back(straight);
						straight.clear();
					}
					else
						straight.clear();

					++i;
					continue;
				}
			}
			if (straight.size() >= 5)
				possibles.push_back(straight);
		}

		if (possibles.size() > 0)
		{
			const size_t boundary = possibles.size();
			for (size_t i = 0; i < boundary; ++i)
			{
				const size_t cases_count = possibles[i].size() - 5;
				for (size_t j = 1; j <= cases_count; ++j)
				{
					std::vector<Card>	case_rm_front_n(possibles[i]);
					std::vector<Card>	case_rm_back_n(possibles[i]);

					for (size_t k = 0; k < j; ++k)
					{
						case_rm_front_n.erase(case_rm_front_n.begin());
						case_rm_back_n.pop_back();
					}

					possibles.push_back(case_rm_front_n);
					possibles.push_back(case_rm_back_n);
				}
			}
			
			return true;
		}
		return false;
	}

	inline bool Player::try_double_straight(std::vector<std::vector<Card>>& possibles) const
	{
		possibles.clear();
		if (m_cards.size() < 6)
			return false;

		{// figure out the longest straghts
			std::vector<Card>	straight;
			size_t i = 1;
			while (i < m_cards.size())
			{
				if (m_cards[i].get_value() == m_cards[i - 1].get_value() &&
					m_cards[i].get_value() != Card::c2 &&
					m_cards[i - 1].get_value() != Card::c2)
				{
					bool existing = false;
					for (auto& card : straight)
					{
						if (card.get_value() == m_cards[i].get_value())
						{
							existing = true;
							break;
						}
					}
					if (existing)
					{
						++i;
						continue;
					}

					if (straight.size() == 0)
					{
						straight.push_back(m_cards[i - 1]);
						straight.push_back(m_cards[i]);
						i += 2;
						continue;
					}
					else
					{
						if (straight.back().get_value() == m_cards[i].get_value() - 1)
						{
							straight.push_back(m_cards[i - 1]);
							straight.push_back(m_cards[i]);
							i += 2;
							continue;
						}
						else if (straight.size() >= 6)
						{
							possibles.push_back(straight);
							straight.clear();

							++i;
							continue;
						}
						else
						{
							straight.clear();
							++i;
							continue;
						}
					}
				}
				else
				{
					++i;
					continue;
				}
			}
			if (straight.size() >= 6)
			{
				possibles.push_back(straight);
				straight.clear();
			}
		}

		if (possibles.size() > 0)
		{
			const size_t boundary = possibles.size();
			for (size_t i = 0; i < boundary; ++i)
			{
				const size_t cases_count = possibles[i].size() - 6;
				for (size_t j = 2; j <= cases_count; j += 2)
				{
					std::vector<Card>	case_rm_front_n(possibles[i]);
					std::vector<Card>	case_rm_back_n(possibles[i]);

					for (size_t k = 0; k < j; ++k)
					{
						case_rm_front_n.erase(case_rm_front_n.begin());
						case_rm_back_n.pop_back();
					}

					possibles.push_back(case_rm_front_n);
					possibles.push_back(case_rm_back_n);
				}
			}

			return true;
		}
		return false;
	}

	inline void Player::on_turn(std::vector<Card>& new_cards)
	{
	}

	inline bool Player::on_turn(std::vector<Card>& new_cards, const std::vector<Card>& old_cards)
	{
		return false;
	}
} // namespace Chipoker

#endif // CHIPOKER_PLAYER_H