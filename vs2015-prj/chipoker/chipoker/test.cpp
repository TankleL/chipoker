/* ****************************************************************************
entrance.cpp
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

#include "../../../src/prerequisites.h"
#include "../../../src/card.h"
#include "../../../src/player.h"
#include "../../../src/tree.h"

using namespace std;
using namespace Chipoker;

// ----------------------------------------------------------------------------
// forward declaration
// ----------------------------------------------------------------------------

void deal_random(const vector<Player*>& players, vector<Card>& left_cards);

// ----------------------------------------------------------------------------
// implementations
// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Player players[3];
	vector<Card>	left_cards;

	{// deal cards
		vector<Player*> player_list;
		player_list.push_back(&players[0]);
		player_list.push_back(&players[1]);
		player_list.push_back(&players[2]);
		deal_random(player_list, left_cards);
	}

	{// print cards
		int i = 0;
		for (Player& player : players)
		{
			++i;
			player.arrange_card();
			cout << "Player " << i << ": -----------------------" << endl;
			cout << player.show_cards().c_str() << endl;
		}
	}

	Tree<std::string, int> treeRoot("treeRoot", 0);

	treeRoot.add_child(std::make_shared<Tree<std::string, int>>("treeA", 1));
	treeRoot.add_child(std::make_shared<Tree<std::string, int>>("treeB", 2));

	Tree<std::string, int>::ChildPtr child = treeRoot.get_child("treeA");
	return 0;
}

void deal_random(const vector<Player*>& players, vector<Card>& left_cards)
{
	assert(players.size() == 3);

	Card::Types colors[4] = { Card::diamond, Card::club, Card::heart, Card::spade };
	vector<Card> all_cards;

	// initialize the cards
	{
		for (auto& color : colors)
		{
			for (int i = 0x01; i <= 0x0D; ++i)
			{
				Card::Types value = static_cast<Card::Types>(i);
				all_cards.push_back(Card::gen_card(color, value));
			}
		}

		all_cards.push_back(Card::black_joker);
		all_cards.push_back(Card::red_joker);
	}

	// deal cards
	srand((unsigned int)time(nullptr));
	int count = 54;
	while (count > 3)
	{
		int pick_idx = rand() % count;
		vector<Card>::iterator iter = all_cards.begin() + pick_idx;
		players[count % 3]->add_card(*iter);
		all_cards.erase(iter);
		--count;
	}

	left_cards.push_back(all_cards.back());
	all_cards.pop_back();
	left_cards.push_back(all_cards.back());
	all_cards.pop_back();
	left_cards.push_back(all_cards.back());
	all_cards.pop_back();
}
