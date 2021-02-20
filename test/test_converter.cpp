#include "roman.h"

#include "gtest.h"


TEST(test_converter, romanToArabic_1)
{
  EXPECT_EQ(1, Number("I").getArabic().value);
}

TEST(test_converter, romanToArabic_5)
{
	EXPECT_EQ(5, Number("V").getArabic().value);
}

TEST(test_converter, romanToArabic_10)
{
	EXPECT_EQ(10, Number("X").getArabic().value);
}

TEST(test_converter, romanToArabic_4)
{
	EXPECT_EQ(4, Number("IV").getArabic().value);
}

TEST(test_converter, romanToArabic_7)
{
	EXPECT_EQ(7, Number("VII").getArabic().value);
}

TEST(test_converter, romanToArabic_19)
{
	EXPECT_EQ(19, Number("XIX").getArabic().value);
}

TEST(test_converter, romanToArabic_999)
{
	//EXPECT_EQ(999, Number("IM").getArabic().value);
	EXPECT_EQ(999, Number("CMXCIX").getArabic().value);
}



TEST(test_converter, arabicToRoman_1)
{
	EXPECT_EQ("I", Number(1).getRoman().value);
}

TEST(test_converter, arabicToRoman_5)
{
	EXPECT_EQ("V", Number(5).getRoman().value);
}

TEST(test_converter, arabicToRoman_100)
{
	EXPECT_EQ("C", Number(100).getRoman().value);
}

TEST(test_converter, arabicToRoman_4)
{
	EXPECT_EQ("IV", Number(4).getRoman().value);
}

TEST(test_converter, arabicToRoman_8)
{
	EXPECT_EQ("VIII", Number(8).getRoman().value);
}

TEST(test_converter, arabicToRoman_499)
{
	//EXPECT_EQ("ID", Number(499).getRoman().value);
	EXPECT_EQ("CDXCIX", Number(499).getRoman().value);
}



TEST(test_converter, invalidButFixibleRoman_Arabic)
{
	EXPECT_EQ(6, Number("IIIIII").getArabic().value);
}

TEST(test_converter, invalidButFixibleRoman_Roman)
{
	EXPECT_EQ("VI", Number("IIIIII").getRoman().value);
}

TEST(test_converter, invalidRoman)
{
	ASSERT_ANY_THROW(Number("INVALID").getRoman().value);
}