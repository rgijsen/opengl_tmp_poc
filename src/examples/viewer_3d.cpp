
#include "common/logging.hpp"

#include <GL/glew.h>
#include "../viewer/window/Window.hpp"

#include "../viewer/render/RendererContext.hpp"
//#include "../viewer/render/PointCloudRenderer.hpp"
#include "../viewer/render/PolarGridRenderer.hpp"
#include "../viewer/render/primitives/CubeRenderer.hpp"
#include "../viewer/window/InputControlHandlers.hpp"

using namespace logging;

void viewer_3d_example()
{
  view::Window window;
  window.CreateWindow("test viewer", 700, 500);

  auto rendererContext = std::make_shared<render::RendererContext>();
  window.AttachContext(rendererContext);

  auto inputControl = window.GetInputControl();
  auto camera = rendererContext->GetCamera();

  inputControl->AddHandler([camera](view::InputControl& inputControl) { view::InputControlHandlers::InputHandler3D(camera, inputControl); });
  inputControl->AddHandler([camera](view::InputControl& inputControl) { view::InputControlHandlers::MouseHandler3D(camera, inputControl); });
  
  // polar groundplane
  rendererContext->AddRenderer(render::make_renderer<render::PolarGridRenderer>(rendererContext, 1.0f, 10.0f, mathex::DegreeToRad(15.0f), mathex::DegreeToRad(360.0f)));
  rendererContext->AddRenderer(render::make_renderer<render::CubeRenderer>(rendererContext, glm::mat4x4()));

  camera->SetResetPosition(glm::vec3(0, 0, -5));

  window.Show();
}
