#ifdef _cplusplus
extern "C" {
#endif

#ifndef LOCALE_H
#define LOCALE_H

#define LC_COLLATE	1
#define LC_CTYPE	2
#define LC_MONETARY	4
#define LC_NUMERIC	8
#define LC_TIME	16
#define LC_ALL	(LC_COLLATE | LC_CTYPE | LC_MONETARY | LC_NUMERIC | LC_TIME)

struct lconv {
	char *decimal_point;
	char *thousands_sep;
	char *grouping;	
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
};

char *setlocale(int category, const char *locale);
struct lconv *localeconv(void);

#endif

#ifdef _cplusplus
}
#endif
