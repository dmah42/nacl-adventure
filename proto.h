#ifdef __STDC__
# define	P(s) s
#else
# define P(s) ()
#endif


/* advent.c */
/*      37 */ int main P((int argc , char **argv ));
/*      89 */ void scanint P((int *pi , char *str ));
/*     106 */ void initplay P((void ));
/*     180 */ void opentxt P((void ));
/*     207 */ void saveadv P((void ));
/*     244 */ void restore P((void ));
char *game_name P((char *username));

/* database.c */
/*      25 */ void gettrav P((int loc ));
/*      62 */ int rdupto P((FILE *fdi , int uptoc , int print , char *string ));
/*      89 */ void rdskip P((FILE *fdi , int skipc , int n , int rewind ));
/*     108 */ int yes P((int msg1 , int msg2 , int msg3, void (*yes_result)(int)));
/*     130 */ void rspeak P((int msg ));
/*     147 */ void pspeak P((int item , int state ));
/*     158 */ void desclg P((int loc ));
/*     168 */ void descsh P((int loc ));
/*     184 */ int vocab P((char *word , int val ));
/*     208 */ int binary P((char *w , struct wac wctable [], int maxwc ));
/*     237 */ int dark P((void ));
/*     247 */ int here P((int item ));
/*     256 */ int toting P((int item ));
/*     266 */ int forced P((int atloc ));
/*     275 */ int pct P((int x ));
/*     285 */ int at P((int item ));
/*     294 */ void dstroy P((int obj ));
/*     303 */ void move P((int obj , int where ));
/*     318 */ void juggle P((int loc ));
/*     326 */ void carry P((int obj , int where ));
/*     340 */ void drop P((int obj , int where ));
/*     357 */ int put P((int obj , int where , int pval ));
/*     367 */ int dcheck P((void ));
/*     380 */ int liq P((void ));
/*     391 */ int liqloc P((int loc ));
/*     405 */ int liq2 P((int pbottle ));
/*     414 */ void bug P((int n ));

/* english.c */
              void english P((void (*english_result)(int)));
/*     100 */ int analyze P((char *word , int *type , int *value ));
              int getwords P((void (*words_callback)()));
/*     150 */ void outwords P((void ));

/* itverb.c */
/*      16 */ void itverb P((void ));
/*      91 */ void ivtake P((void ));
/*     116 */ void ivopen P((void ));
/*     143 */ void ivkill P((void ));
/*     177 */ void iveat P((void ));
/*     193 */ void ivdrink P((void ));
/*     207 */ void ivquit P((void ));
/*     213 */ void ivfill P((void ));
/*     231 */ void ivfoo P((void ));
/*     288 */ void inventory P((void ));
/*     312 */ void addobj P((int obj ));

/* turn.c */
/*      18 */ void turn P((void (*callback)(void) ));
/*     116 */ void describe P((void ));
/*     133 */ void descitem P((void ));
/*     165 */ void domove P((void ));
/*     199 */ void goback P((void ));
/*     242 */ void copytrv P((struct trav *trav1 , struct trav *trav2 ));
/*     258 */ void dotrav P((void ));
/*     326 */ void badmove P((void ));
/*     344 */ void spcmove P((int rdest ));
/*     396 */ void dwarfend P((void ));
/*     405 */ void normend P((void ));
/*     414 */ void score P((void ));
/*     467 */ void death P((void ));
/*     499 */ void doobj P((void ));
/*     560 */ void trobj P((void ));
/*     572 */ char *probj P((int object ));
/*     581 */ void dwarves P((void ));
/*     688 */ void dopirate P((void ));
/*     742 */ int stimer P((void ));

/* verb.c */
/*      16 */ void trverb P((void ));
/*     106 */ void vtake P((void ));
/*     182 */ void vdrop P((void ));
/*     271 */ void vopen P((void ));
/*     357 */ void vsay P((void ));
/*     368 */ void von P((void ));
/*     387 */ void voff P((void ));
/*     400 */ void vwave P((void ));
/*     417 */ void vkill P((void ));
/*     484 */ void vpour P((void ));
/*     523 */ void veat P((void ));
/*     546 */ void vdrink P((void ));
/*     562 */ void vthrow P((void ));
/*     658 */ void vfind P((void ));
/*     681 */ void vfill P((void ));
/*     721 */ void vfeed P((void ));
/*     780 */ void vread P((void ));
/*     816 */ void vblast P((void ));
/*     834 */ void vbreak P((void ));
/*     861 */ void vwake P((void ));
/*     874 */ void actspk P((int verb ));
/*     891 */ void needobj P((void ));

#undef P
