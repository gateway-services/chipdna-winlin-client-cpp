#ifndef VALIDATIONERRORCODE_H
#define VALIDATIONERRORCODE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Validation Error Codes.
		**/
		enum ValidationErrorCode {

			/**
			* \brief
			* 	Required parameter is missing.
			**/
			MissingParameter,

			/**
			* \brief
			* 	The value provided is invalid.
			*/
			InvalidValue,

			/**
			* \brief
			* 	Reference has already been used for another approved transaction.
			**/
			ReferenceAlreadyExistsForApprovedTransaction,

			/**
			* \brief
			* 	Unexpected parameters encountered.
			**/
			UnexpectedParameters,

			/**
			* \brief
			* 	Amount is less than minimum amount permitted.
			**/
			AmountTooSmall,

			/**
			* \brief
			* 	Amount is more than minimum amount permitted.
			**/
			AmountTooLarge,

			/**
			* \brief
			* 	Amount of zero is not allowed.
			**/
			AmountZeroNotAllowed,

			/**
			* \brief
			* 	Parameter is not valid with related command.
			**/
			InvalidParameter,

			/**
			* \brief
			* 	Billing Information contains ambiguous parameter values. They should be checked for consistency.
			**/
			AmbiguousBillingInformation,

			/**
			* \brief
			* 	Misconfiguration of TippingSupported. 
			**/
			TippingNotSupported
		};
		
		struct ValidationErrorCodeMapGenerator {
			static std::map<std::string, ValidationErrorCode> CreateMap() {
				std::map<std::string, ValidationErrorCode> map;
				map["MissingParameter"] = MissingParameter;
				map["InvalidValue"] = InvalidValue;
				map["ReferenceAlreadyExistsForApprovedTransaction"] = ReferenceAlreadyExistsForApprovedTransaction;
				map["UnexpectedParameters"] = UnexpectedParameters;
				map["AmountTooSmall"] = AmountTooSmall;
				map["AmountTooLarge"] = AmountTooLarge;
				map["AmountZeroNotAllowed"] = AmountZeroNotAllowed;
				map["InvalidParameter"] = InvalidParameter;
				map["AmbiguousBillingInformation"] = AmbiguousBillingInformation;
				map["TippingNotSupported"] = TippingNotSupported;

				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link ValidationErrorCode} value.
		**/
		const std::map<std::string, ValidationErrorCode> StringToValidationErrorCode = ValidationErrorCodeMapGenerator::CreateMap();

	}
}
#endif