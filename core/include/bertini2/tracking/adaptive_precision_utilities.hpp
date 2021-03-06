//This file is part of Bertini 2.
//
//fixed_precision_utilities.hpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//fixed_precision_utilities.hpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with fixed_precision_utilities.hpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2015, 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
// daniel brake, university of notre dame
// Tim Hodges, Colorado State University


#pragma once

#include "bertini2/tracking/tracking_config.hpp"


namespace bertini{ namespace tracking { namespace endgame {
namespace adaptive{

inline
void SetPrecision(SampCont<mpfr> & samples, unsigned prec)
{
	for (auto& s : samples)
		for (unsigned ii=0; ii<s.size(); ii++)
			s(ii).precision(prec);
}

inline
void SetPrecision(TimeCont<mpfr> & times, unsigned prec)
{
	for (auto& t : times)
		t.precision(prec);
}

inline
unsigned MaxPrecision(SampCont<mpfr> const& samples)
{
	unsigned max_precision = 0;
	for (const auto& s : samples)
		if(Precision(s(0)) > max_precision)
			max_precision = Precision(s(0));
	return max_precision;
}

inline
unsigned MaxPrecision(TimeCont<mpfr> const& times)
{
	unsigned max_precision = 0;
	for (const auto& t : times)
		if(Precision(t) > max_precision)
			max_precision = Precision(t);
	return max_precision;
}


/**
\brief Does not a thing, because cannot.

Cannot change precision of fixed precision hardware doubles.

\return The precision, which is now uniform.
*/
inline
unsigned EnsureAtUniformPrecision(TimeCont<dbl> & times, SampCont<dbl> & derivatives)
{
	return DoublePrecision();
}


/**
\brief Changes precision of mpfr to highest needed precision for the samples.

\return The precision, which is now uniform.
*/
inline
unsigned EnsureAtUniformPrecision(TimeCont<mpfr> & times, SampCont<mpfr> & samples)
{
	using std::max;
	unsigned max_precision = max(
	                             mpfr_float::default_precision(),
	                             MaxPrecision(samples)
	                             ); 

	if (max_precision != mpfr_float::default_precision())
		std::cout << "EG changing default precision from " << mpfr_float::default_precision() << " to " << max_precision << std::endl;
	//BOOST_LOG_TRIVIAL(severity_level::trace)
	mpfr_float::default_precision(max_precision);

	SetPrecision(times, max_precision);
	SetPrecision(samples, max_precision);

	return max_precision;
}


//changes precision of mpfr to highest needed precision for the samples.
inline
unsigned EnsureAtUniformPrecision(TimeCont<mpfr> & times, SampCont<mpfr> & samples, SampCont<mpfr> & derivatives)
{
	unsigned max_precision = max(
	                             mpfr_float::default_precision(),
	                             MaxPrecision(samples),
	                             MaxPrecision(derivatives)
	                             ); 

	if (max_precision != mpfr_float::default_precision())
		BOOST_LOG_TRIVIAL(severity_level::trace) << "EG changing default precision from " << mpfr_float::default_precision() << " to " << max_precision << std::endl;
	
	mpfr_float::default_precision(max_precision);

	SetPrecision(times, max_precision);
	SetPrecision(samples, max_precision);
	SetPrecision(derivatives, max_precision);

	return max_precision;
}


}}}} // re: namespaces
