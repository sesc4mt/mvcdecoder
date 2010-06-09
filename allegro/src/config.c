/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      Configuration routines.
 *
 *      By Trent Gamblin.
 */

/* Title: Configuration routines
 */


#include <stdio.h>
#include <ctype.h>
#include "allegro5/allegro5.h"
#include "allegro5/internal/aintern.h"
#include "allegro5/internal/aintern_config.h"
#include "allegro5/internal/aintern_memory.h"



static void *local_calloc1(size_t size)
{
   void *p;

   p = _AL_MALLOC(size);
   if (p) {
      memset(p, 0, size);
   }
   return p;
}


/* Function: al_create_config
 */
ALLEGRO_CONFIG *al_create_config(void)
{
   ALLEGRO_CONFIG *config = local_calloc1(sizeof(ALLEGRO_CONFIG));
   ASSERT(config);

   return config;
}


static ALLEGRO_CONFIG_SECTION *find_section(const ALLEGRO_CONFIG *config,
   const ALLEGRO_USTR *section)
{
   ALLEGRO_CONFIG_SECTION *p = config->head;

   if (!p)
      return NULL;

   while (p != NULL) {
      if (al_ustr_equal(p->name, section))
         return p;
      p = p->next;
   }

   return NULL;
}


static ALLEGRO_CONFIG_ENTRY *find_entry(ALLEGRO_CONFIG_ENTRY *section_head,
   const ALLEGRO_USTR *key)
{
   ALLEGRO_CONFIG_ENTRY *p = section_head;

   while (p != NULL) {
      if (!p->is_comment && al_ustr_equal(p->key, key)) {
         return p;
      }
      p = p->next;
   }

   return NULL;
}


static void get_key_and_value(const ALLEGRO_USTR *buf,
   ALLEGRO_USTR *key, ALLEGRO_USTR *value)
{
   int eq = al_ustr_find_chr(buf, 0, '=');

   if (eq == -1) {
      al_ustr_assign(key, buf);
      al_ustr_assign_cstr(value, "");
   }
   else {
      al_ustr_assign_substr(key, buf, 0, eq);
      al_ustr_assign_substr(value, buf, eq + 1, al_ustr_size(buf));
   }

   al_ustr_trim_ws(key);
   al_ustr_trim_ws(value);
}


static ALLEGRO_CONFIG_SECTION *config_add_section(ALLEGRO_CONFIG *config,
   const ALLEGRO_USTR *name)
{
   ALLEGRO_CONFIG_SECTION *sec = config->head;
   ALLEGRO_CONFIG_SECTION *section;

   if ((section = find_section(config, name)))
      return section;

   section = local_calloc1(sizeof(ALLEGRO_CONFIG_SECTION));
   section->name = al_ustr_dup(name);

   if (sec == NULL) {
      config->head = section;
   }
   else {
      while (sec->next != NULL)
         sec = sec->next;
      sec->next = section;
   }

   return section;
}


/* Function: al_add_config_section
 */
void al_add_config_section(ALLEGRO_CONFIG *config, const char *name)
{
   ALLEGRO_USTR_INFO name_info;
   ALLEGRO_USTR *uname;

   uname = al_ref_cstr(&name_info, name);
   config_add_section(config, uname);
}


static void config_set_value(ALLEGRO_CONFIG *config,
   const ALLEGRO_USTR *section, const ALLEGRO_USTR *key,
   const ALLEGRO_USTR *value)
{
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_CONFIG_ENTRY *entry;

   s = find_section(config, section);
   if (s) {
      entry = find_entry(s->head, key);
   }
   else {
      entry = NULL;
   }

   if (entry) {
      al_ustr_assign(entry->value, value);
      al_ustr_trim_ws(entry->value);
      return;
   }

   entry = local_calloc1(sizeof(ALLEGRO_CONFIG_ENTRY));
   entry->is_comment = false;
   entry->key = al_ustr_dup(key);
   entry->value = al_ustr_dup(value);
   al_ustr_trim_ws(entry->value);

   if (!s) {
      s = config_add_section(config, section);
   }

   if (s->head == NULL) {
      s->head = entry;
   }
   else {
      ALLEGRO_CONFIG_ENTRY *p = s->head;
      while (p->next != NULL)
         p = p->next;
      p->next = entry;
   }
}


