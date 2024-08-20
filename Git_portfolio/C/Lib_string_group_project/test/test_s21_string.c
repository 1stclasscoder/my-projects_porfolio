#include <check.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

#define MAX_LEN 100
#define N 20
#define STRERROR_MIN -200
#define STRERROR_MAX 200

void get_strs(char str[N][MAX_LEN]) {
  const char STRS[N][MAX_LEN] = {
      "ETR",        "hTX",    "qWqtQQc", "-fGq@n6uX", "vjlbPei%Nd",
      "-I(ix7C#jw", "FfVa",   "rgTo",    "hZSHK7",    "7b",
      "OD6tr3Pwck", "wRAj",   "ep9(o",   "Sm7B",      "oDB3Py",
      "9Dv@Tr",     "it3VA&", "A",       "T7",        "Z"};

  for (int i = 0; i < N; ++i) {
    strcpy(str[i], STRS[i]);
  }
}

void get_nums(s21_size_t n[N]) {
  const s21_size_t NUMS[N] = {1, 3, 1, 6, 3, 2, 5, 4, 2, 3,
                              1, 1, 2, 1, 4, 3, 7, 2, 3, 0};

  for (int i = 0; i < N; ++i) {
    n[i] = NUMS[i];
  }
}

START_TEST(test_s21_strncmp) {
  const char str1[] = "abcdefg";
  const char str2[] = "abc2222";
  int n1 = 1;

  ck_assert_int_eq(s21_strncmp(str1, str2, n1), strncmp(str1, str2, n1));
  ck_assert_int_eq(s21_strncmp(str2, str1, n1), strncmp(str2, str1, n1));
  int n2 = 4;
  ck_assert_int_eq(s21_strncmp(str2, str1, n2), strncmp(str2, str1, n2));
  ck_assert_int_eq(s21_strncmp(str1, str1, 10), strncmp(str1, str1, 10));
}
END_TEST

START_TEST(test_s21_memset) {
  char str[N][MAX_LEN];
  get_strs(str);
  const char c[] = "AXDH-DiWxlOendnpw)K@";
  s21_size_t n[N];
  get_nums(n);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      for (s21_size_t k = 0; k < N; ++k) {
        ck_assert_ptr_eq(s21_memset(str[i], c[j], (s21_size_t)n[k]),
                         memset(str[i], c[j], (s21_size_t)n[k]));
      }
    }
  }
}
END_TEST

START_TEST(test_s21_strtok) {
  char str[N][MAX_LEN];
  get_strs(str);
  char str21[N][MAX_LEN];
  get_strs(str21);
  const char delim[N][MAX_LEN] = {"RE",    "hXXTh", "WQWQt", "un6Gq", "Ne%NP",
                                  "i-(C-", "aVafF", "oTrrT", "SHKh7", "7bbbb",
                                  "DPOr6", "jRAAA", "9p9oe", "7SSBm", "DyyoP",
                                  "vTT9v", "Ai3iA", "AAAAA", "TTT77", "ZZZZZ"};

  for (s21_size_t i = 0; i < N; ++i) {
    char *token = strtok(str[i], delim[i]);
    char *token21 = s21_strtok(str21[i], delim[i]);

    while (token != s21_NULL && token21 != s21_NULL) {
      ck_assert_str_eq(token, token21);
      token = strtok(s21_NULL, delim[i]);
      token21 = s21_strtok(s21_NULL, delim[i]);
    }
  }
}
END_TEST

