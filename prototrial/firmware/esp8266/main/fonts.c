/**
 * LCD/OLED fonts library
 *
 * FIXME: License?
 *
 * @date: 8 dec. 2016
 *      Author: zaltora
 */
#include "fonts.h"

#ifndef FONTS_GLCD_5X7
 #define FONTS_GLCD_5X7
#endif

#ifdef FONTS_GLCD_5X7
 #include "fonts/font_glcd_5x7.h"
#endif

#ifdef FONTS_ROBOTO_8PT
 #include "fonts/font_roboto_8pt.h"
#endif

#ifdef FONTS_ROBOTO_10PT
 #include "fonts/font_roboto_10pt.h"
#endif

#ifdef FONTS_TERMINUS_6X12_ISO8859_1
 #include "fonts/font_terminus_6x12_iso8859_1.h"
#endif

/////////////////////////////////////////////

// FIXME: this declaration is noisy

const font_info_t *font_builtin_fonts[] = {

#ifdef FONTS_GLCD_5X7
  [FONT_FACE_GLCD5x7] = &_fonts_glcd_5x7_info,
#else
  [FONT_FACE_GLCD5x7] = NULL,
#endif

#ifdef FONTS_ROBOTO_8PT
  [FONT_FACE_ROBOTO_8PT] = &_fonts_roboto_8pt_info,
#else
  [FONT_FACE_ROBOTO_8PT] = NULL,
#endif

#ifdef FONTS_ROBOTO_10PT
  [FONT_FACE_ROBOTO_10PT] = &_fonts_roboto_10pt_info,
#else
  [FONT_FACE_ROBOTO_10PT] = NULL,
#endif

#ifdef FONTS_TERMINUS_6X12_ISO8859_1
  [FONT_FACE_TERMINUS_6X12_ISO8859_1] = &_fonts_terminus_6x12_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_6X12_ISO8859_1] = NULL,
#endif

};

const size_t font_builtin_fonts_count =
  (sizeof(font_builtin_fonts) / sizeof(font_info_t *));

/////////////////////////////////////////////

uint16_t font_measure_string(const font_info_t *fnt, const char *s) {
  if (!s || !fnt)
    return 0;

  uint16_t res = 0;
  while (*s) {
    const font_char_desc_t *d = font_get_char_desc(fnt, *s);
    if (d)
      res += d->width + fnt->c;
    s++;
  }

  return res > 0 ? res - fnt->c : 0;
}
