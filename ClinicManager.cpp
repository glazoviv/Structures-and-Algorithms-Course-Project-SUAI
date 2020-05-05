#include "ClinicManager.h"

#include <stdexcept>

using namespace std;

bool ClinicManager::AddNewPatient(std::shared_ptr<Patient> patient) {
	if(!patient) {
		return false;
	}

	string reg_number = patient->GetRegistrationNumber().data();

	if(number_patient_.Contains(reg_number)) {
		return false;
	}

	number_patient_.Insert(reg_number, patient);
	name_patients_.emplace(patient->GetName(), patient);

	return true;
}

bool ClinicManager::RemovePatient(std::string_view register_number) {
	bool result = false;
	string reg_number = register_number.data();

	if (number_patient_.Contains(reg_number)) {
		auto patient = number_patient_.Get(reg_number);
		
		if(!patient) {
			throw runtime_error("Непредвиденная ошибка при удалении пациента");
		}

		auto[begin,end] = name_patients_.equal_range(patient->GetName().data());

		for (auto it = begin; it != end; ++it) {
			if(it->second->GetRegistrationNumber() == reg_number) {
				name_patients_.erase(it);
				break;
			}
		}

		result = number_patient_.Erase(reg_number);
	}

	return result;
}

std::vector<std::shared_ptr<Patient>> ClinicManager::GetPatients() const {
	return number_patient_.GetValues();
}

std::vector<std::shared_ptr<Patient>> ClinicManager::GetPatientsByName(std::string_view name) const {
	std::vector<std::shared_ptr<Patient>> result;

	if(name_patients_.count(name.data()) > 1) {
		auto [begin, end] = name_patients_.equal_range(name.data());

		for (auto it = begin; it != end; ++it) {
			result.push_back(it->second);
		}
	}

	return result;
}
