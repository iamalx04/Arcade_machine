#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include <vector>

namespace m1
{
class Tema1 : public gfxc::SimpleScene
{
public:
  Tema1();
  ~Tema1();

  void Init() override;

private:
  gfxc::TextRenderer* m_textRenderer;
  void FrameStart() override;
  void Update(float deltaTimeSeconds) override;
  void FrameEnd() override;

  void OnInputUpdate(float deltaTime, int mods) override;
  void OnKeyPress(int key, int mods) override;
  void OnKeyRelease(int key, int mods) override;
  void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
  void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
  void OnWindowResize(int width, int height) override;
  void EditorGrid();
  void InitSingleBlock();
  void InitEngine();
  void InitBumper();
  void InitGun();
  void RenderSingleBlock(float x, float y);
  void RenderEngine(float x, float y);
  void RenderBumper(float x, float y);
  void RenderGun(float x, float y);
  void UpdateGrid();
  void InitStartButton();
  void EditorUpdate();
  void GameUpdate(float deltaTimeSeconds);
  void EndGame();
  int CheckConex();
  void DFS_CheckConex(int c, int r, bool visited[17][9], int& count);
  void AddSpaceshipInGame();
  void InitText();

  float macScale;
  int typeScreen;
  glm::mat3 modelMatrix;
  int spaceshipPieces;
  int gridLength, gridWidth;
  float objectMouseX, objectMouseY;
  bool onMove;
  std::string objectOnMove;
  int matrixGrid[17][9];
  glm::vec3 startButtonColor;
  int InitGame;
  int score;
  int lives;
  struct spaceship_t {
    int x, y;
    int type;
  };
  std::vector<spaceship_t> comps;
  float size_standard;
  float SceneCenter;
  float paddleMove;
  float paddleX, paddleY;
  float paddleLength;
  float paddleHeight;
  float posBallX, posBallY, vBallX, vBallY;
  float angleBall;
  float speed = 4.0f;
  int matrixBlocks[5][12];
  float blockScales[5][12];
  int startGame;
  int lowY = 0;
  int highY = 670;
  int lowX = 0;
  int highX = 1280;
  int ballRadius = 10;
  int blocksHighX = 1280;
  int blocksLowX = 0;
  int blocksHighY = 670;
  int blocksLowY = 412;
  int blockCount;

  std::vector<glm::vec3> colors = {glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 1) };
};
}   // namespace m1