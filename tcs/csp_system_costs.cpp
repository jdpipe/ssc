/*******************************************************************************************************
*  Copyright 2017 Alliance for Sustainable Energy, LLC
*
*  NOTICE: This software was developed at least in part by Alliance for Sustainable Energy, LLC
*  (�Alliance�) under Contract No. DE-AC36-08GO28308 with the U.S. Department of Energy and the U.S.
*  The Government retains for itself and others acting on its behalf a nonexclusive, paid-up,
*  irrevocable worldwide license in the software to reproduce, prepare derivative works, distribute
*  copies to the public, perform publicly and display publicly, and to permit others to do so.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. The entire corresponding source code of any redistribution, with or without modification, by a
*  research entity, including but not limited to any contracting manager/operator of a United States
*  National Laboratory, any institution of higher learning, and any non-profit organization, must be
*  made publicly available under this license for as long as the redistribution is made available by
*  the research entity.
*
*  4. Redistribution of this software, without modification, must refer to the software by the same
*  designation. Redistribution of a modified version of this software (i) may not refer to the modified
*  version by the same designation, or by any confusingly similar designation, and (ii) must refer to
*  the underlying software originally provided by Alliance as �System Advisor Model� or �SAM�. Except
*  to comply with the foregoing, the terms �System Advisor Model�, �SAM�, or any confusingly similar
*  designation may not be used to refer to any modified version of this software or any modified
*  version of the underlying software originally provided by Alliance without the prior written consent
*  of Alliance.
*
*  5. The name of the copyright holder, contributors, the United States Government, the United States
*  Department of Energy, or any of their employees may not be used to endorse or promote products
*  derived from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
*  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER,
*  CONTRIBUTORS, UNITED STATES GOVERNMENT OR UNITED STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR
*  EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
*  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************************************/

#include "csp_system_costs.h"
#include "csp_solver_util.h"

#include <math.h>

void C_mspt_system_costs::check_parameters_are_set()
{
	if( ms_par.A_sf_refl != ms_par.A_sf_refl ||
		ms_par.site_improv_spec_cost != ms_par.site_improv_spec_cost ||
		ms_par.heliostat_spec_cost != ms_par.heliostat_spec_cost ||
		ms_par.heliostat_fixed_cost != ms_par.heliostat_fixed_cost ||
		
		ms_par.h_tower != ms_par.h_tower ||
		ms_par.h_rec != ms_par.h_rec ||
		ms_par.h_helio != ms_par.h_helio ||
		ms_par.tower_fixed_cost != ms_par.tower_fixed_cost ||
		ms_par.tower_cost_scaling_exp != ms_par.tower_cost_scaling_exp ||
		
		ms_par.A_rec != ms_par.A_rec ||
		ms_par.rec_ref_cost != ms_par.rec_ref_cost ||
		ms_par.A_rec_ref != ms_par.A_rec_ref ||
		ms_par.rec_cost_scaling_exp != ms_par.rec_cost_scaling_exp ||
		
		ms_par.Q_storage != ms_par.Q_storage ||
		ms_par.tes_spec_cost != ms_par.tes_spec_cost ||
		
		ms_par.W_dot_design != ms_par.W_dot_design ||
		ms_par.power_cycle_spec_cost != ms_par.power_cycle_spec_cost ||
		
		ms_par.bop_spec_cost != ms_par.bop_spec_cost ||
		
		ms_par.fossil_backup_spec_cost != ms_par.fossil_backup_spec_cost ||
		
		ms_par.contingency_rate != ms_par.contingency_rate ||
		
		ms_par.total_land_area != ms_par.total_land_area ||
		ms_par.plant_net_capacity != ms_par.plant_net_capacity ||
		ms_par.EPC_land_spec_cost != ms_par.EPC_land_spec_cost ||
		ms_par.EPC_land_perc_direct_cost != ms_par.EPC_land_perc_direct_cost ||
		ms_par.EPC_land_per_power_cost != ms_par.EPC_land_per_power_cost ||
		ms_par.EPC_land_fixed_cost != ms_par.EPC_land_fixed_cost ||
		ms_par.total_land_spec_cost != ms_par.total_land_spec_cost ||
		ms_par.total_land_perc_direct_cost != ms_par.total_land_perc_direct_cost ||
		ms_par.total_land_per_power_cost != ms_par.total_land_per_power_cost ||
		ms_par.total_land_fixed_cost != ms_par.total_land_fixed_cost ||
		ms_par.sales_tax_basis != ms_par.sales_tax_basis ||
		ms_par.sales_tax_rate != ms_par.sales_tax_rate )
	{
		std::string msg = "C_mspt_system_costs initialization failed because not all required parameters were defined"
		"before calculate_costs() was called";
		C_csp_exception(msg,0);
	}

	return;
}


