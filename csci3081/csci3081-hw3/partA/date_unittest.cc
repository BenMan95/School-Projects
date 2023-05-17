#include "gtest/gtest.h"
#include "date.h"

class DateTest : public ::testing::Test {
  public:
    void SetUp( ) { 
      // code here will execute just before the test ensues 
      first_day = Date(2018, 9, 4);
      last_day = Date(2018, 12, 11);
    }
  protected:
    Date first_day;          // first day of classes
    Date last_day;           // last day of classes
};

// Tests PrintDate with newlines
TEST_F(DateTest, PrintDateTests) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  std::string expected_out_1 = "1999-12-31\n";
  std::string expected_out_2 = "1776-07-04\n";
  std::string expected_out_3 = "2018-10-31\n";

  testing::internal::CaptureStdout();
  y2k.PrintDate(true);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  ind_day.PrintDate(true);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintDate(true);
  std::string output3 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

// Tests PrintDate without newlines
TEST_F(DateTest, PrintDateTestsWithoutNewline) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  std::string expected_out_1 = "1999-12-31";
  std::string expected_out_2 = "1776-07-04";
  std::string expected_out_3 = "2018-10-31";

  testing::internal::CaptureStdout();
  y2k.PrintDate(false);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ind_day.PrintDate(false);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintDate(false);
  std::string output3 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

// Tests GetUsDate and DaysBetween
TEST_F(DateTest, DaysBetweenTests) {
  EXPECT_EQ(first_day.GetUsDate(), "09-04-2018") << "First day of class not setup properly";
  EXPECT_EQ(last_day.GetUsDate(), "12-11-2018") << "Last day of class not setup properly";
  EXPECT_EQ(first_day.DaysBetween(last_day), 98) << "Days between is not calculated properly";
}

// Provided Tests
//=============================================================================
// My Tests

// Tests PrintUsDate with newlines
TEST_F(DateTest, PrintUsDateTests) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  std::string expected_out_1 = "12-31-1999\n";
  std::string expected_out_2 = "07-04-1776\n";
  std::string expected_out_3 = "10-31-2018\n";

  testing::internal::CaptureStdout();
  y2k.PrintUsDate(true);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ind_day.PrintUsDate(true);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintUsDate(true);
  std::string output3 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

// Tests PrintUsDate without newlines
TEST_F(DateTest, PrintUsDateTestsNewline) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  std::string expected_out_1 = "12-31-1999";
  std::string expected_out_2 = "07-04-1776";
  std::string expected_out_3 = "10-31-2018";

  testing::internal::CaptureStdout();
  y2k.PrintUsDate(false);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  ind_day.PrintUsDate(false);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintUsDate(false);
  std::string output3 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

// Tests GetDate
TEST_F(DateTest, GetDateTest) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  EXPECT_EQ(y2k.GetDate(), "1999-12-31");
  EXPECT_EQ(ind_day.GetDate(), "1776-07-04");
  EXPECT_EQ(best_holiday.GetDate(), "2018-10-31");
}

// Tests date constructor using current date
TEST_F(DateTest, CurrentDateTest) {
  Date today;

  // The expected value is hardcoded, and should be updated as necessary
  EXPECT_EQ(today.GetDate(), "2022-11-08") << "Current date not setup properly";
}

// Tests date constructor using epoch
TEST_F(DateTest, EpochDateTest) {
  Date epoch(0);
  Date date1(60 * 60 * 24);
  Date date2(31 * 60 * 60 * 24);
  Date date3(365 * 60 * 60 * 24);
  Date date4(-365 * 60 * 60 * 24);

  EXPECT_EQ(epoch.GetDate(), "1970-01-01") << "Epoch date not setup properly";
  EXPECT_EQ(date1.GetDate(), "1970-01-02") << "Date one day from epoch not setup properly";
  EXPECT_EQ(date2.GetDate(), "1970-02-01") << "Date one month from epoch not setup properly";
  EXPECT_EQ(date3.GetDate(), "1971-01-01") << "Date one year from epoch not setup properly";
  EXPECT_EQ(date4.GetDate(), "1969-01-01") << "Date one year before epoch not setup properly";
}

// Tests DaysBetween with the dates given in the README
TEST_F(DateTest, DaysBetweenTest2) {
  Date day1(2016, 1, 1);
  Date day2(2016, 3, 1);

  EXPECT_EQ(day1.DaysBetween(day2), 60) << "Days between dates is not calculated properly";
}

// Tests addition operator
TEST_F(DateTest, DateAdditionTest) {
  Date date1(0);
  Date date2(100 * 60 * 60 * 24);
  Date date3(-100 * 60 * 60 * 24);

  Date calc1 = date1 + 100;
  Date calc2 = date3 + 100;
  Date calc3 = date3 + 200;

  EXPECT_EQ(calc1.GetDate(), date2.GetDate()) << "Date addition not calculated properly";
  EXPECT_EQ(calc2.GetDate(), date1.GetDate()) << "Date addition not calculated properly";
  EXPECT_EQ(calc3.GetDate(), date2.GetDate()) << "Date addition not calculated properly";
}

// Tests subtraction operator
TEST_F(DateTest, DateSubtractionTest) {
  Date date1(0);
  Date date2(100 * 60 * 60 * 24);
  Date date3(-100 * 60 * 60 * 24);

  Date calc1 = date2 - 100;
  Date calc2 = date1 - 100;
  Date calc3 = date2 - 200;

  EXPECT_EQ(calc1.GetDate(), date1.GetDate()) << "Date subtraction not calculated properly";
  EXPECT_EQ(calc2.GetDate(), date3.GetDate()) << "Date subtraction not calculated properly";
  EXPECT_EQ(calc3.GetDate(), date3.GetDate()) << "Date subtraction not calculated properly";
}

// Tests both addition and subtraction operators
TEST_F(DateTest, OperationsTest) {
  Date date1(2016, 3, 1);
  Date date2(2016, 2, 27);

  EXPECT_EQ((date1 - 2).GetDate(), "2016-02-28") << "Date addition not calculated properly";
  EXPECT_EQ((date2 + 2).GetDate(), "2016-02-29") << "Date addition not calculated properly";
}
