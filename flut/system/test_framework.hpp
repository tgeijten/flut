#pragma once

#include "platform.hpp"
#include "types.hpp"

#define FLUT_TEST( operation ) flut::test_framework::get_instance().test( #operation, operation )
#define FLUT_TEST_MSG( operation, message ) flut::test_framework::get_instance().test( #operation, operation, message )
#define FLUT_TEST_REPORT flut::test_framework::get_instance().report

namespace flut
{
	class FLUT_API test_framework
	{
	public:
		test_framework();
		bool test( const char* name, bool result, const string& message = "" );
		void reset();
		int report();

		int num_tests;
		int num_failed;
		int num_passed;

		static test_framework& get_instance();
		static test_framework test_;
	};

}
