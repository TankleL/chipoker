/* ****************************************************************************
card.cpp
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
#include "card.h"

using namespace Chipoker;

std::map<int, std::string> Card::m_code2name
= { {Card::ace, "ace"},
	{ Card::c2, "2" },
	{ Card::c3, "3" },
	{ Card::c4, "4" },
	{ Card::c5, "5" },
	{ Card::c6, "6" },
	{ Card::c7, "7" },
	{ Card::c8, "8" },
	{ Card::c9, "9" },
	{ Card::c10, "10" },
	{ Card::jack, "jack" },
	{ Card::queen, "queen" },
	{ Card::king, "king" },
	{ Card::black_joker, "black_joker" },
	{ Card::red_joker, "red_joker" },
	{ Card::diamond, "diamond" },
	{ Card::club, "club" },
	{ Card::heart, "heart" },
	{ Card::spade, "spade" } };

std::map<std::string, int> Card::m_name2code
= { {"ace", Card::ace },
	{ "2", Card::c2 },
	{ "3", Card::c3 },
	{ "4", Card::c4 },
	{ "5", Card::c5 },
	{ "6", Card::c6 },
	{ "7", Card::c7 },
	{ "8", Card::c8 },
	{ "9", Card::c9 },
	{ "10", Card::c10 },
	{ "jack", Card::jack },
	{ "queen", Card::queen },
	{ "king", Card::king },
	{ "black_joker", Card::black_joker },
	{ "red_joker", Card::red_joker },
	{ "diamond", Card::diamond },
	{ "club", Card::club },
	{ "heart", Card::heart },
	{ "spade", Card::spade } };


