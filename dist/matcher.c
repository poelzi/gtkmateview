
#include "matcher.h"
#include <gee/collection.h>
#include "string_helper.h"




enum  {
	GTK_MATE_MATCHER_DUMMY_PROPERTY
};
static gint gtk_mate_matcher_sorted_ix (GeeArrayList* ixs, gint val);
static gpointer gtk_mate_matcher_parent_class = NULL;
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



gint gtk_mate_matcher_compare_match (const char* scope_string, OnigurumaMatch* m1, OnigurumaMatch* m2) {
	GeeArrayList* space_ixs;
	gint max_cap1;
	gint max_cap2;
	gint cap1_ix;
	gint cap1_el_ix;
	gint len1;
	gint cap2_ix;
	gint cap2_el_ix;
	gint len2;
	gint _tmp4;
	g_return_val_if_fail (scope_string != NULL, 0);
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (m1), 0);
	g_return_val_if_fail (ONIGURUMA_IS_MATCH (m2), 0);
	space_ixs = string_helper_occurrences (scope_string, " ");
	/* foreach (var ix in space_ixs)
	 stdout.printf("space at %d\n", ix);*/
	max_cap1 = oniguruma_match_num_captures (m1);
	max_cap2 = oniguruma_match_num_captures (m2);
	/* stdout.printf("m1 has %d matches\n", m1.num_captures());
	 stdout.printf("m2 has %d matches\n", m2.num_captures());*/
	cap1_ix = 0;
	cap1_el_ix = 0;
	len1 = 0;
	cap2_ix = 0;
	cap2_el_ix = 0;
	len2 = 0;
	{
		gint i;
		i = 0;
		for (; i < MIN (max_cap1, max_cap2); i++) {
			/* first try element depth:*/
			cap1_ix = oniguruma_match_begin (m1, max_cap1 - 1 - i);
			cap2_ix = oniguruma_match_begin (m2, max_cap2 - 1 - i);
			/* stdout.printf("m1 capture %d at %d\n", max_cap1-1-i, cap1_ix);
			 stdout.printf("m2 capture %d at %d\n", max_cap2-1-i, cap2_ix);*/
			cap1_el_ix = gtk_mate_matcher_sorted_ix (space_ixs, cap1_ix);
			cap2_el_ix = gtk_mate_matcher_sorted_ix (space_ixs, cap2_ix);
			/* stdout.printf("m1 capture %d at el %d\n", max_cap1-1-i, cap1_el_ix);
			 stdout.printf("m2 capture %d at el %d\n", max_cap2-1-i, cap2_el_ix);*/
			if (cap1_el_ix > cap2_el_ix) {
				gint _tmp0;
				return (_tmp0 = 1, (space_ixs == NULL ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL))), _tmp0);
			} else {
				if (cap1_el_ix < cap2_el_ix) {
					gint _tmp1;
					return (_tmp1 = -1, (space_ixs == NULL ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL))), _tmp1);
				}
			}
			/* next try length of match*/
			len1 = oniguruma_match_end (m1, max_cap1 - 1 - i) - cap1_ix;
			len2 = oniguruma_match_end (m2, max_cap2 - 1 - i) - cap2_ix;
			if (len1 > len2) {
				gint _tmp2;
				return (_tmp2 = 1, (space_ixs == NULL ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL))), _tmp2);
			} else {
				if (len1 < len2) {
					gint _tmp3;
					return (_tmp3 = -1, (space_ixs == NULL ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL))), _tmp3);
				}
			}
		}
	}
	return (_tmp4 = 0, (space_ixs == NULL ? NULL : (space_ixs = (g_object_unref (space_ixs), NULL))), _tmp4);
}


static gint gtk_mate_matcher_sorted_ix (GeeArrayList* ixs, gint val) {
	g_return_val_if_fail (GEE_IS_ARRAY_LIST (ixs), 0);
	if (gee_collection_get_size (GEE_COLLECTION (ixs)) == 0) {
		return 0;
	}
	if (val < GPOINTER_TO_INT (gee_list_get (((GeeList*) (ixs)), 0))) {
		return 0;
	}
	{
		gint i;
		i = 0;
		for (; i < gee_collection_get_size (GEE_COLLECTION (ixs)); i++) {
			if (val > GPOINTER_TO_INT (gee_list_get (((GeeList*) (ixs)), i))) {
				return i + 1;
			}
		}
	}
	return gee_collection_get_size (GEE_COLLECTION (ixs));
}


