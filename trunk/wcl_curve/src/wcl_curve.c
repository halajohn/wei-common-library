#include "precompiled_header.h"

#include "wcl_curve.h"

static void wcl_curve_init(WclCurve *self);
static void wcl_curve_class_init(WclCurveClass *klass);
static gpointer wcl_curve_parent_class = NULL;

static void
wcl_curve_class_intern_init(gpointer klass)
{  
  wcl_curve_parent_class = g_type_class_peek_parent(klass);
  wcl_curve_class_init((WclCurveClass *)klass);
}

GType  
wcl_curve_get_type(void)  
{  
  static gsize volatile g_define_type_id__volatile = 0;
  
  if (g_once_init_enter(&g_define_type_id__volatile))
  {
    // starting a critical initialization section.
    GType g_define_type_id =  
      g_type_register_static_simple(GTK_TYPE_DRAWING_AREA,
                                    g_intern_static_string("WclCurve"),
                                    sizeof(WclCurveClass),  
                                    (GClassInitFunc)wcl_curve_class_intern_init,  
                                    sizeof(WclCurve),  
                                    (GInstanceInitFunc)wcl_curve_init,  
                                    (GTypeFlags)0);  
    {
    }
    
    g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);  
  }
  
  return g_define_type_id__volatile;	 
}

static gboolean
wcl_curve_expose(
  GtkWidget *widget,
  GdkEventExpose *event)
{
  // WclCurve * const wcl_curve = WCL_CURVE(widget);
  (void)widget;
  (void)event;
  
  return FALSE;
}

static void
wcl_curve_class_init(
  WclCurveClass *klass)
{
  GtkWidgetClass *widget_klass;
  
  widget_klass = GTK_WIDGET_CLASS(klass);
  
  widget_klass->expose_event = wcl_curve_expose;
}

/* Initialize the memory space allocated for the WclCurve
 * object.
 */
static void
wcl_curve_init(
  WclCurve *wcl_curve)
{
  wcl_curve->pixmap = NULL;
}

GtkWidget *
wcl_curve_new(void)
{
  return g_object_new(WCL_TYPE_CURVE, NULL);
}
