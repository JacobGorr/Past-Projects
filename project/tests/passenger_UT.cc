/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:

  	Passenger* passenger;

	virtual void SetUp() {
    	passenger = new Passenger();
			passenger2 = new Passenger(11, "Jane");
  	}

  	virtual void TearDown() {
    	delete passenger;
			delete passenger2;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, IsOnBus) {
	EXPECT_EQ(passenger->IsOnBus(), false);
	EXPECT_NE(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, GetDestination) {
	EXPECT_EQ(passenger2->GetDestination(), 11);

};

TEST_F(PassengerTests, GetTotalWait) {
	EXPECT_EQ(passenger->GetTotalWait(), 0);
};

TEST_F(PassengerTests, Update) {
	EXPECT_EQ(passenger2->GetTotalWait(), 0);
	passenger2->Update();
	EXPECT_EQ(passenger2->GetTotalWait(), 1);
};

TEST_F(PassengerTests, Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};
