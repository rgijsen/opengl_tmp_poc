#include "common/logging.hpp"

#include <GL/glew.h>
#include "../viewer/window/Window.hpp"
#include "../viewer/render/PlotRenderer.hpp"
#include "../viewer/render/AxisRenderer.hpp"
#include "../viewer/render/RendererContext.hpp"
#include "../viewer/window/InputControlHandlers.hpp"

using namespace logging;

void viewer_2d_example()
{
  view::Window window;
  window.CreateWindow("test viewer", 700, 500);

  auto rendererContext = std::make_shared<render::RendererContext>();
  window.AttachContext(rendererContext);

  auto inputControl = window.GetInputControl();
  auto camera = rendererContext->GetCamera();

  inputControl->AddHandler([camera](view::InputControl& inputControl) { view::InputControlHandlers::InputHandler2D(camera, inputControl); });
  inputControl->AddHandler([camera](view::InputControl& inputControl) { view::InputControlHandlers::MouseHandler2D(camera, inputControl); });

  rendererContext->AddRenderer(render::make_renderer<render::AxisRenderer>(rendererContext));

  auto plotRenderer = render::make_renderer<render::PlotRenderer>(rendererContext);
  rendererContext->AddRenderer(plotRenderer);

  render::points_t points;
  for(int i = 0; i < 2000; i++)
  {
    float x = (float)((i - 1000.0) / 100.0);
    float y = (float)(sin(x * 10.0) / (1.0 + x * x));
    points.push_back({x, y});
  }

  plotRenderer->UpdatePoints(&points);

  window.Show();
}
