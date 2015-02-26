#include "stdafx.h"
#include "CppUnitTest.h"
#include "Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		// Testing if string returns is lower-cased.
		TEST_METHOD(Test_readCommand)
		{
			string input = "QWERT";
			string test1 = readCommand(input);
			string testExpected = "qwert";
			Assert::AreEqual(testExpected,test1);
		}

		// Display function display in the format below:
		// 1. <item>
		// 2. <item>
		// Testing if format is displayed correctly.
		TEST_METHOD(Test_display)
		{
			vector<string> inputVector;
			inputVector.push_back("First line");
			inputVector.push_back("Second line");
			inputVector.push_back("Third line");

			string inputString;
			inputString = commandDisplay(inputVector);

			string expectedString = "1. First line\n2. Second line\n3. Third line\n" ;

			Assert::AreEqual(expectedString, inputString);
		}
		
		// Function sorts in this order:
		// Number -> Big Letters -> Small Letters
		TEST_METHOD(Test_sort)
		{
			vector<string> inputVector;
			inputVector.push_back("ccc");
			inputVector.push_back("bbb");
			inputVector.push_back("aaa");
			inputVector.push_back("333");
			inputVector.push_back("222");
			inputVector.push_back("111");
			inputVector.push_back("CCC");
			inputVector.push_back("BBB");
			inputVector.push_back("AAA");

			inputVector = commandSort(inputVector);

			string inputString = commandDisplay(inputVector);

			vector<string> testExpected;
			testExpected.push_back("111");
			testExpected.push_back("222");
			testExpected.push_back("333");
			testExpected.push_back("AAA");
			testExpected.push_back("BBB");
			testExpected.push_back("CCC");
			testExpected.push_back("aaa");
			testExpected.push_back("bbb");
			testExpected.push_back("ccc");

			string testExpectedString = commandDisplay(testExpected);

			Assert::AreEqual(testExpectedString, inputString);	
		}

		// Search returns all sentences that have the search word in it.
		TEST_METHOD(Test_Search)
		{
			vector<string> inputVector;
			inputVector.push_back("apples are healthy");
			inputVector.push_back("an apple a day");
			inputVector.push_back("keeps the doctor away");
			inputVector.push_back("I like to eat apples");
			inputVector.push_back("they are red");

			string inputString = commandSearch(inputVector, "apple");

			vector<string> testExpected;
			testExpected.push_back("1. apples are healthy");
			testExpected.push_back("2. an apple a day");
			testExpected.push_back("4. I like to eat apples");

			ostringstream oss;
			for(int i=0; i<testExpected.size() ; i++){
				oss << testExpected[i] << endl;
			}

			string testExpectedString = oss.str();

			Assert::AreEqual(testExpectedString, inputString);
		}

	};
}