START_TEST(test_s21_memcmp) {
  const char *s1 = "This is a 1st string s21_memcmp test";
  const char *s2 = "This is a 2nd string s21_memcmp test";
  ck_assert_int_eq(s21_memcmp(s1, s2, 36), memcmp(s1, s2, 36));
  ck_assert_int_eq(s21_memcmp(s1, s2, 2), memcmp(s1, s2, 2));
  ck_assert_int_eq(s21_memcmp(s1, s2, 0), memcmp(s1, s2, 0));

  const int arr1[] = {1, 2, 3, 4};
  const int arr2[] = {1, 2, 4, 3, 3, 4};
  ck_assert_int_eq(s21_memcmp(arr1, arr2, 2), memcmp(arr1, arr2, 2));
  ck_assert_int_eq(s21_memcmp(arr1, arr2, 4), memcmp(arr1, arr2, 4));

  const long long arr3[] = {1000000, 223445, 5555, -123123, 23232, 333};
  const long long arr4[] = {1000000, 223445, 5555, 3, 4,   44,
                            12,      0,      -3,   4, 9393};
  ck_assert_int_eq(s21_memcmp(arr3, arr4, 3), memcmp(arr3, arr4, 3));
  ck_assert_int_eq(s21_memcmp(arr3, arr4, 1), memcmp(arr3, arr4, 1));
  ck_assert_int_eq(s21_memcmp(arr3, arr4, 5), memcmp(arr3, arr4, 5));

  const unsigned long long arr5[] = {32, 300000, 9999, 933, 3235466};
  const unsigned long long arr6[] = {32, 300000, 9999, 933, 323, 0, -1};
  ck_assert_int_eq(s21_memcmp(arr5, arr6, 3), memcmp(arr5, arr6, 3));
  ck_assert_int_eq(s21_memcmp(arr5, arr6, 1), memcmp(arr5, arr6, 1));
  ck_assert_int_eq(s21_memcmp(arr5, arr6, 5), memcmp(arr5, arr6, 5));
}
END_TEST

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("aaa"), strlen("aaa"));
  ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("1234567890"), strlen("1234567890"));
  ck_assert_int_eq(s21_strlen("bobabbaba"), strlen("bobabbaba"));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char s21_dest[] = "1111111111111", dest[] = "1111111111111";
  int n = 4;
  ck_assert_pstr_eq(s21_strncpy(s21_dest, "123456", n),
                    strncpy(dest, "123456", n));
  ck_assert_str_eq(s21_dest, dest);

  n = 3;
  ck_assert_pstr_eq(s21_strncpy(s21_dest, "chebureki", n),
                    strncpy(dest, "chebureki", n));
  ck_assert_str_eq(s21_dest, dest);

  n = 1;
  ck_assert_pstr_eq(s21_strncpy(s21_dest, "bashkort", n),
                    strncpy(dest, "bashkort", n));
  ck_assert_str_eq(s21_dest, dest);

  n = 0;
  ck_assert_pstr_eq(s21_strncpy(s21_dest, "empty", n),
                    strncpy(dest, "empty", n));
  ck_assert_str_eq(s21_dest, dest);

  n = 10;
  ck_assert_pstr_eq(s21_strncpy(s21_dest, "empty", n),
                    strncpy(dest, "empty", n));
  ck_assert_str_eq(s21_dest, dest);
}
END_TEST

START_TEST(test_s21_strncat) {
  char src[3 * MAX_LEN] = "abcdef";
  char dest[3 * MAX_LEN] = "1234567";
  char s21_dest[3 * MAX_LEN] = "1234567";
  int n = 4;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "2121");
  strcpy(dest, "popstar");
  strcpy(s21_dest, "popstar");
  n = 2;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "pop");
  strcpy(dest, "rockstar");
  strcpy(s21_dest, "rockstar");
  n = 8;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "boba");
  strcpy(dest, "super_sueta");
  strcpy(s21_dest, "super_sueta");
  n = 0;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "iampatsan");
  strcpy(dest, "iamstreet");
  strcpy(s21_dest, "iamstreet");
  n = 4;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "");
  strcpy(dest, "");
  strcpy(s21_dest, "");
  n = 3;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "21$$$");
  strcpy(dest, "school");
  strcpy(s21_dest, "school");
  n = 2;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "unicorn");
  strcpy(dest, "magic");
  strcpy(s21_dest, "magic");
  n = 3;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "pink^^^^");
  strcpy(dest, "eMo_G1rL");
  strcpy(s21_dest, "eMo_G1rL");
  n = 5;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));

  strcpy(src, "___^000000000000");
  strcpy(dest, "^*_");
  strcpy(s21_dest, "^*_");
  n = 3;
  ck_assert_str_eq(s21_strncat(s21_dest, src, n), strncat(dest, src, n));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str[N][MAX_LEN];
  get_strs(str);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      ck_assert_int_eq(s21_strcspn(str[i], str[j]), strcspn(str[i], str[j]));
    }
  }
}
END_TEST

START_TEST(test_s21_strchr) {
  char str[N][MAX_LEN];
  get_strs(str);
  const char c[] = "AXDH-DiWxlOendnpw)K@";

  for (s21_size_t i = 0; i < N; ++i) {
    ck_assert_pstr_eq(s21_strchr(str[i], c[i]), strchr(str[i], c[i]));
  }
}
END_TEST

START_TEST(test_s21_strrchr) {
  char str[N][MAX_LEN];
  get_strs(str);
  const char c[] = "AXDH-DiWxlOendnpw)K@";

  for (s21_size_t i = 0; i < N; ++i) {
    ck_assert_pstr_eq(s21_strrchr(str[i], c[i]), strrchr(str[i], c[i]));
  }
}
END_TEST

