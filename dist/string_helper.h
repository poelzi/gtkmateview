/* Vala string utility functions*/

#ifndef __STRING_HELPER_H__
#define __STRING_HELPER_H__

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define TYPE_STRING_HELPER (string_helper_get_type ())
#define STRING_HELPER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_STRING_HELPER, StringHelper))
#define STRING_HELPER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_STRING_HELPER, StringHelperClass))
#define IS_STRING_HELPER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_STRING_HELPER))
#define IS_STRING_HELPER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_STRING_HELPER))
#define STRING_HELPER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_STRING_HELPER, StringHelperClass))

typedef struct _StringHelper StringHelper;
typedef struct _StringHelperClass StringHelperClass;
typedef struct _StringHelperPrivate StringHelperPrivate;

/* Started: 30 Aug 08*/
struct _StringHelper {
	GTypeInstance parent_instance;
	volatile int ref_count;
	StringHelperPrivate * priv;
};

struct _StringHelperClass {
	GTypeClass parent_class;
	void (*finalize) (StringHelper *self);
};


char* string_helper_gsub (const char* start_string, const char* match_string, const char* replacement_string);
StringHelper* string_helper_new (void);
GType string_helper_get_type (void);
gpointer string_helper_ref (gpointer instance);
void string_helper_unref (gpointer instance);


G_END_DECLS

#endif
