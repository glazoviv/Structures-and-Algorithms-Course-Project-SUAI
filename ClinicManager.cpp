#include "ClinicManager.h"

#include <stdexcept>

using namespace std;

bool ClinicManager::AddPatient(std::shared_ptr<Patient> patient) {
	if(!patient) {
		return false;
	}

	auto reg_number = patient->GetRegistrationNumber();

	if(number_patient_.Contains(reg_number)) {
		return false;
	}

	number_patient_.Insert(reg_number, patient);
	name_patients_.emplace(patient->GetName(), patient);

	return true;
}

bool ClinicManager::RemovePatient(std::string_view register_number) {
	bool result = false;

	if (number_patient_.Contains(register_number)) {
		auto patient = number_patient_.Get(register_number);
		
		if(!patient) {
			throw runtime_error("Непредвиденная ошибка при удалении пациента");
		}

		auto[begin,end] = name_patients_.equal_range(patient->GetName().data());

		for (auto it = begin; it != end; ++it) {
			if(it->second->GetRegistrationNumber() == register_number) {
				name_patients_.erase(it);
				break;
			}
		}

		result = number_patient_.Erase(register_number);
	}

	return result;
}

std::vector<std::shared_ptr<Patient>> ClinicManager::GetPatients() const {
	return number_patient_.GetValues();
}

std::vector<std::shared_ptr<Patient>> ClinicManager::GetPatientsByName(std::string_view name) const {
	std::vector<std::shared_ptr<Patient>> result;

	if(name_patients_.count(name.data()) > 1) {
		auto [begin, end] = name_patients_.equal_range(name);

		for (auto it = begin; it != end; ++it) {
			result.push_back(it->second);
		}
	}

	return result;
}

bool ClinicManager::AddDoctor(std::shared_ptr<Doctor> doctor) {
	if(!doctor || name_doctor_.Contains(doctor->GetName())) {
		return false;
	}

	name_doctor_.Insert(doctor->GetName(), doctor);

	return true;
}

bool ClinicManager::EraseDoctor(std::string_view name) {
	if (name.empty() || !name_doctor_.Contains(name)) {
		return false;
	}

	name_doctor_.Erase(name);

	return true;
}

std::vector<std::shared_ptr<Doctor>> ClinicManager::GetDoctors() {
	std::vector<std::shared_ptr<Doctor>> result;

	name_doctor_.SymmetricForEach([&result](AvlTree<std::string_view, std::shared_ptr<Doctor>>::Node node) mutable {
		result.push_back(node.value);
	});

	return result;
}

void ClinicManager::EraseDoctors() {
	name_doctor_.Clear();
}
