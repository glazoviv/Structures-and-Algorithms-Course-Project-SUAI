#include "ClinicManager.h"

#include <stdexcept>

#include "Accessory.h"

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

bool ClinicManager::ErasePatient(std::string_view register_number) {
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

		/* Удаляем направления */
		referrals_.Erase([register_number](std::shared_ptr<Referral> referral) {
			return register_number == referral->register_number;
		});
	}

	return result;
}

std::vector<std::weak_ptr<Patient>> ClinicManager::GetPatients() const {
	std::vector<std::weak_ptr<Patient>> result;
	
	auto patients = number_patient_.GetValues();
	result.reserve(patients.size());

	for(auto patient : patients) {
		result.push_back(patient);
	}

	return result;
}

void ClinicManager::ErasePatients() {
	number_patient_.Clear();
	name_patients_.clear();

	referrals_.Clear();
}

std::pair<std::weak_ptr<Patient>, std::string> ClinicManager::GetPatient(std::string_view reg_number) {
	if(reg_number.empty()) {
		return { {}, {} };
	}

	auto patient = number_patient_.Get(reg_number);
	if(!patient) {
		return { {}, {} };
	}

	auto node = referrals_.Find([reg_number](std::shared_ptr<Referral> other) {
		return reg_number == other->register_number;
	});

	std::string doctor_name;

	if(node) {
		doctor_name = node->value->doctor_name;
	}

	return { patient , doctor_name };
}


std::vector<std::weak_ptr<Patient>> ClinicManager::GetPatientsByName(std::string_view name) const {
	std::vector<std::weak_ptr<Patient>> result;

	if(name_patients_.count(name.data()) > 0) {
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

	/* Удаляем направления */
	referrals_.Erase([name](std::shared_ptr<Referral> referral) {
		return name == referral->doctor_name;
	});

	return true;
}

std::vector<std::weak_ptr<Doctor>> ClinicManager::GetDoctors() {
	std::vector<std::weak_ptr<Doctor>> result;

	name_doctor_.SymmetricForEach([&result](AvlTree<std::string_view, std::shared_ptr<Doctor>>::Node node) mutable {
		result.push_back(node.value);
	});

	return result;
}

void ClinicManager::EraseDoctors() {
	name_doctor_.Clear();
	referrals_.Clear();
}

std::pair<std::weak_ptr<Doctor>, std::vector<std::string>> ClinicManager::GetDoctorByName(std::string_view name) {
	if(!name_doctor_.Contains(name)) {
		return {};
	}

	auto doctor = name_doctor_.GetValue(name);

	vector<string> patients;

	if(doctor) {

		referrals_.ForEach([&patients, name](std::shared_ptr<Referral> other) mutable {
			if(name == other->doctor_name) {
				patients.push_back(other->register_number);
			}
		});
	}

	return { doctor, patients };
}

std::vector<std::weak_ptr<Doctor>> ClinicManager::GetDoctorsByPosition(std::string_view position) {
	std::vector<std::weak_ptr<Doctor>> result;

	name_doctor_.SymmetricForEach([&result, position](AvlTree<std::string_view, std::shared_ptr<Doctor>>::Node node) mutable {
		if(FindSubstring(node.value->GetPosition(), position) != -1) {
			result.push_back(node.value);
		}
	});

	return result;
}

ClinicManager::ReferralError ClinicManager::RegistrationRefferal(std::shared_ptr<Referral> refferral) {
	if(!refferral) {
		return ReferralError::REFERRAL_EMPTY;
	}

	if (!number_patient_.Contains(refferral->register_number)) {
		return ReferralError::PATIENT_NOT_EXISTS;
	}

	if(!name_doctor_.Contains(refferral->doctor_name)) {
		return ReferralError::DOCTOR_NOT_EXISTS;
	}
	
	auto node = referrals_.Find([refferral](std::shared_ptr<Referral> other) {
		return refferral->date == other->date
			&& refferral->time == other->time
			&& refferral->doctor_name == other->doctor_name;
	});

	if(!node) {
		referrals_.PushFront(refferral);

		BubleSort(referrals_, [](std::shared_ptr<Referral> lhs, std::shared_ptr<Referral> rhs) {
			return lhs->doctor_name < rhs->doctor_name;
		});
	}


	return node ? ReferralError::DATETIME_BUSY : ReferralError::OK;
}

bool ClinicManager::RefundRefferal(std::shared_ptr<Referral> refferral) {
	if (!refferral) {
		return false;
	}
	
	auto node = referrals_.Find([refferral](std::shared_ptr<Referral> other) {
		return refferral->register_number == other->register_number &&
			refferral->time == other->time &&
			refferral->date == other->date &&
			refferral->doctor_name == other->doctor_name;
	});

	return false;
}