START_TEST(test_s21_memcpy) {
  char str[N][MAX_LEN];
  get_strs(str);
  char dest[N][MAX_LEN];
  s21_size_t n[N];
  get_nums(n);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      ck_assert_ptr_eq(s21_memcpy(dest[i], str[i], n[j]),
                       memcpy(dest[i], str[i], n[j]));
    }
  }
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str[N][MAX_LEN];
  get_strs(str);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      ck_assert_pstr_eq(s21_strpbrk(str[i], str[j]), strpbrk(str[i], str[j]));
    }
  }
}
END_TEST

START_TEST(test_s21_strstr) {
  char str[N][MAX_LEN];
  get_strs(str);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      ck_assert_pstr_eq(s21_strstr(str[i], str[j]), strstr(str[i], str[j]));
    }
  }
}
END_TEST

START_TEST(test_s21_memchr) {
  char str[N][MAX_LEN];
  get_strs(str);
  const char c[] = "AXDH-DiWxlOendnpw)K@";
  s21_size_t n[N];
  get_nums(n);

  for (s21_size_t i = 0; i < N; ++i) {
    for (s21_size_t j = 0; j < N; ++j) {
      ck_assert_ptr_eq(s21_memchr(str[i], c[j], n[i]),
                       memchr(str[i], c[j], n[i]));
    }
  }
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int num = STRERROR_MIN; num <= STRERROR_MAX; ++num) {
    ck_assert_str_eq(s21_strerror(num), strerror(num));
  }
}
END_TEST

START_TEST(test_s21_sprintf) {
  char str[MAX_LEN] = {0}, s21_str[MAX_LEN] = {0};
  const char *s = "Hello, s21_string!";

  ck_assert_int_eq(sprintf(str, "test"), s21_sprintf(s21_str, "test"));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, " padding: "),
                   s21_sprintf(s21_str, " padding: "));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "[%60s]", s),
                   s21_sprintf(s21_str, "[%60s]", s));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "[%-60s]", s),
                   s21_sprintf(s21_str, "[%-60s]", s));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, " truncating: "),
                   s21_sprintf(s21_str, " truncating: "));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%.4s", s), s21_sprintf(s21_str, "%.4s", s));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "Characters: %c %%", 'A'),
                   s21_sprintf(s21_str, "Characters: %c %%", 'A'));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "Floating point:"),
                   s21_sprintf(s21_str, "Floating point:"));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(
      sprintf(str, "Rounding: %f %.0f %.11f", 1.5, 1.5, 1.3),
      s21_sprintf(s21_str, "Rounding: %f %.0f %.11f", 1.5, 1.5, 1.3));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(
      sprintf(str, "Padding: %05.2f %.2f %5.2f", 1.5, 1.5, 1.5),
      s21_sprintf(s21_str, "Padding: %05.2f %.2f %5.2f", 1.5, 1.5, 1.5));
  ck_assert_str_eq(str, s21_str);

  int a = 10;
  int b = -122;
  char c = '&';
  double d = 0.003;
  unsigned e = 44221;
  const char f[] = "hello,   s21_string!!!";

  ck_assert_int_eq(sprintf(str, "%c%u", c, e),
                   s21_sprintf(s21_str, "%c%u", c, e));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%c[%10f]%+d", c, d, a),
                   s21_sprintf(s21_str, "%c[%10f]%+d", c, d, a));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%d%s", b, f),
                   s21_sprintf(s21_str, "%d%s", b, f));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "Decimal: %i %.0d %.6d %i %.0i %+i %i", 1, 0, 3,
                           0, 0, 4, -4),
                   s21_sprintf(s21_str, "Decimal: %i %.0d %.6d %i %.0i %+i %i",
                               1, 0, 3, 0, 0, 4, -4));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(
      sprintf(str, "Hexadecimal: %x %x %X %#x", 5, 10, 10, 6),
      s21_sprintf(s21_str, "Hexadecimal: %x %x %X %#x", 5, 10, 10, 6));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "Octal: %o %#o %#o", 10, 10, 4),
                   s21_sprintf(s21_str, "Octal: %o %#o %#o", 10, 10, 4));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "[%*s]", 10, s),
                   s21_sprintf(s21_str, "[%*s]", 10, s));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%.*s", 3, s),
                   s21_sprintf(s21_str, "%.*s", 3, s));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%2.0f", 20.0003),
                   s21_sprintf(s21_str, "%2.0f", 20.0003));
  ck_assert_str_eq(str, s21_str);

  unsigned int x = 2;
  ck_assert_int_eq(sprintf(str, "%u", x), s21_sprintf(s21_str, "%u", x));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%lf", -2.0),
                   s21_sprintf(s21_str, "%lf", -2.0));
  ck_assert_str_eq(str, s21_str);

  const char *roma = "romaGoodbye";
  ck_assert_int_eq(sprintf(str, "%p", roma), s21_sprintf(s21_str, "%p", roma));
  ck_assert_str_eq(str, s21_str);

  ck_assert_int_eq(sprintf(str, "%f", 0.0), s21_sprintf(s21_str, "%f", 0.0));
  ck_assert_str_eq(str, s21_str);
}
END_TEST

