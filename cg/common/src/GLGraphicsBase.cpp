#include "GLGraphicsBase.h"

namespace V3D
{ // begin namespace V3D

namespace Graphics
{ // begin namespace Graphics

static const char* pointVertexShader =
  "#version 400\n"
  "uniform vec4 p;\n"
  "uniform vec4 pointColor;\n"
  "out vec4 color;\n"
  "void main() {\n"
  "gl_Position = p;\n"
  "color = pointColor;\n"
  "}";

static const char* lineVertexShader =
  "#version 400\n"
  "uniform vec4 p[2];\n"
  "uniform vec4 lineColor;\n"
  "out vec4 color;\n"
  "void main() {\n"
  "gl_Position = p[gl_VertexID];\n"
  "color = lineColor;\n"
  "}";

static const char* triangleVertexShader =
  "#version 400\n"
  "uniform vec4 p[3];\n"
  "uniform vec4 vertexColor[3];\n"
  "out vec4 color;\n"
  "void main() {\n"
  "gl_Position = p[gl_VertexID];\n"
  "color = vertexColor[gl_VertexID];\n"
"}";

static const char* fragmentShader =
  "#version 400\n"
  "in vec4 color;\n"
  "out vec4 fragmentColor;\n"
  "void main() {\n"
  "fragmentColor = color;\n"
  "}";

inline void
setShaders(GLSL::Program& p, const char* vs, const char* fs)
{
  p.addShader(GL_VERTEX_SHADER, vs).addShader(GL_FRAGMENT_SHADER, fs);
}

GLGraphicsBase::GLGraphicsBase():
  _pointDrawer{"Point Drawer"},
  _pointColor{Color::white},
  _pointSize{4},
  _lineDrawer{"Line Drawer"},
  _lineColor{Color::white},
  _lineWidth{1},
  _triangleDrawer{"TriangleDrawer"}
{
  using namespace GLSL;

  setShaders(_pointDrawer, pointVertexShader, fragmentShader);
  _pointDrawer.use();
  _pointLoc = _pointDrawer.uniformLocation("p");
  _pointColorLoc = _pointDrawer.uniformLocation("pointColor");
  setShaders(_lineDrawer, lineVertexShader, fragmentShader);
  _lineDrawer.use();
  _linePointsLoc = _lineDrawer.uniformLocation("p[0]");
  _lineColorLoc = _lineDrawer.uniformLocation("lineColor");
  setShaders(_triangleDrawer, triangleVertexShader, fragmentShader);
  _triangleDrawer.use();
  _trianglePointsLoc = _triangleDrawer.uniformLocation("p[0]");
  _triangleColorsLoc = _triangleDrawer.uniformLocation("vertexColor[0]");
  glGenVertexArrays(1, &_vao);
}

GLGraphicsBase::~GLGraphicsBase()
{
  glDeleteVertexArrays(1, &_vao);
}

void
GLGraphicsBase::drawPoint(const float* point)
{
  using namespace GLSL;

  auto cp = Program::current();

  _pointDrawer.use();
  _pointDrawer.setUniformVec4(_pointColorLoc, _pointColor);
  glUniform4fv(_pointLoc, 1, point);
  glBindVertexArray(_vao);
  glPointSize(_pointSize);
  glDrawArrays(GL_POINTS, 0, 1);
  Program::setCurrent(cp);
}

void
GLGraphicsBase::drawLine(const float* points)
{
  using namespace GLSL;

  auto cp = Program::current();

  _lineDrawer.use();
  _lineDrawer.setUniformVec4(_lineColorLoc, _lineColor);
  glUniform4fv(_linePointsLoc, 2, points);
  glBindVertexArray(_vao);
  glLineWidth(_lineWidth);
  glDrawArrays(GL_LINES, 0, 2);
  Program::setCurrent(cp);
}

void
GLGraphicsBase::drawTriangle(const float* points, bool fill)
{
  using namespace GLSL;

  auto cp = Program::current();

  _triangleDrawer.use();
  glBindVertexArray(_vao);
  glUniform4fv(_triangleColorsLoc, 3, (float*)_triangleColors);
  glUniform4fv(_trianglePointsLoc, 3, points);
  glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
  if (fill)
  {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
  }
  glDrawArrays(GL_TRIANGLES, 0, 3);
  Program::setCurrent(cp);
}

} // end namespace Graphics
} // end namespace V3D