void C_mspt_system_costs::calculate_costs()
{
	check_parameters_are_set();

	ms_out.site_improvement_cost = 
		N_mspt::site_improvement_cost(ms_par.A_sf_refl, ms_par.site_improv_spec_cost);

	ms_out.heliostat_cost = 
		N_mspt::heliostat_cost(ms_par.A_sf_refl, ms_par.heliostat_spec_cost, ms_par.heliostat_fixed_cost);

	ms_out.tower_cost = 
		N_mspt::tower_cost(ms_par.h_tower, ms_par.h_rec, ms_par.h_helio, ms_par.tower_fixed_cost, ms_par.tower_cost_scaling_exp);

	ms_out.receiver_cost = 
		N_mspt::receiver_cost(ms_par.A_rec, ms_par.rec_ref_cost, ms_par.A_rec_ref, ms_par.rec_cost_scaling_exp);

	ms_out.tes_cost = 
		N_mspt::tes_cost(ms_par.Q_storage, ms_par.tes_spec_cost);

	ms_out.power_cycle_cost = 
		N_mspt::power_cycle_cost(ms_par.W_dot_design, ms_par.power_cycle_spec_cost);

	ms_out.bop_cost = 
		N_mspt::bop_cost(ms_par.W_dot_design, ms_par.bop_spec_cost);

	ms_out.fossil_backup_cost = 
		N_mspt::fossil_backup_cost(ms_par.W_dot_design, ms_par.fossil_backup_spec_cost);

	ms_out.direct_capital_precontingency_cost = 
		N_mspt::direct_capital_precontingency_cost(
			ms_out.site_improvement_cost,
			ms_out.heliostat_cost,
			ms_out.tower_cost,
			ms_out.receiver_cost,
			ms_out.tes_cost,
			ms_out.power_cycle_cost,
			ms_out.bop_cost,
			ms_out.fossil_backup_cost);

	ms_out.contingency_cost = 
		N_mspt::contingency_cost(ms_par.contingency_rate, ms_out.direct_capital_precontingency_cost);

	ms_out.total_direct_cost = 
		N_mspt::total_direct_cost(ms_out.direct_capital_precontingency_cost, ms_out.contingency_cost);

	ms_out.total_land_cost = 
		N_mspt::total_land_cost(ms_par.total_land_area, ms_out.total_direct_cost, ms_par.plant_net_capacity,
			ms_par.total_land_spec_cost, ms_par.total_land_perc_direct_cost, ms_par.total_land_per_power_cost, ms_par.total_land_fixed_cost);

	ms_out.epc_and_owner_cost = 
		N_mspt::epc_and_owner_cost(ms_par.total_land_area, ms_out.total_direct_cost, ms_par.plant_net_capacity,
			ms_par.EPC_land_spec_cost, ms_par.EPC_land_perc_direct_cost, ms_par.EPC_land_per_power_cost, ms_par.EPC_land_fixed_cost);

	ms_out.sales_tax_cost = 
		N_mspt::sales_tax_cost(ms_out.total_direct_cost, ms_par.sales_tax_basis, ms_par.sales_tax_rate);

	ms_out.total_indirect_cost = 
		N_mspt::total_indirect_cost(ms_out.total_land_cost, ms_out.epc_and_owner_cost, ms_out.sales_tax_cost);

	ms_out.total_installed_cost = 
		N_mspt::total_installed_cost(ms_out.total_direct_cost, ms_out.total_indirect_cost);

	ms_out.estimated_installed_cost_per_cap = 
		N_mspt::estimated_installed_cost_per_cap(ms_out.total_installed_cost, ms_par.plant_net_capacity);

	return;
}

double N_mspt::site_improvement_cost(double A_refl /*m^2*/, double site_improv_spec_cost /*$/m^2_reflect*/)
{
	return A_refl*site_improv_spec_cost;		//[$]
}

double N_mspt::heliostat_cost(double A_refl /*m^2*/, double heliostat_spec_cost /*$/m^2*/, double heliostate_fixed_cost /*$*/)
{
	return A_refl*heliostat_spec_cost + heliostate_fixed_cost;	//[$]
}

