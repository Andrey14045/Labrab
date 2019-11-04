#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(15);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v(5);
	TVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(5);
	TVector<int> v1(v);
	v[4] = 1;
	v1[4] = 0;
	EXPECT_NE(v, v1);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);

	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[-1] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[6] = 1);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int>  v(5);
	TVector<int> v1(5);
	for (int i = 0; i < v.GetSize(); i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int>  v(5);
	TVector<int> v1(5);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(5), v1(10);
	v = v1;
	EXPECT_EQ(v.GetSize(), v1.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int>  v(5);
	TVector<int> v1(10);
	TVector<int> v2(5);
	for (int i = 0; i < v.GetSize(); i++)
	{
		v[i] = i;
		v2[i] = i;
	}
	v1 = v;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int>  v(5);
	TVector<int> v1(5);
	for (int i = 0; i < v.GetSize(); i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	EXPECT_EQ(true, v == v1);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int>  v(5);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	EXPECT_EQ(true, v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int>  v(5);
	TVector<int> v1(10);
	EXPECT_NE(v, v1);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	v = v + 5;
	ASSERT_NO_THROW(v);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	v = v - 5;
	ASSERT_NO_THROW(v);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	v = v * 5;
	ASSERT_NO_THROW(v);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(2);
	TVector<int> v2(2);
	TVector<int> v3(2);
	v[0] = 1;
	v[1] = 2;

	v1[0] = 5;
	v1[1] = 7;

	v2[0] = 6;
	v2[1] = 9;

	v3 = v + v1;

	EXPECT_EQ(v3, v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(3);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	ASSERT_ANY_THROW(v + v1);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(2);
	TVector<int> v2(2);
	TVector<int> v3(2);
	v[0] = 5;
	v[1] = 8;

	v1[0] = 3;
	v1[1] = 4;

	v2[0] = 2;
	v2[1] = 4;

	v3 = v - v1;

	EXPECT_EQ(v3, v2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(5);
	TVector<int> v1(10);
	for (int i = 0; i < v.GetSize(); i++)
		v[i] = i;
	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	ASSERT_ANY_THROW(v - v1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(2);
	int mltpl;
	v[0] = 6;
	v[1] = 8;

	v1[0] = 7;
	v1[1] = 1;

	mltpl = v * v1;

	EXPECT_EQ(50, mltpl); //6*7 + 8*1=50
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(3);
	int mltpl;
	v[0] = 5;
	v[1] = 8;

	v1[0] = 3;
	v1[1] = 4;
	v1[2] = 5;

	ASSERT_ANY_THROW(v * v1);
}
