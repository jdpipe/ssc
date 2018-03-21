#include "lib_pv_system_controller.h"

PVSystemController::PVSystemController(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager)
{
	std::unique_ptr<PVSystem> ptr(new PVSystem(pvIOManager));
	m_pvSystem = std::move(ptr);
}

const bool PVSystemController::RunSingleStep(const size_t runIndex)
{
	return (m_pvSystem->RunSingleStep(runIndex));
}

PVSystem::PVSystem(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager)
{
	std::unique_ptr<PVDCController> ptr(new PVDCController(pvIOManager));
	m_pvDCController = std::move(ptr);

	std::unique_ptr<PVACController> ptr2(new PVACController(pvIOManager));
	m_pvACController = std::move(ptr2);
}

const bool PVSystem::RunSingleStep(const size_t runIndex)
{
	return m_pvDCController->RunSingleStep(runIndex);
}

PVDCController::PVDCController(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager),
	m_MPPTIO(pvIOManager->getMPPTControllerIO())
{
}

const bool PVDCController::RunSingleStep(const size_t runIndex)
{
	for (size_t mpptType = 0; mpptType != m_MPPTIO->n_MPPTControllers; mpptType++)
	{
		if (m_MPPTControllers[0]->RunSingleStep(runIndex, mpptType) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

PVACController::PVACController(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager)
{
}

MPPTController::MPPTController(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager)
{
	m_MPPTIO = pvIOManager->getMPPTControllerIO();
	for (size_t subarrayNumber = 0; subarrayNumber != m_MPPTIO->n_enabledSubarrays; subarrayNumber++)
	{
		std::unique_ptr<Subarray> ptr(new Subarray(pvIOManager));
		m_Subarrays.push_back(std::move(ptr));
	}
}

const bool MPPTController::RunSingleStep(const size_t runIndex, const size_t mpptType)
{
	for (size_t subarrayNumber = 0; subarrayNumber != m_MPPTIO->n_enabledSubarrays; subarrayNumber++)
	{
		// Only run the subarrays that are on this mppt controller.  
		if (m_MPPTIO->subarrayMPPTControllers[subarrayNumber] == mpptType)
			m_Subarrays[subarrayNumber]->RunSingleStep(runIndex);
		
		// do stuff with multiple MPPT ports

		// do stuff with MPPT feedback to subarray and check error conditions
	}
	return EXIT_SUCCESS;
}

Subarray::Subarray(PVIOManager * pvIOManager) :
	m_pvIOManager(pvIOManager)
{
}

const bool Subarray::RunSingleStep(const size_t runIndex)
{
	bool ranSuccessfully = false;

	// Run the Irradiance model
	if (m_IrradianceModel->RunSingleStep(runIndex)){
		if (m_ModuleModel->RunSingleStep()){
			ranSuccessfully = true;
		}
	}

	// Run DC battery
	if (ranSuccessfully)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}