double N_mspt::tower_cost(double h_tower /*m*/, double h_rec /*m*/, double h_helio /*m*/, double tower_fixed_cost /*$*/, double tower_cost_scaling_exp /*-*/)
{
	return tower_fixed_cost * exp(tower_cost_scaling_exp * (h_tower - h_rec / 2.0 + h_helio / 2.0));	//[$]
}

double N_mspt::receiver_cost(double A_rec /*m^2*/, double rec_ref_cost /*$*/, double rec_ref_area /*m^2*/, double rec_cost_scaling_exp /*-*/)
{
	return rec_ref_cost*pow(A_rec/rec_ref_area, rec_cost_scaling_exp);	//[$]
}

double N_mspt::tes_cost(double Q_storage /*MWt-hr*/, double tes_spec_cost /*$/kWt-hr*/)
{
	return Q_storage*1.E3*tes_spec_cost;		//[$]
}

double N_mspt::power_cycle_cost(double W_dot_design /*MWe*/, double power_cycle_spec_cost /*$/kWe*/)
{
	return W_dot_design*1.E3*power_cycle_spec_cost;		//[$]
}

double N_mspt::bop_cost(double W_dot_design /*MWe*/, double bop_spec_cost /*$/kWe*/)
{
	return W_dot_design*1.E3*bop_spec_cost;				//[$]
}

double N_mspt::fossil_backup_cost(double W_dot_design /*MWe*/, double fossil_backup_spec_cost /*$/kWe*/)
{
	return W_dot_design*1.E3*fossil_backup_spec_cost;	//[$]
}

double N_mspt::direct_capital_precontingency_cost(double site_improvement_cost /*$*/,
	double heliostat_cost /*$*/,
	double tower_cost /*$*/,
	double receiver_cost /*$*/,
	double tes_cost /*$*/,
	double power_cycle_cost /*$*/,
	double bop_cost /*$*/,
	double fossil_backup_cost /*$*/)
{
	return site_improvement_cost +
		heliostat_cost +
		tower_cost +
		receiver_cost +
		tes_cost +
		power_cycle_cost +
		bop_cost +
		fossil_backup_cost;	//[$]
}

double N_mspt::contingency_cost(double contingency_rate /*%*/, double direct_capital_precontingency_cost /*$*/)
{
	return contingency_rate/100.0*direct_capital_precontingency_cost;	//[$]
}

double N_mspt::total_direct_cost(double direct_capital_precontingency_cost /*$*/, double contingency_cost /*$*/)
{
	return direct_capital_precontingency_cost + contingency_cost;		//[$]
}

double N_mspt::total_land_cost(double total_land_area /*acres*/, double total_direct_cost /*$*/, double plant_net_capacity /*MWe*/,
	double land_spec_cost /*$/acre*/, double land_perc_direct_cost /*%*/, double land_spec_per_power_cost /*$/We*/, double land_fixed_cost /*$*/)
{
	return total_land_area*land_spec_cost +
		total_direct_cost*land_perc_direct_cost/100.0 +
		plant_net_capacity*1.E6*land_spec_per_power_cost +
		land_fixed_cost;	//[$]
}

double N_mspt::epc_and_owner_cost(double total_land_area /*acres*/, double total_direct_cost /*$*/, double plant_net_capacity /*MWe*/,
	double land_spec_cost /*$/acre*/, double land_perc_direct_cost /*%*/, double land_spec_per_power_cost /*$/We*/, double land_fixed_cost /*$*/)
{
	return total_land_area*land_spec_cost +
		total_direct_cost*land_perc_direct_cost / 100.0 +
		plant_net_capacity*1.E6*land_spec_per_power_cost +
		land_fixed_cost;	//[$]
}

double N_mspt::sales_tax_cost(double total_direct_cost /*$*/, double sales_tax_basis /*% of tot. direct cost*/, double sales_tax_rate /*%*/)
{
	return total_direct_cost*(sales_tax_basis/100.0)*(sales_tax_rate/100.0);
}

double N_mspt::total_indirect_cost(double total_land_cost /*$*/, double epc_and_owner_cost /*$*/, double sales_tax_cost /*$*/)
{
	return total_land_cost + epc_and_owner_cost + sales_tax_cost;	//[$]
}

