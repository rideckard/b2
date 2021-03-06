//This file is part of Bertini 2.
//
//amp_powerseries_test.cpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//amp_powerseries_test.cpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with amp_powerseries_test.cpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2015, 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
// daniel brake, university of notre dame
// Tim Hodges, Colorado State University


#include <iostream>
#include <boost/test/unit_test.hpp>

#include "bertini2/start_system.hpp"
#include "bertini2/num_traits.hpp"

#include "bertini2/tracking/amp_powerseries_endgame.hpp"





BOOST_AUTO_TEST_SUITE(amp_powerseries_endgame_generic_tests_ambient_precision_16)

using namespace bertini::tracking;
using namespace bertini::tracking::endgame;

using TrackerType = AMPTracker; // select a tracker type
using TestedEGType = EndgameSelector<TrackerType>::PSEG;
auto TestedPredictor = config::Predictor::HeunEuler;
unsigned ambient_precision = 16;
#include "test/endgames/generic_pseg_test.hpp"

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE(amp_powerseries_endgame_generic_tests_ambient_precision_30)

using namespace bertini::tracking;
using namespace bertini::tracking::endgame;

using TrackerType = AMPTracker; // select a tracker type
using TestedEGType = EndgameSelector<TrackerType>::PSEG;
auto TestedPredictor = config::Predictor::HeunEuler;
unsigned ambient_precision = 30;
#include "test/endgames/generic_pseg_test.hpp"

BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(amp_powerseries_endgame_generic_tests_ambient_precision_50)

using namespace bertini::tracking;
using namespace bertini::tracking::endgame;

using TrackerType = AMPTracker; // select a tracker type
using TestedEGType = EndgameSelector<TrackerType>::PSEG;
auto TestedPredictor = config::Predictor::HeunEuler;
unsigned ambient_precision = 50;
#include "test/endgames/generic_pseg_test.hpp"

BOOST_AUTO_TEST_SUITE_END()






BOOST_AUTO_TEST_SUITE(amp_powerseries_endgame_AMPspecific_tests)

using namespace bertini::tracking;
using namespace bertini::tracking::endgame;

using TrackerType = AMPTracker; // select a tracker type
using TestedEGType = EndgameSelector<TrackerType>::PSEG;

using namespace bertini;
BOOST_AUTO_TEST_CASE(ensure_uniform_precision_16_30_40)
{
	TimeCont<mpfr> times;
	SampCont<mpfr> samples;

	mpfr_float::default_precision(16);
	times.emplace_back(RandomUnit<mpfr>());

	mpfr_float::default_precision(30);
	times.emplace_back(RandomUnit<mpfr>());

	mpfr_float::default_precision(40);
	times.emplace_back(RandomUnit<mpfr>());



	mpfr_float::default_precision(16);
	samples.emplace_back(RandomOfUnits<mpfr>(4));

	mpfr_float::default_precision(30);
	samples.emplace_back(RandomOfUnits<mpfr>(4));

	mpfr_float::default_precision(40);
	samples.emplace_back(RandomOfUnits<mpfr>(4));


	auto max_precision = TestedEGType::EnsureAtUniformPrecision(times, samples);

	BOOST_CHECK_EQUAL(max_precision,40);

	for (const auto& t : times)
		BOOST_CHECK_EQUAL(Precision(t),40);

	for (const auto& s : samples)
		BOOST_CHECK_EQUAL(Precision(s(0)),40);
}



BOOST_AUTO_TEST_CASE(ensure_uniform_precision_all_uniform_to_start)
{
	TimeCont<mpfr> times;
	SampCont<mpfr> samples;

	mpfr_float::default_precision(30);
	times.emplace_back(RandomUnit<mpfr>());

	mpfr_float::default_precision(30);
	times.emplace_back(RandomUnit<mpfr>());

	mpfr_float::default_precision(30);
	times.emplace_back(RandomUnit<mpfr>());



	mpfr_float::default_precision(30);
	samples.emplace_back(RandomOfUnits<mpfr>(4));

	mpfr_float::default_precision(30);
	samples.emplace_back(RandomOfUnits<mpfr>(4));

	mpfr_float::default_precision(30);
	samples.emplace_back(RandomOfUnits<mpfr>(4));


	auto max_precision = TestedEGType::EnsureAtUniformPrecision(times, samples);

	BOOST_CHECK_EQUAL(max_precision,30);

	for (const auto& t : times)
		BOOST_CHECK_EQUAL(Precision(t),30);

	for (const auto& s : samples)
		BOOST_CHECK_EQUAL(Precision(s(0)),30);
}
BOOST_AUTO_TEST_SUITE_END()
