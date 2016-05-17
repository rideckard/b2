//This file is part of Bertini 2.
//
//python/tracker_export.cpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//python/tracker_export.cpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with python/tracker_export.cpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
//
//  Daniel Brake
//  University of Notre Dame
//  Summer 2016
//
//
//  python/tracker_export.cpp:  source file for exposing trackers to python.

#include "tracker_export.hpp"

namespace bertini{
	namespace python{

		template<typename TrackerT>
		template<class PyClass>
		void TrackerVisitor<TrackerT>::visit(PyClass& cl) const
		{
			cl
			.def("setup", &TrackerT::Setup)
			.def("track_path", &TrackerT::TrackPath)
			.def("get_system",&TrackerT::GetSystem,return_internal_reference<>())
			.def("predictor",get_predictor_,"Query the current predictor method used by the tracker.")
			.def("predictor",set_predictor_,"Set the predictor method used by the tracker.")
			.def("set_stepsize", &TrackerT::SetStepSize)
//			.def("refine", return_Refine3_ptr<dbl>)
//			.def("refine", return_Refine3_ptr<mpfr>)
			.def("refine", return_Refine4_ptr<dbl, double>)
			.def("refine", return_Refine4_ptr<mpfr, mpfr_float>)
			.def("reinitialize_initial_step_size", &TrackerT::ReinitializeInitialStepSize)
			.def("num_total_steps_taken", &TrackerT::NumTotalStepsTaken)
			.def("tracking_tolerance", &TrackerT::TrackingTolerance)
			;
		}


		template<typename TrackerT>
		template<class PyClass>
		void AMPTrackerVisitor<TrackerT>::visit(PyClass& cl) const
		{
			cl
			.def("precision_setup", &TrackerT::PrecisionSetup)
			.def("precision_preservation", &TrackerT::PrecisionPreservation)
			.def("current_point", &TrackerT::CurrentPoint)
			.def("change_precision", &TrackerT::ChangePrecision)
			.def("current_precision", &TrackerT::CurrentPrecision)
			;
		}


		

		void ExportTrackers()
		{	
			ExportConfigSettings();

			ExportAMPTracker();
			ExportFixedTrackers();
		}

		void ExportAMPTracker()
		{
			class_<AMPTracker, std::shared_ptr<AMPTracker> >("AMPTracker", init<const System&>())
			.def(TrackerVisitor<AMPTracker>())
			;
		}

		void ExportFixedTrackers()
		{
			ExportFixedDoubleTracker();
			ExportFixedMultipleTracker();
		}

		void ExportFixedDoubleTracker()
		{

		}

		void ExportFixedMultipleTracker()
		{

		}
		
		
		
		void ExportConfigSettings()
		{
			using namespace bertini::tracking::config;
			
			enum_<Predictor>("Predictor")
			.value("Constant", Predictor::Constant)
			.value("Euler", Predictor::Euler)
			.value("Heun", Predictor::Heun)
			.value("RK4", Predictor::RK4)
			.value("HeunEuler", Predictor::HeunEuler)
			.value("RKNorsett34", Predictor::RKNorsett34)
			.value("RKF45", Predictor::RKF45)
			.value("RKCashKarp45", Predictor::RKCashKarp45)
			.value("RKDormandPrince56", Predictor::RKDormandPrince56)
			.value("RKVerner67", Predictor::RKVerner67)
			.export_values()
			;

			enum_<SuccessCode>("SuccessCode")
			.value("Success", SuccessCode::Success)
			.value("HigherPrecisionNecessary", SuccessCode::HigherPrecisionNecessary)
			.value("ReduceStepSize", SuccessCode::ReduceStepSize)
			.value("GoingToInfinity", SuccessCode::GoingToInfinity)
			.value("FailedToConverge", SuccessCode::FailedToConverge)
			.value("MatrixSolveFailure", SuccessCode::MatrixSolveFailure)
			.value("MatrixSolveFailureFirstPartOfPrediction", SuccessCode::MatrixSolveFailureFirstPartOfPrediction)
			.value("MaxNumStepsTaken", SuccessCode::MaxNumStepsTaken)
			.value("MaxPrecisionReached", SuccessCode::MaxPrecisionReached)
			.value("MinStepSizeReached", SuccessCode::MinStepSizeReached)
			.value("Failure", SuccessCode::Failure)
			.value("SingularStartPoint", SuccessCode::SingularStartPoint)
			.value("ExternallyTerminated", SuccessCode::ExternallyTerminated)
			.value("MinTrackTimeReached", SuccessCode::MinTrackTimeReached)
			.value("SecurityMaxNormReached", SuccessCode::SecurityMaxNormReached)
			.value("CycleNumTooHigh", SuccessCode::CycleNumTooHigh)
			.export_values()
			;
			
			
			class_<AdaptiveMultiplePrecisionConfig, std::shared_ptr<AdaptiveMultiplePrecisionConfig> >("AMPConfig", init<>())
			.def(init<System const&>())
			.def("set_amp_config_from", &AdaptiveMultiplePrecisionConfig::SetAMPConfigFrom)
			.def("set_phi_psi_from_bounds", &AdaptiveMultiplePrecisionConfig::SetPhiPsiFromBounds)
			.def("set_bounds_and_epsilon_from", &AdaptiveMultiplePrecisionConfig::SetBoundsAndEpsilonFrom)
			.def_readwrite("coefficient_bound", &AdaptiveMultiplePrecisionConfig::coefficient_bound)
			.def_readwrite("degree_bound", &AdaptiveMultiplePrecisionConfig::degree_bound)
			.def_readwrite("epsilon", &AdaptiveMultiplePrecisionConfig::epsilon)
			.def_readwrite("phi", &AdaptiveMultiplePrecisionConfig::Phi)
			.def_readwrite("psi", &AdaptiveMultiplePrecisionConfig::Psi)
			.def_readwrite("safety_digits_1", &AdaptiveMultiplePrecisionConfig::safety_digits_1)
			.def_readwrite("safety_digits_2", &AdaptiveMultiplePrecisionConfig::safety_digits_2)
			.def_readwrite("maximum_precision", &AdaptiveMultiplePrecisionConfig::maximum_precision)
			.def_readwrite("consecutive_successful_steps_before_precision_decrease", &AdaptiveMultiplePrecisionConfig::consecutive_successful_steps_before_precision_decrease)
			.def_readwrite("max_num_precision_decreases", &AdaptiveMultiplePrecisionConfig::max_num_precision_decreases)
			.def_readwrite("coefficient_bound", &AdaptiveMultiplePrecisionConfig::coefficient_bound)
			;
			
			def("amp_config_from", &AMPConfigFrom);
			
			
		}



}} // namespaces

