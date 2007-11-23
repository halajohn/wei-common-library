#ifndef __wcl_curve_gdk_h__
#define __wcl_curve_gdk_h__

#include <gtk/gtk.h>
#include <cairo.h>

typedef enum
{
  GDKCAIRO_BACKEND_IMAGE,
  GDKCAIRO_BACKEND_XLIB,
  GDKCAIRO_BACKEND_GL,
  GDKCAIRO_BACKEND_NONE
} gdkcairo_backend;

typedef struct gdkcairo_t
{
  GtkWidget *widget;
  cairo_t  *cr;
  gdkcairo_backend backend;
} gdkcairo_t;

gdkcairo_t *gdkcairo_new (GtkWidget *widget);

void        gdkcairo_destroy (gdkcairo_t *self);

void        gdkcairo_realize (gdkcairo_t *self);

void        gdkcairo_size_allocate (gdkcairo_t *self,
                                    gint        x,
                                    gint        y,
                                    gint        width,
                                    gint        height);
gint        gdkcairo_expose (gdkcairo_t     *self,
                             GdkEventExpose *event);

#endif /* GDKCAIRO_H */
