#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Awards.h"
#include <string.h>

using namespace awards;
using ::testing::InSequence;
using ::testing::Return;

class MockAwardsCeremonyActions : public AwardCeremonyActions {
public:
	MOCK_METHOD0(playAnthem, void());
	MOCK_METHOD0(turnOffTheLightsAndGoHome, void());
	MOCK_METHOD1(awardBronze, void(std::string));
	MOCK_METHOD1(awardSilver, void(std::string));
	MOCK_METHOD1(awardGold, void(std::string));
};

class RankListStub : public RankList{
public:
	MOCK_METHOD0(getNext, std::string());
};

namespace AwardsTests {
	TEST(AwardsTests, awardCeremonyActionsTest){
		MockAwardsCeremonyActions awards;
		RankListStub list;
		
		std::string a = "a";
		std::string b = "b";
		std::string c = "c";
		EXPECT_CALL(list, getNext())
			.WillOnce(Return(a))
			.WillOnce(Return(b))
			.WillOnce(Return(c));


		{
			//Start of the sequence
			InSequence sec; 


			//Play Anthem
			EXPECT_CALL(awards, playAnthem())
				.Times(1);

			//Awards Bronze Medal
			//EXPECT_CALL(list, getNext()).Times(1);
			EXPECT_CALL(awards, awardBronze(a))
				.Times(1);

			//Awards Silver Medal
			//EXPECT_CALL(list, getNext()).Times(1);
			EXPECT_CALL(awards, awardSilver(b))
				.Times(1);
			
			//EXPECT_CALL(list, getNext()).Times(1);
			EXPECT_CALL(awards, awardGold(c))
				.Times(1);
			
			//End of Ceremony
			EXPECT_CALL(awards, turnOffTheLightsAndGoHome())
				.Times(1);

			//EXPECT_CALL(list, getNext()).Times(3);
		}
		
		performAwardCeremony(list, awards);
	}

}