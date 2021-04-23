#include "text.h"

#include "gtest.h"

TEST(test_text_format, create_string)
{
	Line l("key:value");
	EXPECT_EQ(l.getKey(), "key");
	EXPECT_EQ(l.getValue()->getString(), "value");
	EXPECT_EQ(l.getValue()->getType(), object_type::String);
}

TEST(test_text_format, create_comment)
{
	Line l("#comment");
	EXPECT_EQ(l.getValue()->getString(), "comment");
	EXPECT_EQ(l.getValue()->getType(), object_type::Comment);
}

TEST(test_text_format, create_title)
{
	Line l("title:");
	EXPECT_EQ(l.getKey(), "title");
	EXPECT_EQ(l.getValue()->getType(), object_type::Title);
}


TEST(test_text, can_create_text)
{
	ASSERT_NO_THROW(Text t);
}

TEST(test_text, can_add_lines)
{
	Text t;
	ASSERT_NO_THROW(t.addLeft("line1"));
	ASSERT_NO_THROW(t.addLeft("line2"));
}

TEST(test_text, correct_move_left)
{
	Text t;
	t.addLeft("line1");
	EXPECT_EQ(t.left(), false);
	t.addLeft("line2");
	EXPECT_EQ(t.left(), true);
	EXPECT_EQ(t.left(), false);
}

TEST(test_text, correct_move_top)
{
	Text t;
	t.addLeft("line1");
	t.addLeft("line2");
	EXPECT_EQ(t.top(), false);
	t.left();
	EXPECT_EQ(t.top(), true);
	EXPECT_EQ(t.top(), false);
}

TEST(test_text, can_add_underlines)
{
	Text t;
	t.addLeft("line");
	ASSERT_NO_THROW(t.addRight("underline"));
}

TEST(test_text, correct_move_right)
{
	Text t;
	t.addLeft("line");
	EXPECT_EQ(t.right(), false);
	t.addRight("underline");
	EXPECT_EQ(t.right(), true);
	EXPECT_EQ(t.right(), false);
}

TEST(test_text, correct_move_overTop)
{
	Text t;
	t.addLeft("line");
	t.addRight("underline");
	EXPECT_EQ(t.overTop(), false);
	t.right();
	EXPECT_EQ(t.overTop(), true);
	EXPECT_EQ(t.overTop(), false);
}

TEST(test_text, get_value)
{
	Text t;
	string path = "key";
	EXPECT_EQ(t.getValue(path), "");
	t.addLeft("key:value");
	EXPECT_EQ(t.getValue(path), "value");
}

TEST(test_text, replace_line)
{
	Text t;
	ASSERT_ANY_THROW(t.replace("line"));
	t.addLeft("line1:1");
	ASSERT_NO_THROW(t.replace("line2:2"));
	string path1 = "line1";
	string path2 = "line2";
	EXPECT_EQ(t.getValue(path1), "");
	EXPECT_EQ(t.getValue(path2), "2");
}

TEST(test_text, replace_key)
{
	Text t;
	ASSERT_ANY_THROW(t.replaceKey("key"));
	t.addLeft("key1:1");
	ASSERT_NO_THROW(t.replaceKey("key2"));
	string path1 = "key1";
	string path2 = "key2";
	EXPECT_EQ(t.getValue(path1), "");
	EXPECT_EQ(t.getValue(path2), "1");
}

TEST(test_text, replace_value)
{
	Text t;
	ASSERT_ANY_THROW(t.replaceValue("value"));
	t.addLeft("key:v1");
	ASSERT_NO_THROW(t.replaceValue("v2"));
	string path = "key";
	EXPECT_EQ(t.getValue(path), "v2");
}

TEST(test_text, remove_line)
{
	Text t;
	ASSERT_ANY_THROW(t.remove());
	t.addLeft("line");
	ASSERT_NO_THROW(t.remove());
}

TEST(test_text, IO_file)
{
	Text t1;
	t1.addLeft("key:value");
	ofstream fileO("..\\test.yml");
	if (fileO.is_open())
		fileO << t1;
	fileO.close();

	Text t2;
	ifstream fileI("..\\test.yml");
	if (fileI.is_open())
		fileI >> t2;
	fileI.close();
	string path = "key";
	EXPECT_EQ(t2.getValue(path), "value");
}

TEST(test_text, complex_test)
{
	Text t;
	t.addLeft("key1:");
	t.addRight("key2:");
	t.right();
	t.addRight("key21:v1");
	t.addLeft("key3:v2");
	string path1 = "key1.key2.key21";
	string path2 = "key1.key3";
	EXPECT_EQ(t.getValue(path1), "v1");
	EXPECT_EQ(t.getValue(path2), "v2");
	t.remove();
	EXPECT_EQ(t.getValue(path1), "");
	EXPECT_EQ(t.getValue(path2), "v2");
}