#include "Referral.h"
#include "Patient.h"
#include "Doctor.h"

using namespace std;

std::shared_ptr<Referral> Referral::Enter() {
	auto referral = make_shared<Referral>();

	referral->register_number = EnterRegisterNumber();
	referral->doctor_name = EnterDoctorName();



	return referral;
}