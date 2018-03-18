/* ****************************************************************************
strategist.h
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

#ifndef CHIPOKER_STRATEGIST_H
#define CHIPOKER_STRATEGIST_H

#include "prerequisites.h"
#include "card.h"
#include "judger.h"

namespace Chipoker
{
	class Strategist
	{
	public:
		struct SolveNode
		{
			SolveNode()
				: weight(0e0)
			{}

			double				weight;
			std::vector<Card>	cards;
		};

	public:
		Strategist();

	public:
		void solve(const std::vector<Card>& cards);

	protected:
		typedef std::function	<std::vector<std::vector<Card>>(const std::vector<Card>&)>	try_type_fp;
		std::vector<try_type_fp>	type_tryers;

		static std::vector<std::vector<Card>> try_single(const std::vector<Card>& cards);
		static std::vector<std::vector<Card>> try_pair(const std::vector<Card>& cards);
	};
}

#endif // CHIPOKER_STRATEGIST_H