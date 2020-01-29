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
			Other = 0,

			/**
			* \brief
			*	Visa.
			*/
			Visa = 1,

			/**
			* \brief
			*	MasterCard.
			*/
			MasterCard = 2,

			/**
			* \brief
			*	Maestro.
			*/
			Maestro = 3,

			/**
			* \brief
			*	Amex.
			*/
			Amex = 4,

			/**
			* \brief
			*	Jcb.
			*/
			Jcb = 5,

			/**
			* \brief
			*	Diners.
			*/
			Diners = 6,

			/**
			* \brief
			*	Discover.
			*/
			Discover = 7,

			/**
			* \brief
			*	Carte Bleue.
			*/
			CarteBleue = 8,

			/**
			* \brief
			*	Carte Blanc.
			*/
			CarteBlanc = 9,

			/**
			* \brief
			*	Voyager.
			*/
			Voyager = 10,

			/**
			* \brief
			*	Wex.
			*/
			Wex = 11,

			/**
			* \brief
			*	Union Pay.*/
			UnionPay = 12,

			/**
			* \brief
			*	Style.
			*/
			Style = 100,

			/**
			* \brief
			*	Value Link.
			*/
			ValueLink = 101,

			/**
			* \brief
			*	Interac
			*/
			Interac = 1241,

			/**
			* \brief
			*	Laser.
			*/
			Laser = 3721
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
				map["Diners"] = Diners;
				map["Discover"] = Discover;
				map["CarteBleue"] = CarteBleue;
				map["CarteBlanc"] = CarteBlanc;
				map["Voyager"] = Voyager;
				map["Wex"] = Wex;
				map["UnionPay"] = UnionPay;
				map["Style"] = Style;
				map["ValueLink"] = ValueLink;
				map["Interac"] = Interac;
				map["Laser"] = Laser;
				return map;
			}
		};

		struct CardSchemeIdMapIndex {
			static std::map<int, CardSchemeId> CreateMap() {
				std::map<int, CardSchemeId> map;
				map[0] = Other;
				map[1] = Visa;
				map[2] = MasterCard;
				map[3] = Maestro;
				map[4] = Amex;
				map[5] = Jcb;
				map[6] = Diners;
				map[7] = Discover;
				map[8] = CarteBleue;
				map[9] = CarteBlanc;
				map[10] = Voyager;
				map[11] = Wex;
				map[12] = UnionPay;
				map[100] = Style;
				map[101] = ValueLink;
				map[1241] = Interac;
				map[3721] = Laser;
				return map;
			}
		};

		/**
		* \brief
		*	Converts a string to a {@link CardSchemeId} value.
		*/
		const std::map<std::string, CardSchemeId> StringToCardSchemeId = CardSchemeIdMapGenerator::CreateMap();
		const std::map<int, CardSchemeId> IntToCardSchemeId = CardSchemeIdMapIndex::CreateMap();

	}
}
#endif