START_TEST(test_s21_to_lower) {
  ck_assert_pstr_eq(s21_to_lower(s21_NULL), s21_NULL);

  const char *src1 = "$AokL*lll";
  char *res1_21 = (char *)s21_to_lower(src1);
  const char *res1 = "$aokl*lll";
  ck_assert_str_eq(res1_21, res1);
  if (res1_21) {
    free(res1_21);
  }

  const char *src2 = "*******";
  char *res2_21 = (char *)s21_to_lower(src2);
  const char *res2 = "*******";
  ck_assert_str_eq(res2_21, res2);
  if (res2_21) {
    free(res2_21);
  }

  const char *src3 = "SSSSSSS";
  char *res3_21 = (char *)s21_to_lower(src3);
  const char *res3 = "sssssss";
  ck_assert_str_eq(res3_21, res3);
  if (res3_21) {
    free(res3_21);
  }

  const char *src4 = "ZARA";
  char *res4_21 = (char *)s21_to_lower(src4);
  const char *res4 = "zara";
  ck_assert_str_eq(res4_21, res4);
  if (res4_21) {
    free(res4_21);
  }
}
END_TEST

START_TEST(test_s21_to_upper) {
  ck_assert_pstr_eq(s21_to_upper(s21_NULL), s21_NULL);

  const char *src1 = "$aokl*lll";
  char *res1_21 = (char *)s21_to_upper(src1);
  const char *res1 = "$AOKL*LLL";
  ck_assert_str_eq(res1_21, res1);
  if (res1_21) {
    free(res1_21);
  }

  const char *src2 = "*******";
  char *res2_21 = (char *)s21_to_upper(src2);
  const char *res2 = "*******";
  ck_assert_str_eq(res2_21, res2);
  if (res2_21) {
    free(res2_21);
  }

  const char *src3 = "sssssss";
  char *res3_21 = (char *)s21_to_upper(src3);
  const char *res3 = "SSSSSSS";
  ck_assert_str_eq(res3_21, res3);
  if (res3_21) {
    free(res3_21);
  }

  const char *src4 = "zara";
  char *res4_21 = (char *)s21_to_upper(src4);
  const char *res4 = "ZARA";
  ck_assert_str_eq(res4_21, res4);
  if (res4_21) {
    free(res4_21);
  }
}
END_TEST

START_TEST(test_s21_insert) {
  const char *src1 = "12345";
  int n1 = 3;
  const char *str1 = "aaa";
  char *res1 = "123aaa45";
  char *res1_21 = (char *)s21_insert(src1, str1, n1);
  ck_assert_str_eq(res1, res1_21);
  if (res1_21) {
    free(res1_21);
  }

  int n2 = -1;
  char *res2_21 = (char *)s21_insert(src1, str1, n2);
  ck_assert_ptr_eq(res2_21, s21_NULL);
  if (res2_21) {
    free(res2_21);
  }
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("s21_string");
  TCase *tc1_1 = tcase_create("s21_string");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_s21_strncmp);
  tcase_add_test(tc1_1, test_s21_memset);
  tcase_add_test(tc1_1, test_s21_strtok);
  tcase_add_test(tc1_1, test_s21_memcmp);
  tcase_add_test(tc1_1, test_s21_strlen);
  tcase_add_test(tc1_1, test_s21_strncpy);
  tcase_add_test(tc1_1, test_s21_strncat);
  tcase_add_test(tc1_1, test_s21_strcspn);
  tcase_add_test(tc1_1, test_s21_strchr);
  tcase_add_test(tc1_1, test_s21_strrchr);
  tcase_add_test(tc1_1, test_s21_memcpy);
  tcase_add_test(tc1_1, test_s21_strpbrk);
  tcase_add_test(tc1_1, test_s21_strstr);
  tcase_add_test(tc1_1, test_s21_memchr);
  tcase_add_test(tc1_1, test_s21_strerror);
  tcase_add_test(tc1_1, test_s21_sprintf);
  tcase_add_test(tc1_1, test_s21_to_lower);
  tcase_add_test(tc1_1, test_s21_to_upper);
  tcase_add_test(tc1_1, test_s21_insert);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
