#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>

#include "wcl_curve_gdk.h"
#include "wcl_curve_gtk.h"

enum
{
  PAINT,
  LAST_SIGNAL
};

static void wcl_curve_realize (GtkWidget *widget);
static void wcl_curve_size_allocate (GtkWidget *widget, GtkAllocation * allocation);
static gint wcl_curve_expose (GtkWidget *widget, GdkEventExpose *event);

/*FIXME: make the cairo object a property as well,. and deprecate the get_cairo function */

static GtkWidgetClass *parent_class = 0;
static guint signals[LAST_SIGNAL] = { 0 };

static void
wcl_curve_destroy(
  GtkObject *object)
{
  g_return_if_fail(object != NULL);
  g_return_if_fail(GTK_IS_WCL_CURVE(object));
  
  {
    WclCurve * const wcl_curve = WCL_CURVE(object);
    
    gdkcairo_destroy(wcl_curve->gdkcairo);
  }
  
  if (GTK_OBJECT_CLASS (parent_class)->destroy)
    (*GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}

static void
wcl_curve_class_init(
  WclCurveClass *klass)
{
  GtkObjectClass *object_class;
  GtkWidgetClass *widget_class;
  
  object_class = (GtkObjectClass *) class;
  widget_class = (GtkWidgetClass *) class;
  parent_class = gtk_type_class (GTK_TYPE_WIDGET);
  
  object_class->destroy = wcl_curve_destroy;
  
  widget_class->realize = wcl_curve_realize;
  widget_class->expose_event = wcl_curve_expose;
  widget_class->size_allocate = wcl_curve_size_allocate;

  signals[PAINT] = g_signal_new ("paint",
                                 GTK_TYPE_WCL_CURVE,
                                 G_SIGNAL_RUN_LAST,
                                 G_STRUCT_OFFSET (WclCurveClass, paint),
                                 NULL, NULL,
                                 g_cclosure_marshal_VOID__POINTER,
                                 G_TYPE_NONE, 1, G_TYPE_POINTER);
}

/* Initialize the memory space allocated for the WclCurve
 * object.
 */
static void
wcl_curve_init(
  WclCurve *wcl_curve)
{
}

GType
wcl_curve_get_type(void)
{
  static GType wcl_curve_type = 0;
  
  if (0 == wcl_curve_type)
  {
    static GTypeInfo const wcl_curve_info = {
      sizeof(WclCurveClass),
      NULL,
      NULL,
      (GClassInitFunc)wcl_curve_class_init,
      NULL,
      NULL,
      sizeof(WclCurve),
      0,
      (GInstanceInitFunc)wcl_curve_init,
    };
    
    wcl_curve_type = g_type_register_static(GTK_TYPE_DRAWING_AREA,
                                            "WclCurve",
                                            &wcl_curve_info,
                                            0);
  }
  
  return wcl_curve_type;
}

GtkWidget *
wcl_curve_new (void)
{
  GtkWidget *wcl_curve;
  wcl_curve = GTK_WIDGET (g_object_new (GTK_TYPE_WCL_CURVE, NULL));

  gtk_widget_queue_draw (GTK_WIDGET (wcl_curve));

  return wcl_curve;
}

static void
wcl_curve_realize (GtkWidget *widget)
{
  WclCurve *wcl_curve;

  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_CAIRO (widget));

  GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
  wcl_curve = WCL_CURVE (widget);

  gdkcairo_realize (wcl_curve->gdkcairo);
}

static void
wcl_curve_size_allocate (GtkWidget     *widget,
                         GtkAllocation *allocation)
{
  WclCurve *wcl_curve;
  
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_CAIRO (widget));
  g_return_if_fail (allocation != NULL);
  
  wcl_curve = WCL_CURVE (widget);
  
  widget->allocation = *allocation;
  
  gdkcairo_size_allocate (wcl_curve->gdkcairo,
                          allocation->x, allocation->y,
                          allocation->width, allocation->height);
}

static gint
wcl_curve_expose (GtkWidget      *widget,
                  GdkEventExpose *event)
{
  WclCurve *wcl_curve;

  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_CAIRO (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  wcl_curve = WCL_CURVE (widget);

  gdkcairo_expose (wcl_curve->gdkcairo, event);
  return FALSE;
}

cairo_t  *
wcl_curve_get_cairo (WclCurve *wcl_curve)
{
  g_return_val_if_fail (wcl_curve != NULL, NULL);
  g_return_val_if_fail (GTK_IS_CAIRO (wcl_curve), NULL);
  return ((gdkcairo_t *) wcl_curve->gdkcairo)->cr;
}

void
wcl_curve_set_gdk_color (cairo_t  *cr,
                         GdkColor *color)
{
  double    red, green, blue;

  red = color->red / 65535.0;
  green = color->green / 65535.0;
  blue = color->blue / 65535.0;

  cairo_set_source_rgb (cr, red, green, blue);
}

int
wcl_curve_backend_is_gl (WclCurve *wcl_curve)
{
  if (((gdkcairo_t *) wcl_curve->gdkcairo)->backend == GDKCAIRO_BACKEND_GL)
    return 1;
  return 0;
}

#if 0
/* FIXME: premultiply the buffer, but who should own it?
 */

cairo_surface_t *
wcl_curve_surface_create_for_gdk_pixbuf (const GdkPixbuf * pixbuf)
{
  cairo_surface_t *self;
  char     *data;
  cairo_format_t format;
  int       width;
  int       height;
  int       stride;

  if (!pixbuf)
    return NULL;
  data = gdk_pixbuf_get_pixels (pixbuf);
  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);
  format = CAIRO_FORMAT_ARGB32;
  stride = gdk_pixbuf_get_rowstride (pixbuf);

  self = cairo_surface_create_for_image (data, format, width, height, stride);
  return self;
}
#endif

/* vim: set ts=4 sw=4 noet : */
