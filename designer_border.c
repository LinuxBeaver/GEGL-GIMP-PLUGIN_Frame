/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øvind Kolas (pippin) for major GEGL contributions
 * 2023 Beaver, Frame.

Test static preview of this plugin by installing by pasting this syntax. Requires lb:threshold-alpha and lb:glossy-balloon that ship with the plugin.

id=1 src  aux=[ ref=1 color ] crop

gaussian-blur std-dev-x=10 std-dev-y=10   clip-extent=false

lb:threshold-alpha alphadegree=9 lb:threshold-alpha alphadegree=9 lb:threshold-alpha alphadegree=9 lb:threshold-alpha alphadegree=9 lb:threshold-alpha alphadegree=9 lb:threshold-alpha alphadegree=9 color-overlay value=#ffffff dst-over aux=[ color value=#000000  ]  gimp:layer-mode layer-mode=color-erase opacity=1.00 aux=[ color value=#ffffff ] crop
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

#define prepare_canvas \
" id=1 src  aux=[ ref=1 color value=black ] crop "\

#define ta2spam \
" lb:threshold-alpha  lb:threshold-alpha  lb:threshold-alpha lb:threshold-alpha  lb:threshold-alpha  lb:threshold-alpha  "\

#define invert_transparency_meme \
" color-overlay value=#ffffff dst-over aux=[ color value=#000000  ] color-to-alpha color=#ffffff invert "\


#define ta2 \
" lb:threshold-alpha median-blur radius=0 "\

property_double (control, _("Increase the size of the border"), 25.0)
   description  (_("Increase the size of the border"))
  value_range (1.0, 100.0)
  ui_range (1.0, 100.0)
  ui_gamma (1.5)

property_color  (color, _("Color Selection"), "#ffffff")
    description (_("Color of the border"))

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     designer_border
#define GEGL_OP_C_SOURCE designer_border.c

#include "gegl-op.h"



static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output,   *graph1, *graph2, *graph3, *color, *graph0, *control;


  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");

  graph0 = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", invert_transparency_meme,
                                  NULL);

  graph1 = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", prepare_canvas,
                                  NULL);

  graph2 = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", ta2spam,
                                  NULL);
  graph3 = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", ta2,
                                  NULL);

  control = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur", "clip-extent", FALSE,
                                  NULL);

  color = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                  NULL);


    gegl_node_link_many (input, graph1, control, graph2, graph0, graph3, color,  output, NULL);

  gegl_operation_meta_redirect (operation, "control", control, "std-dev-x");
  gegl_operation_meta_redirect (operation, "control", control, "std-dev-y");
  gegl_operation_meta_redirect (operation, "color", color, "value");

}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;


  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:frame",
    "title",       _("Frame Border Generator"),
    "reference-hash", "deklal3fdisenadesinbordaada",
    "description", _("Render a border then style it"
                     ""),
    "gimp:menu-path", "<Image>/Filters/Render/Fun",
    "gimp:menu-label", _("Designer Frame..."),

    NULL);
}

#endif