/* this method is mainly for testing in the Ruby specs*/
char* gtk_mate_matcher_test_rank (const char* selector_a, const char* selector_b, const char* scope_string) {
	OnigurumaMatch* m1;
	OnigurumaMatch* m2;
	OnigurumaMatch* _tmp2;
	gboolean _tmp1;
	OnigurumaMatch* _tmp0;
	OnigurumaMatch* _tmp5;
	gboolean _tmp4;
	OnigurumaMatch* _tmp3;
	gint r;
	g_return_val_if_fail (selector_a != NULL, NULL);
	g_return_val_if_fail (selector_b != NULL, NULL);
	g_return_val_if_fail (scope_string != NULL, NULL);
	m1 = NULL;
	m2 = NULL;
	_tmp2 = NULL;
	_tmp0 = NULL;
	_tmp1 = gtk_mate_matcher_match (selector_a, scope_string, &_tmp0);
	m1 = (_tmp2 = _tmp0, (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), _tmp2);
	_tmp1;
	_tmp5 = NULL;
	_tmp3 = NULL;
	_tmp4 = gtk_mate_matcher_match (selector_b, scope_string, &_tmp3);
	m2 = (_tmp5 = _tmp3, (m2 == NULL ? NULL : (m2 = (g_object_unref (m2), NULL))), _tmp5);
	_tmp4;
	r = gtk_mate_matcher_compare_match (scope_string, m1, m2);
	if (r > 0) {
		const char* _tmp6;
		char* _tmp7;
		_tmp6 = NULL;
		_tmp7 = NULL;
		return (_tmp7 = (_tmp6 = selector_a, (_tmp6 == NULL ? NULL : g_strdup (_tmp6))), (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), (m2 == NULL ? NULL : (m2 = (g_object_unref (m2), NULL))), _tmp7);
	} else {
		if (r == 0) {
			char* _tmp8;
			char* _tmp9;
			char* _tmp10;
			_tmp8 = NULL;
			_tmp9 = NULL;
			_tmp10 = NULL;
			return (_tmp10 = (_tmp9 = g_strconcat ((_tmp8 = g_strconcat (selector_a, " == ", NULL)), selector_b, NULL), (_tmp8 = (g_free (_tmp8), NULL)), _tmp9), (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), (m2 == NULL ? NULL : (m2 = (g_object_unref (m2), NULL))), _tmp10);
		} else {
			const char* _tmp11;
			char* _tmp12;
			_tmp11 = NULL;
			_tmp12 = NULL;
			return (_tmp12 = (_tmp11 = selector_b, (_tmp11 == NULL ? NULL : g_strdup (_tmp11))), (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), (m2 == NULL ? NULL : (m2 = (g_object_unref (m2), NULL))), _tmp12);
		}
	}
	(m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL)));
	(m2 == NULL ? NULL : (m2 = (g_object_unref (m2), NULL)));
}


