/* ****************************************************************************
tree.h
-------------------------------------------------------------------------------

Copyright (c) 2018, Tain L.
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

#ifndef CHIPOKER_TREE_H
#define CHIPOKER_TREE_H

#include "prerequisites.h"

namespace Chipoker
{
	template<typename _TKey, typename _TValue>
	class Tree
	{
	public:
		typedef std::shared_ptr<Tree>	ChildPtr;
	public:
		Tree()
			: m_parent(nullptr)
		{}
		Tree(const _TKey& name, const _TValue& value)
			: m_parent(nullptr)
			, m_name(name)
			, m_value(value)
		{}

		virtual	~Tree()
		{}

	public:
		void set_value(const _TValue& value)
		{
			m_value = value;
		}

		_TValue get_value() const
		{
			return m_value;
		}

		void add_child(const std::shared_ptr<Tree>& child)
		{
			m_children[child->m_name] = child;
			child->m_parent = this;
		}

		std::shared_ptr<Tree> get_child(const _TKey& name) const
		{
			std::shared_ptr<Tree> res;
			std::map<_TKey, std::shared_ptr<Tree>>::const_iterator citer =
				m_children.find(name);
			if (citer != m_children.end())
			{
				res = citer->second;
			}
			return std::move(res);
		}

	protected:
		_TKey									m_name;
		_TValue									m_value;
		std::map<_TKey, std::shared_ptr<Tree>>	m_children;
		Tree*									m_parent;
	};
}

#endif // !CHIPOKER_TREE_H
