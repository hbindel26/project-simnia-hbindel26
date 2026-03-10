#include "strvec.h"
#include "acutest.h"

void test_init(void)
{
	strvec v;
	strvec_init(&v);
	TEST_CHECK(strvec_size(v) == 0);
	TEST_CHECK(strvec_capacity(v) == 4);
	strvec_free(&v);
}

void test_add_good(void)
{
	strvec v;
	strvec_init(&v);
	strvec_push(&v, "asdf");
	TEST_CHECK(strvec_size(v) == 1);
	TEST_CHECK(strcmp(strvec_get(v, 0), "asdf") == 0);

	strvec_push(&v, "qwerty");
	TEST_CHECK(strvec_size(v) == 2);
	TEST_CHECK(strcmp(strvec_get(v, 1), "qwerty") == 0);
	TEST_CHECK(strvec_capacity(v) == 4);

	strvec_push(&v, "dvorak");
	TEST_CHECK(strvec_size(v) == 3);
	TEST_CHECK(strcmp(strvec_get(v, 2), "dvorak") == 0);

	strvec_push(&v, "a");
	TEST_CHECK(strvec_size(v) == 4);
	TEST_CHECK(strcmp(strvec_get(v, 3), "a") == 0);
	TEST_CHECK(strvec_capacity(v) == 8);
	strvec_free(&v);
}

void test_get_bad(void)
{
	strvec v;
	strvec_init(&v);

	TEST_CHECK(strvec_get(v, 0) == NULL);
	strvec_push(&v, "a");
	TEST_CHECK(strvec_get(v, 1) == NULL);

	strvec_free(&v);
}

TEST_LIST = {
	{"init", test_init},
	{"add", test_add_good},
	{"get_bad", test_get_bad},

	{NULL, NULL}
};
