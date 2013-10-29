#include "core.h"
#include "tckernel.h"

static var_info _cm_vtab_tcsgeneric_solar[] = {
//   weather reader inputs
//   VARTYPE            DATATYPE          NAME                LABEL                                                             UNITS              META            GROUP            REQUIRED_IF                CONSTRAINTS              UI_HINTS
    { SSC_INPUT,        SSC_STRING,      "file_name",        "local weather file path",                                        "",                 "",             "Weather",        "*",                       "LOCAL_FILE",            "" },
    { SSC_INPUT,        SSC_NUMBER,      "track_mode",       "Tracking mode",                                                  "",                 "",             "Weather",        "*",                       "",                      "" },
    { SSC_INPUT,        SSC_NUMBER,      "tilt",             "Tilt angle of surface/axis",                                     "",                 "",             "Weather",        "*",                       "",                      "" },
    { SSC_INPUT,        SSC_NUMBER,      "azimuth",          "Azimuth angle of surface/axis",                                  "",                 "",             "Weather",        "*",                       "",                      "" },

	// TOU
    { SSC_INPUT,        SSC_MATRIX,      "weekday_schedule", "12x24 Time of Use Values for week days",                         "",                 "",             "tou_translator", "*",                       "",                      "" }, 
    { SSC_INPUT,        SSC_MATRIX,      "weekend_schedule", "12x24 Time of Use Values for week end days",                     "",                 "",             "tou_translator", "*",                       "",                      "" }, 

//   Generic solar model (type 260) inputs
//   VARTYPE            DATATYPE          NAME                LABEL                                                             UNITS              META            GROUP            REQUIRED_IF                CONSTRAINTS              UI_HINTS
	{ SSC_INPUT,        SSC_NUMBER,      "latitude",         "Site latitude",                                                  "",                 "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "longitude",        "Site longitude",                                                 "",                 "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "timezone",         "Site timezone",                                                  "hr",               "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "theta_stow",       "Solar elevation angle at which the solar field stops operating", "deg",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "theta_dep",        "Solar elevation angle at which the solar field begins operating","deg",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "interp_arr",       "Interpolate the array or find nearest neighbor? (1=interp,2=no)","none",             "",             "type_260",       "*",                       "INTEGER",               "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rad_type",         "Solar resource radiation type (1=DNI,2=horiz.beam,3=tot.horiz)", "none",             "",             "type_260",       "*",                       "INTEGER",               "" },
	{ SSC_INPUT,        SSC_NUMBER,      "solarm",           "Solar multiple",                                                 "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "T_sfdes",          "Solar field design point temperature (dry bulb)",                "C",                "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "irr_des",          "Irradiation design point",                                       "W/m2",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "eta_opt_soil",     "Soiling optical derate factor",                                  "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "eta_opt_gen",      "General/other optical derate",                                   "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_sfhl_ref",       "Reference solar field thermal loss fraction",                    "MW/MWcap",         "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "sfhlQ_coefs",      "Irr-based solar field thermal loss adjustment coefficients",     "1/MWt",            "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "sfhlT_coefs",      "Temp.-based solar field thermal loss adjustment coefficients",   "1/C",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "sfhlV_coefs",      "Wind-based solar field thermal loss adjustment coefficients",    "1/(m/s)",          "",             "type_260",       "*",                       "",                      "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "qsf_des",          "Solar field thermal production at design",                       "MWt",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "w_des",            "Design power cycle gross output",                                "MWe",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "eta_des",          "Design power cycle gross efficiency",                            "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_wmax",           "Maximum over-design power cycle operation fraction",             "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_wmin",           "Minimum part-load power cycle operation fraction",               "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_startup",        "Equivalent full-load hours required for power system startup",   "hours",            "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "eta_lhv",          "Fossil backup lower heating value efficiency",                   "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "etaQ_coefs",       "Part-load power conversion efficiency adjustment coefficients",  "1/MWt",            "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "etaT_coefs",       "Temp.-based power conversion efficiency adjustment coefs.",      "1/C",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "T_pcdes",          "Power conversion reference temperature",                         "C",                "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "PC_T_corr",        "Power conversion temperature correction mode (1=wetb, 2=dryb)",  "none",             "",             "type_260",       "*",                       "INTEGER",               "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_Wpar_fixed",     "Fixed capacity-based parasitic loss fraction",                   "MWe/MWcap",        "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_Wpar_prod",      "Production-based parasitic loss fraction",                       "MWe/MWe",          "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "Wpar_prodQ_coefs", "Part-load production parasitic adjustment coefs.",               "1/MWe",            "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "Wpar_prodT_coefs", "Temp.-based production parasitic adjustment coefs.",             "1/C",              "",             "type_260",       "*",                       "",                      "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "hrs_tes",          "Equivalent full-load hours of storage",                          "hours",            "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_charge",         "Storage charging energy derate",                                 "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_disch",          "Storage discharging energy derate",                              "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_etes_0",         "Initial fractional charge level of thermal storage (0..1)",      "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "f_teshl_ref",      "Reference heat loss from storage per max stored capacity",       "kWt/MWhr-stored",  "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "teshlX_coefs",     "Charge-based thermal loss adjustment - constant coef.",          "1/MWhr-stored",    "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "teshlT_coefs",     "Temp.-based thermal loss adjustment - constant coef.",           "1/C",              "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "ntod",             "Number of time-of-dispatch periods in the dispatch schedule",    "none",             "",             "type_260",       "*",                       "",                      "" },

	{ SSC_INPUT,        SSC_ARRAY,       "disws",            "Time-of-dispatch control for with-solar conditions",             "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "diswos",           "Time-of-dispatch control for without-solar conditions",          "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "qdisp",            "TOD power output control factors",                               "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_ARRAY,       "fdisp",            "Fossil backup output control factors",                           "none",             "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_MATRIX,      "OpticalTable",     "Optical table",                                                  "none",             "",             "type_260",       "*",                       "",                      "" },

	// initial values
	{ SSC_INPUT,        SSC_NUMBER,      "ibn",              "Beam-normal (DNI) irradiation",                                  "kJ/hr-m^2",        "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "ibh",              "Beam-horizontal irradiation",                                    "kJ/hr-m^2",        "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "itoth",            "Total horizontal irradiation",                                   "kJ/hr-m^2",        "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tdb",              "Ambient dry-bulb temperature",                                   "C",                "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "twb",              "Ambient wet-bulb temperature",                                   "C",                "",             "type_260",       "*",                       "",                      "" },
	{ SSC_INPUT,        SSC_NUMBER,      "vwind",            "Wind velocity",                                                  "m/s",              "",             "type_260",       "*",                       "",                      "" },


// OUTPUTS
// The names of the output variables should match the parameter names for the TCS units in order to signal the TCS kernel to store the values by timestep

//   VARTYPE            DATATYPE          NAME                LABEL                                                             UNITS           META            GROUP            REQUIRED_IF                CONSTRAINTS              UI_HINTS
    { SSC_OUTPUT,       SSC_ARRAY,       "global",            "Global horizontal irradiance",                                   "W/m2",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "beam",              "Beam normal irradiance",                                         "W/m2",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "diff",              "Diffuse horizontal irradiance",                                  "W/m2",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
	{ SSC_OUTPUT,       SSC_ARRAY,       "irr_used",          "Irradiation value used in simulation",                           "W/m2",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "tdry",              "Dry bulb temperature",                                           "C",            "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "twet",              "Wet bulb temperature",                                           "C",            "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "wspd",              "Wind velocity",                                                  "m/s",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "hour_of_day",       "Hour of the day",                                                "hour",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "day_of_year",       "Day of the year",                                                "day",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "solzen",            "Solar elevation angle",                                          "deg",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "solazi",            "Solar azimuth angle (-180..180, 0deg=South)",                    "deg",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "eta_opt_sf",        "Solar field optical efficiency",                                 "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "f_sfhl_qdni",       "Solar field load-based thermal loss correction",                 "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "f_sfhl_tamb",       "Solar field temp.-based thermal loss correction",                "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "f_sfhl_vwind",      "Solar field wind-based thermal loss correction",                 "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_hl_sf",           "Solar field thermal losses",                                     "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_sf",              "Solar field delivered thermal power",                            "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_inc",             "Qdni - Solar incident energy, before all losses",                "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_to_pb",           "Thermal energy to the power conversion system",                  "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_startup",         "Power conversion startup energy",                                "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_to_tes",          "Thermal energy into storage",                                    "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_from_tes",        "Thermal energy from storage",                                    "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "e_in_tes",          "Energy in storage",                                              "MWt-hr",       "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_hl_tes",          "Thermal losses from storage",                                    "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_dump_tesfull",    "Dumped energy  exceeding storage charge level max",              "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_dump_teschg",     "Dumped energy exceeding exceeding storage charge rate",          "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_dump_umin",       "Dumped energy from falling below min. operation fraction",       "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_dump_tot",        "Total dumped energy",                                            "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_fossil",          "Thermal energy supplied from aux firing",                        "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "q_gas",             "Energy content of fuel required to supply Qfos",                 "MWt",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "f_effpc_qtpb",      "Load-based conversion efficiency correction",                    "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "f_effpc_tamb",      "Temp-based conversion efficiency correction",                    "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "eta_cycle",         "Adjusted power conversion efficiency",                           "none",         "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_gr_solar",        "Power produced from the solar component",                        "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_gr_fossil",       "Power produced from the fossil component",                       "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_gr",              "Total gross power production",                                   "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_par_fixed",       "Fixed parasitic losses",                                         "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_par_prod",        "Production-based parasitic losses",                              "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_par_tot",         "Total parasitic losses",                                         "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_par_online",      "Online parasitics",                                              "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "w_par_offline",     "Offline parasitics",                                             "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },
    { SSC_OUTPUT,       SSC_ARRAY,       "enet",              "Net electric output",                                            "MWh",          "",            "Outputs",        "*",                       "LENGTH=8760",           "" },



	var_info_invalid };



class cm_tcsgeneric_solar : public tcKernel
{
public:

	cm_tcsgeneric_solar(tcstypeprovider *prov)
	:tcKernel(prov)
	{
		add_var_info( _cm_vtab_tcsgeneric_solar );
		//set_store_all_parameters(true); // default is 'false' = only store TCS parameters that match the SSC_OUTPUT variables above
	}

	void exec( ) throw( general_error )
	{
		//if ( 0 >= load_library("typelib") ) throw exec_error( "tcsgeneric_solar", util::format("could not load the tcs type library.") );

		bool debug_mode = false; //(__DEBUG__ == 1);  // When compiled in VS debug mode, this will use the trnsys weather file; otherwise, it will attempt to open the file with name that was passed in
		//Add weather file reader unit
		int weather = 0;
		if(debug_mode) weather = add_unit("trnsys_weatherreader", "TRNSYS weather reader");
		else weather = add_unit("weatherreader", "TCS weather reader");
		//Add Physical Solar Field Model
		int	gss = add_unit( "sam_mw_gen_type260", "Generic solar model" );

		if(debug_mode)
		{
			set_unit_value( weather, "file_name", "C:/svn_NREL/main/ssc/tcs/typelib/TRNSYS_weather_outputs/tucson_trnsys_weather.out" );
			set_unit_value( weather, "i_hour", "TIME" );
			set_unit_value( weather, "i_month", "month" );
			set_unit_value( weather, "i_day", "day" );
			set_unit_value( weather, "i_global", "GlobalHorizontal" );
			set_unit_value( weather, "i_beam", "DNI" );
			set_unit_value( weather, "i_diff", "DiffuseHorizontal" );
			set_unit_value( weather, "i_tdry", "T_dry" );
			set_unit_value( weather, "i_twet", "T_wet" );
			set_unit_value( weather, "i_tdew", "T_dew" );
			set_unit_value( weather, "i_wspd", "WindSpeed" );
			set_unit_value( weather, "i_wdir", "WindDir" );
			set_unit_value( weather, "i_rhum", "RelHum" );
			set_unit_value( weather, "i_pres", "AtmPres" );
			set_unit_value( weather, "i_snow", "SnowCover" );
			set_unit_value( weather, "i_albedo", "GroundAlbedo" );
			set_unit_value( weather, "i_poa", "POA" );
			set_unit_value( weather, "i_solazi", "Azimuth" );
			set_unit_value( weather, "i_solzen", "Zenith" );
			set_unit_value( weather, "i_lat", "Latitude" );
			set_unit_value( weather, "i_lon", "Longitude" );
			set_unit_value( weather, "i_shift", "Shift" );
		}
		else
		{
			//Set weatherreader parameters
			set_unit_value_ssc_string( weather, "file_name" );
			set_unit_value_ssc_double( weather, "track_mode" );    //, 1 );
			set_unit_value_ssc_double( weather, "tilt" );          //, 0 );
			set_unit_value_ssc_double( weather, "azimuth" );       //, 0 );
		}

		//Set parameters
        set_unit_value_ssc_double(gss, "latitude" ); //, 35);
        set_unit_value_ssc_double(gss, "longitude" ); //, -117);
		set_unit_value_ssc_matrix(gss, "OpticalTable" ); //, opt_data);
        set_unit_value_ssc_double(gss, "timezone" ); //, -8);
        set_unit_value_ssc_double(gss, "theta_stow" ); //, 170);
        set_unit_value_ssc_double(gss, "theta_dep" ); //, 10);
        set_unit_value_ssc_double(gss, "interp_arr" ); //, 1);
        set_unit_value_ssc_double(gss, "rad_type" ); //, 1);
        set_unit_value_ssc_double(gss, "solarm" ); //, solarm);
        set_unit_value_ssc_double(gss, "T_sfdes" ); //, T_sfdes);
        set_unit_value_ssc_double(gss, "irr_des" ); //, irr_des);
        set_unit_value_ssc_double(gss, "eta_opt_soil" ); //, eta_opt_soil);
        set_unit_value_ssc_double(gss, "eta_opt_gen" ); //, eta_opt_gen);
        set_unit_value_ssc_double(gss, "f_sfhl_ref" ); //, f_sfhl_ref);
        set_unit_value_ssc_array(gss, "sfhlQ_coefs" ); //, [1,-0.1,0,0]);
        set_unit_value_ssc_array(gss, "sfhlT_coefs" ); //, [1,0.005,0,0]);
        set_unit_value_ssc_array(gss, "sfhlV_coefs" ); //, [1,0.01,0,0]);
        set_unit_value_ssc_double(gss, "qsf_des" ); //, q_sf);
        set_unit_value_ssc_double(gss, "w_des" ); //, w_gr_des);
        set_unit_value_ssc_double(gss, "eta_des" ); //, eta_cycle_des);
        set_unit_value_ssc_double(gss, "f_wmax" ); //, 1.05);
        set_unit_value_ssc_double(gss, "f_wmin" ); //, 0.25);
        set_unit_value_ssc_double(gss, "f_startup" ); //, 0.2);
        set_unit_value_ssc_double(gss, "eta_lhv" ); //, 0.9);
        set_unit_value_ssc_array(gss, "etaQ_coefs" ); //, [0.9,0.1,0,0,0]);
        set_unit_value_ssc_array(gss, "etaT_coefs" ); //, [1,-0.002,0,0,0]);
        set_unit_value_ssc_double(gss, "T_pcdes" ); //, 21);
        set_unit_value_ssc_double(gss, "PC_T_corr" ); //, 1);
        set_unit_value_ssc_double(gss, "f_Wpar_fixed" ); //, f_Wpar_fixed);
        set_unit_value_ssc_double(gss, "f_Wpar_prod" ); //, f_Wpar_prod);
        set_unit_value_ssc_array(gss, "Wpar_prodQ_coefs" ); //, [1,0,0,0]);
        set_unit_value_ssc_array(gss, "Wpar_prodT_coefs" ); //, [1,0,0,0]);
        set_unit_value_ssc_double(gss, "hrs_tes" ); //, hrs_tes);
        set_unit_value_ssc_double(gss, "f_charge" ); //, 0.98);
        set_unit_value_ssc_double(gss, "f_disch" ); //, 0.98);
        set_unit_value_ssc_double(gss, "f_etes_0" ); //, 0.1);
        set_unit_value_ssc_double(gss, "f_teshl_ref" ); //, 0.35);
        set_unit_value_ssc_array(gss, "teshlX_coefs" ); //, [1,0,0,0]);
        set_unit_value_ssc_array(gss, "teshlT_coefs" ); //, [1,0,0,0]);
        set_unit_value_ssc_double(gss, "ntod" ); //, 9);
        set_unit_value_ssc_array(gss, "disws" ); //, [0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1]);
        set_unit_value_ssc_array(gss, "diswos" ); //, [0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1]);
        set_unit_value_ssc_array(gss, "qdisp" ); //, [1,1,1,1,1,1,1,1,1]);
        set_unit_value_ssc_array(gss, "fdisp" ); //, [0,0,0,0,0,0,0,0,0]);


		//Set the initial values
        set_unit_value_ssc_double(gss, "ibn" ); //, 0.);	//Beam-normal (DNI) irradiation
        set_unit_value_ssc_double(gss, "ibh" ); //, 0.);	//	Beam-horizontal irradiation
        set_unit_value_ssc_double(gss, "itoth" ); //, 0.);	//	Total horizontal irradiation
        set_unit_value_ssc_double(gss, "tdb" ); //, 15.);	//	Ambient dry-bulb temperature
        set_unit_value_ssc_double(gss, "twb" ); //, 10.);	//	Ambient wet-bulb temperature
        set_unit_value_ssc_double(gss, "vwind" ); //, 1.);	//	Wind velocity

		// Connect the units
		bool bConnected = connect(weather, "beam", gss, "ibn");
		bConnected &= connect(weather, "global", gss, "itoth");
		bConnected &= connect(weather, "poa_beam", gss, "ibh");
		bConnected &= connect(weather, "tdry", gss, "tdb");
		bConnected &= connect(weather, "twet", gss, "twb");
		bConnected &= connect(weather, "wspd", gss, "vwind");
		//location
		bConnected &= connect(weather, "lat", gss, "latitude");
		bConnected &= connect(weather, "lon", gss, "longitude");
		bConnected &= connect(weather, "tz", gss, "timezone");

		// Example for changing an input variable name in the SSC interface
		// set_unit_value( u3, "m_dot_htf", as_double("m_dot_htf_init") );


		// check if all connections worked
		if ( !bConnected )
			throw exec_error( "tcsgeneric_solar", util::format("there was a problem connecting outputs of one unit to inputs of another for the simulation.") );

		// Run simulation
		size_t hours = 8760;
		if (0 > simulate(3600, hours*3600, 3600) )
			throw exec_error( "tcsgeneric_solar", util::format("there was a problem simulating in tcsgeneric_solar.") );

		// get the outputs
		if (!set_all_output_arrays() )
			throw exec_error( "tcsgeneric_solar", util::format("there was a problem returning the results from the simulation.") );


		//set_output_array("i_SfTi",8760);
	}

};

DEFINE_TCS_MODULE_ENTRY( tcsgeneric_solar, "Generic CSP model using the generic solar TCS types.", 4 )

//static compute_module *_create_tcsgeneric_solar() {
//	extern tcstypeprovider TCSTP;
//	return new cm_tcsgeneric_solar( &TCSTP, I_TEST );
//}
//module_entry_info cm_entry_tcsgeneric_solar = { "tcsgeneric_solar", "rtrrt", 4, _create_tcsgeneric_solar };