/* Function: al_set_config_value
 */
void al_set_config_value(ALLEGRO_CONFIG *config,
   const char *section, const char *key, const char *value)
{
   ALLEGRO_USTR_INFO section_info;
   ALLEGRO_USTR_INFO key_info;
   ALLEGRO_USTR_INFO value_info;
   ALLEGRO_USTR *usection;
   ALLEGRO_USTR *ukey;
   ALLEGRO_USTR *uvalue;

   if (section == NULL) {
      section = "";
   }

   ASSERT(key);
   ASSERT(value);

   usection = al_ref_cstr(&section_info, section);
   ukey = al_ref_cstr(&key_info, key);
   uvalue = al_ref_cstr(&value_info, value);

   config_set_value(config, usection, ukey, uvalue);
}


static void config_add_comment(ALLEGRO_CONFIG *config,
   const ALLEGRO_USTR *section, const ALLEGRO_USTR *comment)
{
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_CONFIG_ENTRY *entry;

   s = find_section(config, section);

   entry = local_calloc1(sizeof(ALLEGRO_CONFIG_ENTRY));
   entry->is_comment = true;
   entry->key = al_ustr_dup(comment);

   /* Replace all newline characters by spaces, otherwise the written comment
    * file will be corrupted.
    */
   al_ustr_find_replace_cstr(entry->key, 0, "\n", " ");

   if (!s) {
      s = config_add_section(config, section);
   }

   if (s->head == NULL) {
      s->head = entry;
   }
   else {
      ALLEGRO_CONFIG_ENTRY *p = s->head;
      while (p->next != NULL)
         p = p->next;
      p->next = entry;
   }
}


/* Function: al_add_config_comment
 */
void al_add_config_comment(ALLEGRO_CONFIG *config,
   const char *section, const char *comment)
{
   ALLEGRO_USTR_INFO section_info;
   ALLEGRO_USTR_INFO comment_info;
   ALLEGRO_USTR *usection;
   ALLEGRO_USTR *ucomment;

   if (section == NULL) {
      section = "";
   }

   ASSERT(comment);

   usection = al_ref_cstr(&section_info, section);
   ucomment = al_ref_cstr(&comment_info, comment);

   config_add_comment(config, usection, ucomment);
}


static bool config_get_value(const ALLEGRO_CONFIG *config,
   const ALLEGRO_USTR *section, const ALLEGRO_USTR *key,
   ALLEGRO_USTR **ret_value)
{
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_CONFIG_ENTRY *e;

   s = find_section(config, section);
   if (!s)
      return false;
   e = s->head;

   e = find_entry(e, key);
   if (!e)
      return false;

   *ret_value = e->value;
   return true;
}


/* Function: al_get_config_value
 */
const char *al_get_config_value(const ALLEGRO_CONFIG *config,
   const char *section, const char *key)
{
   ALLEGRO_USTR_INFO section_info;
   ALLEGRO_USTR_INFO key_info;
   ALLEGRO_USTR *usection;
   ALLEGRO_USTR *ukey;
   ALLEGRO_USTR *value;

   if (section == NULL) {
      section = "";
   }

   usection = al_ref_cstr(&section_info, section);
   ukey = al_ref_cstr(&key_info, key);

   if (config_get_value(config, usection, ukey, &value))
      return al_cstr(value);
   else
      return NULL;
}


static bool readline(ALLEGRO_FILE *file, ALLEGRO_USTR *line)
{
   char buf[128];

   if (!al_fgets(file, buf, sizeof(buf))) {
      return false;
   }

   do {
      al_ustr_append_cstr(line, buf);
      if (al_ustr_has_suffix_cstr(line, "\n"))
         break;
   } while (al_fgets(file, buf, sizeof(buf)));

   return true;
}


