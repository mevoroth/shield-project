#ifndef _CLONEABLE_H_
#define _CLONEABLE_H_

namespace shield {
namespace patterns {
	template<class Class>
	class Cloneable
	{
	public:
		virtual ~Cloneable() {};
		virtual Class clone() const = 0;
	};
};
};

#endif
