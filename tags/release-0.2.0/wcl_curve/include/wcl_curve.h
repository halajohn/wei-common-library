#ifndef __wcl_curve_h__
#define __wcl_curve_h__

#define WCL_TYPE_CURVE            (wcl_curve_get_type())
#define WCL_CURVE(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), WCL_TYPE_CURVE, WclCurve))
#define WCL_CURVE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), WCL_TYPE_CURVE,  WclCurveClass))
#define WCL_IS_CURVE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), WCL_TYPE_CURVE))
#define WCL_IS_CURVE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), WCL_TYPE_CURVE))
#define WCL_CURVE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), WCL_TYPE_CURVE, WclCurveClass))

struct WclCurve
{
  /* parent object */
  GtkDrawingArea parent;
  
  GdkPixmap *pixmap;
};
typedef struct WclCurve WclCurve;

struct WclCurveClass
{
  /* parent class */
  GtkDrawingAreaClass parent_class;
};
typedef struct WclCurveClass WclCurveClass;

#ifdef __cplusplus
extern "C"
{
#endif

__declspec(dllexport) extern GType wcl_curve_get_type(void);
__declspec(dllexport) extern GtkWidget *wcl_curve_new(void);

#ifdef __cplusplus
}
#endif

#endif