double N_mspt::total_installed_cost(double total_direct_cost /*$*/, double total_indirect_cost /*$*/)
{
	return total_direct_cost + total_indirect_cost;		//[$]
}

double N_mspt::estimated_installed_cost_per_cap(double total_installed_cost /*$*/, double plant_net_capacity /*$*/)
{
	return total_installed_cost/(plant_net_capacity*1.E3);
}

void N_financial_parameters::construction_financing_total_cost(double total_installed_cost /*$*/,
	double const_per_interest_rate1 /*%*/, double const_per_interest_rate2 /*%*/, double const_per_interest_rate3 /*%*/, double const_per_interest_rate4 /*%*/, double const_per_interest_rate5 /*%*/,
	double const_per_months1 /*-*/, double const_per_months2 /*-*/, double const_per_months3 /*-*/, double const_per_months4 /*-*/, double const_per_months5 /*-*/,
	double const_per_percent1 /*%*/, double const_per_percent2 /*%*/, double const_per_percent3 /*%*/, double const_per_percent4 /*%*/, double const_per_percent5 /*%*/,
	double const_per_upfront_rate1 /*%*/, double const_per_upfront_rate2 /*%*/, double const_per_upfront_rate3 /*%*/, double const_per_upfront_rate4 /*%*/, double const_per_upfront_rate5 /*%*/,
	double & const_per_principal1 /*$*/, double & const_per_principal2 /*$*/, double & const_per_principal3 /*$*/, double & const_per_principal4 /*$*/, double & const_per_principal5 /*$*/,
	double & const_per_interest1 /*$*/, double & const_per_interest2 /*$*/, double & const_per_interest3 /*$*/, double & const_per_interest4 /*$*/, double & const_per_interest5 /*$*/,
	double & const_per_total1 /*$*/, double & const_per_total2 /*$*/, double & const_per_total3 /*$*/, double & const_per_total4 /*$*/, double & const_per_total5 /*$*/,
	double & const_per_percent_total /*%*/, double & const_per_principal_total /*$*/, double & const_per_interest_total /*$*/, double & construction_financing_cost /*$*/)
{
	// Loan 1
	const_per_principal1 = const_per_percent1*total_installed_cost/100.0;
	construction_financing_loan_cost(const_per_principal1, const_per_interest_rate1, const_per_months1, const_per_upfront_rate1, 
		const_per_interest1, const_per_total1);

	const_per_principal2 = const_per_percent2*total_installed_cost/100.0;
	construction_financing_loan_cost(const_per_principal2, const_per_interest_rate2, const_per_months2, const_per_upfront_rate2,
		const_per_interest2, const_per_total2);

	const_per_principal3 = const_per_percent3*total_installed_cost/100.0;
	construction_financing_loan_cost(const_per_principal3, const_per_interest_rate3, const_per_months3, const_per_upfront_rate3,
		const_per_interest3, const_per_total3);

	const_per_principal4 = const_per_percent4*total_installed_cost/100.0;
	construction_financing_loan_cost(const_per_principal4, const_per_interest_rate4, const_per_months4, const_per_upfront_rate4,
		const_per_interest4, const_per_total4);

	const_per_principal5 = const_per_percent5*total_installed_cost/100.0;
	construction_financing_loan_cost(const_per_principal5, const_per_interest_rate5, const_per_months5, const_per_upfront_rate5,
		const_per_interest5, const_per_total5);

	const_per_percent_total = const_per_percent1 + const_per_percent2 + const_per_percent3 + const_per_percent4 + const_per_percent5;
	const_per_principal_total = const_per_principal1 + const_per_principal2 + const_per_principal3 + const_per_principal4 + const_per_principal5;
	const_per_interest_total = const_per_interest1 + const_per_interest2 + const_per_interest3 + const_per_interest4 + const_per_interest5;
	construction_financing_cost = const_per_total1 + const_per_total2 + const_per_total3 + const_per_total4 + const_per_total5;

}

void N_financial_parameters::construction_financing_loan_cost(double principal /*$*/, double interest_rate /*%*/, double term_months /*-*/, double upfront_rate /*%*/,
	double & interest /*$*/, double & total_cost /*$*/)
{
	double r = interest_rate/100.0;		//[-] annual loan rate

	interest = principal * r / 12.0 * term_months / 2.0;	//[$] loan interest

	double u = upfront_rate/100.0;		//[-] up-front rate

	total_cost = principal*u + interest;
}