/* Function: al_load_config_file
 */
ALLEGRO_CONFIG *al_load_config_file(const char *filename)
{
   ALLEGRO_CONFIG *config;
   ALLEGRO_CONFIG_SECTION *current_section = NULL;
   ALLEGRO_USTR *line;
   ALLEGRO_USTR *section;
   ALLEGRO_USTR *key;
   ALLEGRO_USTR *value;
   ALLEGRO_FILE *file;

   file = al_fopen(filename, "r");
   if (!file) {
      return NULL;
   }
   
   config = al_create_config();
   if (!config) {
      al_fclose(file);
      return NULL;
   }

   line = al_ustr_new("");
   section = al_ustr_new("");
   key = al_ustr_new("");
   value = al_ustr_new("");

   while (1) {
      al_ustr_assign_cstr(line, "");
      if (!readline(file, line))
         break;
      al_ustr_trim_ws(line);

      if (al_ustr_has_prefix_cstr(line, "#") || al_ustr_size(line) == 0) {
         /* Preserve comments and blank lines */
         ALLEGRO_USTR *name;
         if (current_section)
            name = current_section->name;
         else
            name = al_ustr_empty_string();
         config_add_comment(config, name, line);
      }
      else if (al_ustr_has_prefix_cstr(line, "[")) {
         int rbracket = al_ustr_rfind_chr(line, al_ustr_size(line), ']');
         if (rbracket == -1)
            rbracket = al_ustr_size(line);
         al_ustr_assign_substr(section, line, 1, rbracket);
         current_section = config_add_section(config, section);
      }
      else {
         get_key_and_value(line, key, value);
         if (current_section == NULL)
            config_set_value(config, al_ustr_empty_string(), key, value);
         else
            config_set_value(config, current_section->name, key, value);
      }
   }

   al_ustr_free(line);
   al_ustr_free(section);
   al_ustr_free(key);
   al_ustr_free(value);

   al_fclose(file);

   return config;
}


static bool config_write_section(ALLEGRO_FILE *file,
   const ALLEGRO_CONFIG_SECTION *s)
{
   ALLEGRO_CONFIG_ENTRY *e;

   if (al_ustr_size(s->name) > 0) {
      al_fputc(file, '[');
      al_fputs(file, al_cstr(s->name));
      al_fputs(file, "]\n");
      if (al_ferror(file)) {
         return false;
      }
   }

   e = s->head;
   while (e != NULL) {
      if (e->is_comment) {
         if (al_ustr_size(e->key) > 0) {
            if (!al_ustr_has_prefix_cstr(e->key, "#")) {
               al_fputs(file, "# ");
            }
            al_fputs(file, al_cstr(e->key));
         }
         al_fputc(file, '\n');
      }
      else {
         al_fputs(file, al_cstr(e->key));
         al_fputc(file, '=');
         al_fputs(file, al_cstr(e->value));
         al_fputc(file, '\n');
      }
      if (al_ferror(file)) {
         return false;
      }

      e = e->next;
   }

   return true;
}


/* Function: al_save_config_file
 */
bool al_save_config_file(const ALLEGRO_CONFIG *config, const char *filename)
{
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_FILE *file = al_fopen(filename, "w");

   if (!file) {
      return false;
   }

   /* Save global section */
   s = config->head;
   while (s != NULL) {
      if (al_ustr_size(s->name) == 0) {
         if (!config_write_section(file, s)) {
            goto Error;
         }
         break;
      }
      s = s->next;
   }

   /* Save other sections */
   s = config->head;
   while (s != NULL) {
      if (al_ustr_size(s->name) > 0) {
         if (!config_write_section(file, s)) {
            goto Error;
         }
      }
      s = s->next;
   }

#if 0
   if (al_fs_entry_close(file)) {
      /* XXX do we delete the incomplete file? */
      return 1;
   }
#endif

   al_fclose(file);

   return true;

Error:

   /* XXX do we delete the incomplete file? */
   al_fclose(file);
   return false;
}


