#ifndef __wcl_curve_gtk_h__
#define __wcl_curve_gtk_h__

#include <gtk/gtkdrawingarea.h>
#include <cairo.h>

#define GTK_TYPE_WCL_CURVE      (wcl_curve_get_type())
#define WCL_CURVE(obj)          GTK_CHECK_CAST(obj, GTK_TYPE_WCL_CURVE, WclCurve)
#define WCL_CURVE_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, GTK_TYPE_WCL_CURVE, WclCurveClass)
#define GTK_IS_WCL_CURVE(obj)   GTK_CHECK_TYPE(obj, GTK_TYPE_WCL_CURVE)

#ifdef __cplusplus
extern "C"
{
#endif
  
#define gdkcairo_t void
  
  struct WclCurve
  {
    GtkDrawingArea  drawing_area;
    gdkcairo_t     *gdkcairo;
  };
  typedef struct WclCurve WclCurve;
  
#undef gdkcairo_t
  
  struct WclCurveClass
  {
    GtkDrawingAreaClass parent_class;
    
    void (*paint)(WclCurve *, cairo_t *);
  };
  typedef struct WclCurveClass WclCurveClass;
  
  GType      wcl_curve_get_type(void);
  GtkWidget *wcl_curve_new(void);
  cairo_t   *wcl_curve_get_cairo (WclCurve *gtkcairo);
  

/* convenience function to set the current cairo color
 * from a GdkColor
 */
  void      wcl_curve_set_gdk_color (cairo_t  *cr,
                                     GdkColor *color);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#endif
