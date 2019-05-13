#ifndef CHIPDNASERVERISSUE_H
#define CHIPDNASERVERISSUE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	ChipDNA server status.
		*/
		enum ChipDnaServerIssue {
			/**
			* \brief
			* 	ChipDNA is not initialized.
			*/
			Uninitialized,

			/**
			* \brief
			* 	ChipDNA is in normal operation.
			*/
			None,

			/**
			* \brief
			* 	ChipDNA has no PINpads are available.
			*/
			NoPinPadsAvailable,

			/**
			* \brief
			* 	ChipDNA has no configured PINpads.
			*/
			NoPinPadsConfigured,

			/**
			* \brief
			* 	ChipDNA encryption certificate is missing.
			*/
			EncryptionCertRequired,

			/**
			* \brief
			* 	ChipDNA encryption certificate is invalid.
			*/
			EncryptionCertInvalid,

			/**
			* \brief
			* 	ChipDNA configured Creditcall terminal is disabled.
			*/
			TerminalDisabled,

			/**
			* \brief
			* 	ChipDNA application has been disabled.
			*/
			ApplicationDisabled,

			/**
			* \brief
			* 	ChipDNA TMS configuration not found.
			*/
			TerminalConfigurationNotFound,

			/**
			* \brief
			* 	Not enough disk space for ChipDNA to continue.
			*/
			InsufficientStorageSpace,

			/**
			* \brief
			* 	ChipDNA server is currently updating payment devices.
			*/
			InScheduleUpdateTime
		};
		
		struct ChipDnaServerIssueMapGenerator {
			static std::map<std::string, ChipDnaServerIssue> CreateMap() {
				std::map<std::string, ChipDnaServerIssue> map;
				map["Uninitialized"] = Uninitialized;
				map["None"] = None;
				map["NoPinPadsAvailable"] = NoPinPadsAvailable;
				map["NoPinPadsConfigured"] = NoPinPadsConfigured;
				map["EncryptionCertRequired"] = EncryptionCertRequired;
				map["EncryptionCertInvalid"] = EncryptionCertInvalid;
				map["TerminalDisabled"] = TerminalDisabled;
				map["ApplicationDisabled"] = ApplicationDisabled;
				map["TerminalConfigurationNotFound"] = TerminalConfigurationNotFound;
				map["InsufficientStorageSpace"] = InsufficientStorageSpace;
				map["InScheduleUpdateTime"] = InScheduleUpdateTime;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link ChipDnaServerIssue} value.
		**/
		const std::map<std::string, ChipDnaServerIssue> StringToChipDnaServerIssue = ChipDnaServerIssueMapGenerator::CreateMap();
	}
}
#endif