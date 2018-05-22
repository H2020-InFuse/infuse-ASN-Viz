#include <boost/test/unit_test.hpp>
#include <ASN_Viz/Dummy.hpp>

using namespace ASN_Viz;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    ASN_Viz::DummyClass dummy;
    dummy.welcome();
}
