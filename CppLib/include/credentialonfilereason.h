#ifndef CREDENTIALONFILEREASON_H
#define CREDENTIALONFILEREASON_H

#include <map>

namespace ChipDnaClientLib {

	/// Parameter tokens
	namespace ParameterTokens {

		/**
		* \brief
		* 	Credential On File Reason.
		**/
		enum CredentialOnFileReason {
			/**
			* \brief
			* 	The Credential on File transaction is an unscheduled transaction.
			*/
			Unscheduled,

			/**
			* \brief
			* 	The Credential on File transaction is an installment.
			*/
			Installment,

			/**
			* \brief
			* 	The Credential on File transaction is an incremental transaction.
			*/
			Incremental,

			/**
			* \brief
			* 	The Credential on File transaction is a resubmission.
			*/
			Resubmission,

			/**
			* \brief
			* 	The Credential on File transaction is a delayed charge.
			*/
			DelayedCharge,

			/**
			* \brief
			* 	The Credential on File transaction is a re-auth.
			*/
			ReAuth,

			/**
			* \brief
			* 	The Credential on File transaction is due to no show.
			*/
			NoShow
		};

		struct CredentialOnFileReasonMapGenerator {
			static std::map<std::string, CredentialOnFileReason> CreateMap() {
				std::map<std::string, CredentialOnFileReason> map;
				map["Unscheduled"] = Unscheduled;
				map["Installment"] = Installment;
				map["Incremental"] = Incremental;
				map["Resubmission"] = Resubmission;
				map["DelayedCharge"] = DelayedCharge;
				map["ReAuth"] = ReAuth;
				map["NoShow"] = NoShow;
				return map;
			}
		};
	}
}
#endif