#pragma once

#include "system/platform.hpp"

namespace flut
{
	class FLUT_API interruptible
	{
	public:
		interruptible();
		virtual ~interruptible();

		virtual void interrupt() const;
		bool test_interrupt_flag() const;

	private:
		mutable bool interrupt_flag_;
	};
}