gboolean gtk_mate_matcher_test_match (const char* selector_string, const char* scope_string) {
	OnigurumaMatch* m;
	OnigurumaMatch* _tmp2;
	gboolean _tmp1;
	OnigurumaMatch* _tmp0;
	gboolean _tmp3;
	g_return_val_if_fail (selector_string != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	m = NULL;
	_tmp2 = NULL;
	_tmp0 = NULL;
	return (_tmp3 = (_tmp1 = gtk_mate_matcher_match (selector_string, scope_string, &_tmp0), m = (_tmp2 = _tmp0, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp2), _tmp1), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp3);
}


gboolean gtk_mate_matcher_match (const char* selector_string, const char* scope_string, OnigurumaMatch** match) {
	char** _tmp0;
	gint scope_ors1_length1;
	char** scope_ors1;
	gboolean _tmp12;
	g_return_val_if_fail (selector_string != NULL, FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	(*match) = NULL;
	/* FIXME should validate and throw UTF8 error if bad.*/
	_tmp0 = NULL;
	scope_ors1 = (_tmp0 = g_strsplit (selector_string, ",", 0), scope_ors1_length1 = -1, _tmp0);
	{
		char** selector_string1_collection;
		int selector_string1_collection_length1;
		int selector_string1_it;
		selector_string1_collection = scope_ors1;
		selector_string1_collection_length1 = scope_ors1_length1;
		for (selector_string1_it = 0; (scope_ors1_length1 != -1 && selector_string1_it < scope_ors1_length1) || (scope_ors1_length1 == -1 && selector_string1_collection[selector_string1_it] != NULL); selector_string1_it = selector_string1_it + 1) {
			const char* _tmp11;
			char* selector_string1;
			_tmp11 = NULL;
			selector_string1 = (_tmp11 = selector_string1_collection[selector_string1_it], (_tmp11 == NULL ? NULL : g_strdup (_tmp11)));
			{
				OnigurumaRegex* pos_rx;
				GeeArrayList* neg_rxs;
				char** _tmp1;
				gint positives_and_negatives_length1;
				char** positives_and_negatives;
				OnigurumaMatch* _tmp9;
				gboolean _tmp8;
				OnigurumaMatch* _tmp7;
				pos_rx = NULL;
				neg_rxs = gee_array_list_new (ONIGURUMA_TYPE_REGEX, ((GBoxedCopyFunc) (g_object_ref)), g_object_unref, g_direct_equal);
				_tmp1 = NULL;
				positives_and_negatives = (_tmp1 = g_strsplit (selector_string1, "-", 0), positives_and_negatives_length1 = -1, _tmp1);
				{
					char** sub_selector_string_collection;
					int sub_selector_string_collection_length1;
					int sub_selector_string_it;
					sub_selector_string_collection = positives_and_negatives;
					sub_selector_string_collection_length1 = positives_and_negatives_length1;
					for (sub_selector_string_it = 0; (positives_and_negatives_length1 != -1 && sub_selector_string_it < positives_and_negatives_length1) || (positives_and_negatives_length1 == -1 && sub_selector_string_collection[sub_selector_string_it] != NULL); sub_selector_string_it = sub_selector_string_it + 1) {
						const char* _tmp6;
						char* sub_selector_string;
						_tmp6 = NULL;
						sub_selector_string = (_tmp6 = sub_selector_string_collection[sub_selector_string_it], (_tmp6 == NULL ? NULL : g_strdup (_tmp6)));
						{
							if (pos_rx == NULL) {
								char* s1;
								char* s2;
								OnigurumaRegex* _tmp4;
								char* _tmp3;
								char* _tmp2;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ").*(");
								/* stdout.printf("positive '%s' -> '%s'\n", selector_string, "("+s2+")");*/
								_tmp4 = NULL;
								_tmp3 = NULL;
								_tmp2 = NULL;
								pos_rx = (_tmp4 = oniguruma_regex_make1 ((_tmp3 = g_strconcat ((_tmp2 = g_strconcat ("(", s2, NULL)), ")", NULL))), (pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL))), _tmp4);
								_tmp3 = (g_free (_tmp3), NULL);
								_tmp2 = (g_free (_tmp2), NULL);
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							} else {
								char* s1;
								char* s2;
								OnigurumaRegex* _tmp5;
								s1 = string_helper_gsub (g_strstrip (sub_selector_string), ".", "\\.");
								s2 = string_helper_gsub (s1, " ", ".*");
								/* stdout.printf("negative '%s' -> '%s'\n", selector_string, s2);*/
								_tmp5 = NULL;
								gee_collection_add (GEE_COLLECTION (neg_rxs), (_tmp5 = oniguruma_regex_make1 (s2)));
								(_tmp5 == NULL ? NULL : (_tmp5 = (g_object_unref (_tmp5), NULL)));
								s1 = (g_free (s1), NULL);
								s2 = (g_free (s2), NULL);
							}
							sub_selector_string = (g_free (sub_selector_string), NULL);
						}
					}
				}
				_tmp9 = NULL;
				_tmp7 = NULL;
				if ((_tmp8 = gtk_mate_matcher_test_match_re (pos_rx, neg_rxs, scope_string, &_tmp7), (*match) = (_tmp9 = _tmp7, ((*match) == NULL ? NULL : ((*match) = (g_object_unref ((*match)), NULL))), _tmp9), _tmp8)) {
					gboolean _tmp10;
					return (_tmp10 = TRUE, (selector_string1 = (g_free (selector_string1), NULL)), (pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL))), (neg_rxs == NULL ? NULL : (neg_rxs = (g_object_unref (neg_rxs), NULL))), (positives_and_negatives = (_vala_array_free (positives_and_negatives, positives_and_negatives_length1, ((GDestroyNotify) (g_free))), NULL)), (scope_ors1 = (_vala_array_free (scope_ors1, scope_ors1_length1, ((GDestroyNotify) (g_free))), NULL)), _tmp10);
				}
				selector_string1 = (g_free (selector_string1), NULL);
				(pos_rx == NULL ? NULL : (pos_rx = (g_object_unref (pos_rx), NULL)));
				(neg_rxs == NULL ? NULL : (neg_rxs = (g_object_unref (neg_rxs), NULL)));
				positives_and_negatives = (_vala_array_free (positives_and_negatives, positives_and_negatives_length1, ((GDestroyNotify) (g_free))), NULL);
			}
		}
	}
	return (_tmp12 = FALSE, (scope_ors1 = (_vala_array_free (scope_ors1, scope_ors1_length1, ((GDestroyNotify) (g_free))), NULL)), _tmp12);
}


