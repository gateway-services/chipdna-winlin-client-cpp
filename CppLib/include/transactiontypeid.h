#ifndef TRANSACTIONTYPEID_H
#define TRANSACTIONTYPEID_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		*	Transaction Type Values
		**/
		enum TransactionTypeId {
			/**
			* \brief
			*	Authorization.
			*/
			Authorization = 0,

			/**
			* \brief
			*	Linked Refund.
			*/
			LinkedRefund = 1,

			/**
			* \brief
			*	Account Verification.
			*/
			AccountVerification = 3,

			/**
			* \brief
			*	Offline Authorization.
			*/
			OfflineAuth = 4,

			/**
			* \brief
			*	Voice Referral.
			*/
			VoiceReferral = 5,

			/**
			* \brief
			*	Standalone Refund.
			*/
			StandaloneRefund = 6,

			/**
			* \brief
			*	Deferred Authorization.
			*/
			DeferredAuth = 30
		};

		struct TransactionTypeIdMapGenerator {
			static std::map<std::string, TransactionTypeId> CreateMap() {
				std::map<std::string, TransactionTypeId> map;
				map["Authorization"] = Authorization;
				map["LinkedRefund"] = LinkedRefund;
				map["AccountVerification"] = AccountVerification;
				map["OfflineAuth"] = OfflineAuth;
				map["VoiceReferral"] = VoiceReferral;
				map["StandaloneRefund"] = StandaloneRefund;
				map["DeferredAuth"] = DeferredAuth;
				return map;
			}
		};

		struct TransactionTypeIdMapIndex {
			static std::map<int, TransactionTypeId> CreateMap() {
				std::map<int, TransactionTypeId> map;
				map[0] = Authorization;
				map[1] = LinkedRefund;
				map[3] = AccountVerification;
				map[4] = OfflineAuth;
				map[5] = VoiceReferral;
				map[6] = StandaloneRefund;
				map[30] = DeferredAuth;
				return map;
			}
		};

		/**
		* \brief
		*	Converts a string to a {@link TransactionTypeId} value.
		*/
		const std::map<std::string, TransactionTypeId> StringToTransactionTypeId = TransactionTypeIdMapGenerator::CreateMap();
		const std::map<int, TransactionTypeId> IntToTransactionTypeId = TransactionTypeIdMapIndex::CreateMap();

	}
}
#endif