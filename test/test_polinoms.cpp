#include "Polinom.h"

#include <gtest.h>


TEST(test_list, create_list)
{
	ASSERT_NO_THROW(LinkList<int> l);
}

TEST(test_list, empty_list)
{
	LinkList<int> l;
	ASSERT_ANY_THROW(l.getFirst());
}

TEST(test_list, add_first)
{
	LinkList<int> l;
	l.addFirst(0);
	l.addFirst(1);
	EXPECT_EQ(1, l.getFirst());
	EXPECT_EQ(0, l.getLast());
}

TEST(test_list, add_last)
{
	LinkList<int> l;
	l.addFirst(0);
	l.addLast(1);
	EXPECT_EQ(0, l.getFirst());
	EXPECT_EQ(1, l.getLast());
}

TEST(test_list, remove_first)
{
	LinkList<int> l;
	l.addFirst(0);
	l.addFirst(1);
	l.removeFirst();
	EXPECT_EQ(0, l.getFirst());
}

TEST(test_list, copy)
{
	LinkList<int> l1;
	l1.addFirst(0);
	l1.addFirst(1);
	LinkList<int> l2(l1);
	l2.removeFirst();
	EXPECT_EQ(1, l1.getFirst());
	EXPECT_EQ(0, l2.getFirst());
}



TEST(test_list_iterator, create_iterator)
{
	LinkList<int> l;
	ASSERT_NO_THROW(l.begin());
}

TEST(test_list_iterator, simple_iterator)
{
	LinkList<int> l;
	for (int i = 0; i < 5; i++)
		l.addLast(i);
	Iterator<int> iter = l.begin();
	int i = 0;
	while (iter.hasNext())
	{
		EXPECT_EQ(i, iter.next());
		i++;
	}
	EXPECT_EQ(5, i);
}



TEST(test_monom, create_monom_cd)
{
	ASSERT_NO_THROW(Monom m(1, compressedDegrees(201)));
}

TEST(test_monom, create_monom_fd)
{
	ASSERT_NO_THROW(Monom m(1, fullDegrees(1, 1, 1)));
}

TEST(test_monom, monom_is_right)
{
	Monom m(2, fullDegrees(1, 1, 2));
	EXPECT_DOUBLE_EQ(1470., m.getValue(3., 5., 7.));
}

TEST(test_monom, check_ADD)
{
	Monom m1(2, fullDegrees(1, 1, 2));
	Monom m2(1, fullDegrees(1, 1, 2));
	Monom m3 = m1 + m2;
	EXPECT_DOUBLE_EQ(2205., m3.getValue(3., 5., 7.));

}

TEST(test_monom, check_MUL)
{
	Monom m1(2, fullDegrees(1, 1, 2));
	Monom m2(1, fullDegrees(2, 1, 1));
	Monom m3 = m1 * m2;
	EXPECT_DOUBLE_EQ(463050., m3.getValue(3., 5., 7.));
}

TEST(test_monom, copy)
{
	Monom m1(2, fullDegrees(1, 1, 2));
	Monom m2(m1);
	EXPECT_DOUBLE_EQ(1470., m2.getValue(3., 5., 7.));
}



TEST(test_polinom, create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}

TEST(test_polinom, polinom_is_right)
{
	Polinom p;
	p += Monom(2, fullDegrees(1, 1, 2));
	p += Monom(1, fullDegrees(2, 1, 1));
	EXPECT_DOUBLE_EQ(1785., p.getValue(3., 5., 7.));
}

TEST(test_polinom, copy)
{
	Polinom p1;
	p1 += Monom(2, fullDegrees(1, 1, 2));
	p1 += Monom(1, fullDegrees(2, 1, 1));
	Polinom p2(p1);
	EXPECT_DOUBLE_EQ(1785., p2.getValue(3., 5., 7.));
}