gboolean gtk_mate_matcher_test_match_re (OnigurumaRegex* positive_selector_regex, GeeArrayList* negative_selector_regex, const char* scope_string, OnigurumaMatch** match) {
	OnigurumaMatch* m;
	g_return_val_if_fail (ONIGURUMA_IS_REGEX (positive_selector_regex), FALSE);
	g_return_val_if_fail (GEE_IS_ARRAY_LIST (negative_selector_regex), FALSE);
	g_return_val_if_fail (scope_string != NULL, FALSE);
	(*match) = NULL;
	m = oniguruma_regex_search (positive_selector_regex, scope_string, 0, ((gint) (strlen (scope_string))) - 1);
	if (m != NULL) {
		OnigurumaMatch* _tmp2;
		OnigurumaMatch* _tmp1;
		gboolean _tmp3;
		{
			GeeArrayList* neg_rx_collection;
			int neg_rx_it;
			neg_rx_collection = negative_selector_regex;
			for (neg_rx_it = 0; neg_rx_it < gee_collection_get_size (GEE_COLLECTION (neg_rx_collection)); neg_rx_it = neg_rx_it + 1) {
				OnigurumaRegex* neg_rx;
				neg_rx = ((OnigurumaRegex*) (gee_list_get (GEE_LIST (neg_rx_collection), neg_rx_it)));
				{
					OnigurumaMatch* m1;
					m1 = oniguruma_regex_search (neg_rx, scope_string, 0, ((gint) (strlen (scope_string))) - 1);
					if (m1 != NULL) {
						gboolean _tmp0;
						return (_tmp0 = FALSE, (neg_rx == NULL ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL))), (m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL))), (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp0);
					}
					(neg_rx == NULL ? NULL : (neg_rx = (g_object_unref (neg_rx), NULL)));
					(m1 == NULL ? NULL : (m1 = (g_object_unref (m1), NULL)));
				}
			}
		}
		_tmp2 = NULL;
		_tmp1 = NULL;
		(*match) = (_tmp2 = (_tmp1 = m, (_tmp1 == NULL ? NULL : g_object_ref (_tmp1))), ((*match) == NULL ? NULL : ((*match) = (g_object_unref ((*match)), NULL))), _tmp2);
		return (_tmp3 = TRUE, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp3);
	} else {
		gboolean _tmp4;
		return (_tmp4 = FALSE, (m == NULL ? NULL : (m = (g_object_unref (m), NULL))), _tmp4);
	}
	(m == NULL ? NULL : (m = (g_object_unref (m), NULL)));
}


GtkMateMatcher* gtk_mate_matcher_new (void) {
	GtkMateMatcher * self;
	self = g_object_newv (GTK_MATE_TYPE_MATCHER, 0, NULL);
	return self;
}


static void gtk_mate_matcher_class_init (GtkMateMatcherClass * klass) {
	gtk_mate_matcher_parent_class = g_type_class_peek_parent (klass);
}


static void gtk_mate_matcher_instance_init (GtkMateMatcher * self) {
}


GType gtk_mate_matcher_get_type (void) {
	static GType gtk_mate_matcher_type_id = 0;
	if (gtk_mate_matcher_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (GtkMateMatcherClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gtk_mate_matcher_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GtkMateMatcher), 0, (GInstanceInitFunc) gtk_mate_matcher_instance_init };
		gtk_mate_matcher_type_id = g_type_register_static (GTK_TYPE_OBJECT, "GtkMateMatcher", &g_define_type_info, 0);
	}
	return gtk_mate_matcher_type_id;
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if (array != NULL && destroy_func != NULL) {
		int i;
		if (array_length >= 0)
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) (array))[i] != NULL)
			destroy_func (((gpointer*) (array))[i]);
		}
		else
		for (i = 0; ((gpointer*) (array))[i] != NULL; i = i + 1) {
			destroy_func (((gpointer*) (array))[i]);
		}
	}
	g_free (array);
}