/* do_config_merge_into:
 *  Helper function for merging.
 */
static void do_config_merge_into(ALLEGRO_CONFIG *master,
   const ALLEGRO_CONFIG *add, bool merge_comments)
{
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_CONFIG_ENTRY *e;
   ASSERT(master);

   if (!add) {
      return;
   }

   /* Save each section */
   s = add->head;
   while (s != NULL) {
      config_add_section(master, s->name);
      e = s->head;
      while (e != NULL) {
         if (!e->is_comment) {
            config_set_value(master, s->name, e->key, e->value);
         }
         else if (merge_comments) {
            config_add_comment(master, s->name, e->key);
         }
         e = e->next;
      }
      s = s->next;
   }
}


/* Function: al_merge_config_into
 */
void al_merge_config_into(ALLEGRO_CONFIG *master, const ALLEGRO_CONFIG *add)
{
   do_config_merge_into(master, add, false);
}


/* Function: al_merge_config
 */
ALLEGRO_CONFIG *al_merge_config(const ALLEGRO_CONFIG *cfg1,
    const ALLEGRO_CONFIG *cfg2)
{
   ALLEGRO_CONFIG *config = al_create_config();

   do_config_merge_into(config, cfg1, true);
   do_config_merge_into(config, cfg2, false);

   return config;
}


/* Function: al_destroy_config
 */
void al_destroy_config(ALLEGRO_CONFIG *config)
{
   ALLEGRO_CONFIG_ENTRY *e;
   ALLEGRO_CONFIG_SECTION *s;

   if (!config) {
      return;
   }

   s = config->head;
   while (s) {
      ALLEGRO_CONFIG_SECTION *tmp = s->next;
      e = s->head;
      while (e) {
         ALLEGRO_CONFIG_ENTRY *tmp = e->next;
         al_ustr_free(e->key);
         al_ustr_free(e->value);
         _AL_FREE(e);
         e = tmp;
      }
      al_ustr_free(s->name);
      _AL_FREE(s);
      s = tmp;
   }

   _AL_FREE(config);
}


/* Function: al_get_first_config_section
 */
char const *al_get_first_config_section(ALLEGRO_CONFIG const *config,
   void **iterator)
{
   ALLEGRO_CONFIG_SECTION *s;

   if (!config)
      return NULL;
   s = config->head;
   if (iterator) *iterator = s;
   return s ? al_cstr(s->name) : NULL;
}


/* Function: al_get_next_config_section
 */
char const *al_get_next_config_section(void **iterator)
{
   ALLEGRO_CONFIG_SECTION *s;

   if (!iterator)
      return NULL;
   s = *iterator;
   if (s)
      s = s->next;
   *iterator = s;
   return s ? al_cstr(s->name) : NULL;
}


/* Function: al_get_first_config_entry
 */
char const *al_get_first_config_entry(ALLEGRO_CONFIG const *config,
   char const *section, void **iterator)
{
   ALLEGRO_USTR_INFO section_info;
   ALLEGRO_USTR *usection;
   ALLEGRO_CONFIG_SECTION *s;
   ALLEGRO_CONFIG_ENTRY *e;

   if (!config)
      return NULL;

   if (section == NULL)
      section = "";

   usection = al_ref_cstr(&section_info, section);
   s = find_section(config, usection);
   if (!s)
      return NULL;
   e = s->head;
   while (e && e->is_comment)
      e = e->next;
   if (iterator) *iterator = e;
   return e ? al_cstr(e->key) : NULL;
}


/* Function: al_get_next_config_entry
 */
char const *al_get_next_config_entry(void **iterator)
{
   ALLEGRO_CONFIG_ENTRY *e;

   if (!iterator)
      return NULL;
   e = *iterator;
   if (e)
      e = e->next;
   while (e && e->is_comment)
      e = e->next;
   *iterator = e;
   return e ? al_cstr(e->key) : NULL;
}

/* vim: set sts=3 sw=3 et: */