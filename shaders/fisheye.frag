uniform lowp float qt_Opacity;
uniform highp float f1;
uniform highp float f2;
uniform highp float xi1;
uniform highp float xi2;
uniform sampler2D source;

varying highp vec2 qt_TexCoord0;

highp vec3 normalize2( const in highp vec3 v ){
    float n = sqrt( v.x*v.x + v.y*v.y + v.z*v.z);
    highp vec3 o;
    o.x = v.x / n;
    o.y = v.y / n;
    o.z = v.z / n;
    return o;
}
highp vec2 project(const in highp vec3 point_in_camera)
{
    highp vec3 p = normalize2( point_in_camera );

    float focal_x = f1;
    float focal_y = f1;
    float center_x = 320.f;
    float center_y = 200.f;

    p.z = p.z + xi1;

    highp vec2 pixel_in_image;
    pixel_in_image.x = p.x * focal_x / p.z + center_x;
    pixel_in_image.y = p.y * focal_y / p.z + center_y;

    return pixel_in_image;
}

highp vec3 raytrace(const in highp vec2 pixel_in_image)
{
  highp vec3 ray_in_camera;
  highp vec2 center;
  center.x = 320.f;
  center.y = 200.f;

  float focal_x = f2;
  float focal_y = f2;

  highp vec2 p;
  p.x = (pixel_in_image.x-center.x)/focal_x;
  p.y = (pixel_in_image.y-center.y)/focal_y;

  float a = sqrt(p.x*p.x + p.y*p.y);
  float b = 1.0f + a * (1.0f - xi2 * xi2);

  float eta = (xi2 + sqrt(b)) / (1.0f + a);
  ray_in_camera.x = eta * p.x;
  ray_in_camera.y = eta * p.y;
  ray_in_camera.z = eta - xi2;
  return ray_in_camera;
}

void main()
{
    highp vec2 tmp = qt_TexCoord0;
    tmp.x *= 640.0f;
    tmp.y *= 400.0f;

    highp vec3 r = raytrace( tmp ); //from opengl
    highp vec2 p = project( r ); //to fisheye

    p.x = p.x / 640.0f;
    p.y = p.y / 400.0f;

    gl_FragColor = texture2D(source, p) * qt_Opacity;
}
