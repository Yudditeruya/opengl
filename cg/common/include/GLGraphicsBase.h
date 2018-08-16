#pragma once

#include "Color.h"
#include "GLProgram.h"

namespace V3D
{ // begin namespace V3D

namespace Graphics
{ // begin namespace Graphics

class GLGraphicsBase
{
public:
  // Destructor
  ~GLGraphicsBase();

  // Get point color
  const Color& pointColor() const
  {
    return _pointColor;
  }

  // Set point color
  void setPointColor(const Color& color)
  {
    _pointColor = color;
  }

  // Get point size
  float pointSize() const
  {
    return _pointSize;
  }

  // Set point size
  void setPointSize(float size)
  {
    _pointSize = size;
  }

  // Get line color
  const Color& lineColor() const
  {
    return _lineColor;
  }

  // Set line color
  void setLineColor(const Color& color)
  {
    _lineColor = color;
  }

  // Get line width
  float lineWidth() const
  {
    return _lineWidth;
  }

  // Set line width
  void setLineWidth(float width)
  {
    _lineWidth = width;
  }

  // Set triangle color
  void setTriangleColor(const Color& color)
  {
    _triangleColors[0] = color;
    _triangleColors[1] = color;
    _triangleColors[2] = color;
  }

  // Set triangle colors
  void setTriangleColor(const Color* colors)
  {
    _triangleColors[0] = colors[0];
    _triangleColors[1] = colors[1];
    _triangleColors[2] = colors[2];
  }

protected:
  // Constructor
  GLGraphicsBase();

  // Draw point in NDC
  void drawPoint(const float*);

  // Draw line in NDC
  void drawLine(const float*);

  // Draw triangle in NDC
  void drawTriangle(const float*, bool = false);

private:
  GLuint _vao;
  GLSL::Program _pointDrawer;
  Color _pointColor;
  float _pointSize;
  GLint _pointLoc;
  GLint _pointColorLoc;
  GLSL::Program _lineDrawer;
  Color _lineColor;
  float _lineWidth;
  GLint _linePointsLoc;
  GLint _lineColorLoc;
  GLSL::Program _triangleDrawer;
  Color _triangleColors[3];
  GLint _trianglePointsLoc;
  GLint _triangleColorsLoc;

}; // GLGraphicsBase

} // end namespace Graphics
} // end namespace V3D
