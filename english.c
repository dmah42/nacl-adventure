
/*	program ENGLISH.C					*\
\*	WARNING: "advent.c" allocates GLOBAL storage space by	*\
\*		including "advdef.h".				*\
\*		All other modules use "advdec.h".		*/


#include	<stdio.h>	/* drv = 1.1st file 2.def 3.A	*/
#include	"advent.h"
#include	"advdec.h"
#include  "io.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define atoi atol
#define rindex strchr

#ifdef NATIVE_CLIENT
void WaitForInput(int (*input_cb)(const char*, void*, void*),
                  void* a, void* b);
#endif

/*
	Analyze a two word sentence
*/

void (*english_result_)(int) = NULL;

void complete_english() {
	char* msg = "bad grammar...";
	int	type1, type2, val1, val2;
	verb = object = motion = 0;
	type2 = val2 = -1;
	type1 = val1 = -1;

	if (!(*word1))
		return english_result_(0);		/* ignore whitespace	*/
	if (!analyze(word1, &type1, &val1))	/* check word1	*/
		return english_result_(0);		/* didn't know it	*/

	if (type1 == 2 && val1 == SAY) {
		verb = SAY;	/* repeat word & act upon if..	*/
		object = 1;
		return english_result_(1);
	}

	if (*word2)
		if (!analyze(word2, &type2, &val2))
			return english_result_(0);	/* didn't know it	*/

	/* check his grammar */
	if ((type1 == 3) && (type2 == 3) && \
	    (val1 == 51) && (val2 == 51)) {
		outwords();
		return english_result_(0);
	}
	else if (type1 == 3) {
		rspeak(val1);
		return english_result_(0);
	}
	else if (type2 == 3) {
		rspeak(val2);
		return english_result_(0);
	}
	else if (type1 == 0) {
		if (type2 == 0) {
			screen_printf("%s\n", msg);
			return english_result_(0);
		}
		else
			motion = val1;
	}
	else if (type2 == 0)
		motion = val2;
	else if (type1 == 1) {
		object = val1;
		if (type2 == 2)
			verb = val2;
		if (type2 == 1) {
			screen_printf("%s\n", msg);
			return english_result_(0);
		}
	}
	else if (type1 == 2) {
		verb = val1;
		if (type2 == 1)
			object = val2;
		if (type2 == 2) {
			screen_printf("%s\n", msg);
			return english_result_(0);
		}
	}
	else
		bug(36);
	return english_result_(1);
}

void english(void (*english_result)(int))
{
  english_result_ = english_result;
	getwords(complete_english);
}

/*
		Routine to analyze a word.
*/
int analyze(char* word, int* type, int* value)
{
	int	wordval, msg;

	/* make sure I understand */
	if ((wordval = vocab(word, 0)) == -1) {
		switch(rand() % 3) {
		case 0:
			msg = 60;
			break;
		case 1:
			msg = 61;
			break;
		default:
			msg = 13;
		}
		rspeak(msg);
		return(0);
	}
	*type = wordval/1000;
	*value = wordval%1000;
	return(1);
}

/*
	retrieve input line (max 80 chars), convert to lower case
	 & rescan for first two words (max. MAXCOMMANDSIZE-1 chars).
*/

void (*words_callback_)() = NULL;

int getwords_complete(const char* words, void* a, void* b) {
	char *wptr = (char*) words;
	while ((*wptr = tolower(*wptr)))
		++wptr;
	sscanf(words, "%19s %19s", word1, word2);
	if (dbugflg)
		console_printf("WORD1 = %s, WORD2 = %s\n", word1, word2);
  words_callback_();
  return 0;
}

int getwords(void (*words_callback)()) {
	word1[0] = word2[0] = '\0';
  words_callback_ = words_callback;
#ifdef NATIVE_CLIENT
  screen_printf("> ");
  WaitForInput(getwords_complete, NULL, NULL);
#else
	char	words[80];
	fputc('>', stdout);
	fgets(words, 80, stdin);
  getwords_complete(words);
#endif
  return 0;
}

/*
	output adventure word list (motion/0xxx & verb/2xxx) only
	6 words/line pausing at 20th line until keyboard active
*/
void outwords()
{
	int	i, j, line;
	char	words[80];

	j = line = 0;
	for (i = 0; i < MAXWC; ++i) {
		if ((wc[i].acode < 1000) || ((wc[i].acode < 3000) && \
		                             (wc[i].acode > 1999))) {
			screen_printf("%-12s", wc[i].aword);
			if ((++j == 6) || (i == MAXWC-1)) {
				j = 0;
				fputc('\n', stdout);
				if (++line == 20) {
					line = 0;
					screen_printf("\n\007Enter <RETURN>");
					screen_printf(" to continue\n\n");
					fgets(words, 80, stdin);
				}
			}
		}
	}
}


