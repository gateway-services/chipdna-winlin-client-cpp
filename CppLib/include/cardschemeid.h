#ifndef CARDSCHEMEID_H
#define CARDSCHEMEID_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {
		
		/**
		* \brief
		*	Card Scheme Values
		**/
		enum CardSchemeId {
			/**
			* \brief
			*	Other.
			*/
			Other,

			/**
			* \brief
			*	Visa.
			*/
			Visa,

			/**
			* \brief
			*	MasterCard.
			*/
			MasterCard,

			/**
			* \brief
			*	Maestro.
			*/
			Maestro,

			/**
			* \brief
			*	Amex.
			*/
			Amex,

			/**
			* \brief
			*	Jcb.
			*/
			Jcb,

			/**
			* \brief
			*	Diners.
			*/
			Diners,

			/**
			* \brief
			*	Discover.
			*/
			Discover,

			/**
			* \brief
			*	Carte Bleue.
			*/
			CarteBleue,

			/**
			* \brief
			*	Carte Blanc.
			*/
			CarteBlanc,

			/**
			* \brief
			*	Voyager.
			*/
			Voyager,

			/**
			* \brief
			*	Wex.
			*/
			Wex,

			/**
			* \brief
			*	China Union Pay.*/
			ChinaUnionPay,

			/**
			* \brief
			*	Style.
			*/
			Style,

			/**
			* \brief
			*	Value Link.
			*/
			ValueLink,

			/**
			* \brief
			*	Interac
			*/
			Interac,

			/**
			* \brief
			*	Laser.
			*/
			Laser
		};

		struct CardSchemeIdMapGenerator {
			static std::map<std::string, CardSchemeId> CreateMap() {
				std::map<std::string, CardSchemeId> map;
				map["Other"] = Other;
				map["Visa"] = Visa;
				map["MasterCard"] = MasterCard;
				map["Maestro"] = Maestro;
				map["Amex"] = Amex;
				map["Jcb"] = Jcb;
				map["Diner"] = Diners;
				map["Discover"] = Discover;
				map["CarteBleue"] = CarteBleue;
				map["CarteBlanc"] = CarteBlanc;
				map["Voyager"] = Voyager;
				map["Wex"] = Wex;
				map["ChinaUnionPay"] = ChinaUnionPay;
				map["Style"] = Style;
				map["ValueLink"] = ValueLink;
				map["Interac"] = Interac;
				map["Laser"] = Laser;
				return map;
			}
		};

		/**
		* \brief
		*	Converts a string to a {@link CardSchemeId} value.
		*/
		const std::map<std::string, CardSchemeId> StringToCardSchemeId = CardSchemeIdMapGenerator::CreateMap();
	}
}
#endif