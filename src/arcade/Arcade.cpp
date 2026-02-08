#include "arcade/Arcade.h"

#include "components/text_renderer.h"
#include "arcade/GenObjects.h"
#include "arcade/transform2D.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::InitStartButton() {
    Mesh* StartTriangle1 = GenObjects::CreateTriangle("StartTriangle1", glm::vec3(0, 0, 0), glm::vec3(-40, 30, 0), glm::vec3(-40, -30, 0), startButtonColor, true);
    AddMeshToList(StartTriangle1);

    Mesh* StartTriangle2 = GenObjects::CreateTriangle("StartTriangle2", glm::vec3(0, 0, 0), glm::vec3(-40, 30, 0), glm::vec3(30, 30, 0), startButtonColor, true);
    AddMeshToList(StartTriangle2);

    Mesh* StartTriangle3 = GenObjects::CreateTriangle("StartTriangle3", glm::vec3(0, 0, 0), glm::vec3(30, -30, 0), glm::vec3(-40, -30, 0), startButtonColor, true);
    AddMeshToList(StartTriangle3);
}

void Tema1::InitSingleBlock() {
    Mesh* SingleSquare = GenObjects::CreateSquare("SingleSquare", glm::vec3(0, 0, 0), size_standard, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(SingleSquare);
}

void Tema1::InitEngine() {
    Mesh* EngineSquare = GenObjects::CreateSquare("EngineSquare", glm::vec3(0, 0, 0), size_standard, glm::vec3(1.0f, 0.55f, 0.0f), true);
    AddMeshToList(EngineSquare);

    float flameWidth = size_standard / 4.0f;
    float flameHeight = size_standard * 0.75f;

    glm::vec3 v1 = glm::vec3(0, 0, 0);
    glm::vec3 v2 = glm::vec3(flameWidth, 0, 0);
    glm::vec3 v3 = glm::vec3(flameWidth / 2.0f, -flameHeight, 0);

    glm::vec3 yellow = glm::vec3(1.0f, 1.0f, 0.0f);

    Mesh* flame = GenObjects::CreateTriangle("flame", v1, v2, v3, yellow, true);
    AddMeshToList(flame);
}

void Tema1::InitBumper() {
    Mesh* BumperSquare = GenObjects::CreateSquare("BumperSquare", glm::vec3(0, 0, 0), size_standard, glm::vec3(1.0, 1.0f, 1.0f), true);
    AddMeshToList(BumperSquare);

    Mesh* BumperSemicircle = GenObjects::CreateSemicircle("BumperSemicircle", 1.5f * size_standard, glm::vec3(0, 0, 0), glm::vec3(0.96f, 0.96f, 0.86f));
    AddMeshToList(BumperSemicircle);
}

void Tema1::InitGun() {
    Mesh* GunSquare = GenObjects::CreateSquare("GunSquare", glm::vec3(0, 0, 0), size_standard, glm::vec3(1.0, 1.0f, 1.0f), true);
    AddMeshToList(GunSquare);

    Mesh* GunSquare2 = GenObjects::CreateSquare("GunSquare2", glm::vec3(0, 0, 0), size_standard, glm::vec3(0.2f, 0.2f, 0.2f), true);
    AddMeshToList(GunSquare2);

    Mesh* GunSemicircle = GenObjects::CreateSemicircle("GunSemicircle", 0.5f * size_standard, glm::vec3(0, 0, 0), glm::vec3(0.8f, 0.8f, 0.8f));
    AddMeshToList(GunSemicircle);

    Mesh* GunTrapeze = GenObjects::CreateTrapeze("GunTrapeze", glm::vec3(0, 0, 0), size_standard, glm::vec3(0.2f, 0.2f, 0.2f), true);
    AddMeshToList(GunTrapeze);
}

void Tema1::InitText() {
    if (typeScreen == 1)
        m_textRenderer = new gfxc::TextRenderer(
        "../../..",
        window->GetResolution().x / 4,
        window->GetResolution().y / 4
        );
    else
        m_textRenderer = new gfxc::TextRenderer(
       "../../..",
       window->GetResolution().x,
       window->GetResolution().y
       );


    std::string fontPath = PATH_JOIN("../../..", RESOURCE_PATH::FONTS, "Hack-Bold.ttf");
    const GLuint fontSize = 20;
    m_textRenderer->Load(fontPath, fontSize);
}
void Tema1::Init()
{
    srand(static_cast<unsigned int>(time(NULL)));
    window->SetSize(1280, 720);
    glm::ivec2 resolution = window->GetResolution();
    if (resolution.x > 4000) {
        typeScreen = 1;
        macScale = 4;
    } else {
        typeScreen = 0;
        macScale = 1;
    }
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    startButtonColor = glm::vec3(1.0f, 0.0f, 0.0f);
    InitGame = 0;
    score = 0;
    lives = 3;
    size_standard = 50;
    paddleMove = 0;
    posBallX = 640;
    posBallY = 40;
    startGame = 0;
    angleBall = 45.0f * glm::pi<float>() / 180.0f;
    vBallX = 1.0f;
    vBallY = 1.0f;
    blockCount = 0;
    InitText();


    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 9; j++) {
            matrixGrid[i][j] = 0;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            matrixBlocks[i][j] = (rand() % 4) + 1;
            blockScales[i][j] = 1.0f;
        }
    }

    spaceshipPieces = 10;
    gridLength = 17;
    gridWidth = 9;

    objectMouseX = 0.0f;
    objectMouseY = 0.0f;
    onMove = false;
    objectOnMove = "";

    Mesh* RLineVer = GenObjects::CreateLine("RLineVer", 720.0f, glm::vec3(0, 0, 0), false, glm::vec3(1, 0, 0));
    AddMeshToList(RLineVer);

    Mesh* RLineHor = GenObjects::CreateLine("RLineHor", 250.0f, glm::vec3(0, 0, 0), true, glm::vec3(1, 0, 0));
    AddMeshToList(RLineHor);

    Mesh* BLineVert = GenObjects::CreateLine("BLineVert", 500.0f, glm::vec3(0, 0, 0), false, glm::vec3(0, 0, 1));
    AddMeshToList(BLineVert);

    Mesh* BLineHor = GenObjects::CreateLine("BLineHor", 900.0f, glm::vec3(0, 0, 0), true, glm::vec3(0, 0, 1));
    AddMeshToList(BLineHor);

    Mesh* ProgressSquare = GenObjects::CreateSquare("ProgressSquare", glm::vec3(0, 0, 0), 60.0f, glm::vec3(0,1,0), true);
    AddMeshToList(ProgressSquare);

    Mesh* GridSquare = GenObjects::CreateSquare("GridSquare", glm::vec3(0, 0, 0), 46.0f, glm::vec3(0.6f, 0.8f, 1.0f), true);
    AddMeshToList(GridSquare);

    InitSingleBlock();
    InitEngine();
    InitBumper();
    InitGun();

    Mesh* GameBlock4 = GenObjects::CreateSquare("GameBlock4", glm::vec3(0, 0, 0), 50.0f, colors[3], true);
    AddMeshToList(GameBlock4);

    Mesh* GameBlock3 = GenObjects::CreateSquare("GameBlock3", glm::vec3(0, 0, 0), 50.0f, colors[2], true);
    AddMeshToList(GameBlock3);

    Mesh* GameBlock2 = GenObjects::CreateSquare("GameBlock2", glm::vec3(0, 0, 0), 50.0f, colors[1], true);
    AddMeshToList(GameBlock2);

    Mesh* GameBlock1 = GenObjects::CreateSquare("GameBlock1", glm::vec3(0, 0, 0), 50.0f, colors[0], true);
    AddMeshToList(GameBlock1);

    Mesh* GameBall = GenObjects::CreateCircle("GameBall", 10, glm::vec3(0,0,0), glm::vec3(0.7f, 0.7f, 0.7f));
    AddMeshToList(GameBall);

    InitStartButton();
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 logicSize = window->GetResolution();

    if (typeScreen == 1) {
        glViewport(0, 0, logicSize.x * 2, logicSize.y * 2);
    }
}

void Tema1::DFS_CheckConex(int c, int r, bool visited[17][9], int& count) {
    int rows = 9;
    int cols = 17;
    int dc[] = {0, 0, -1, 1};
    int dr[] = {-1, 1, 0, 0};

    if (c < 0 || c >= cols || r < 0 || r >= rows ||
        matrixGrid[c][r] <= 0 || visited[c][r]) {
        return;
        }

    visited[c][r] = true;
    count++;

    for (int i = 0; i < 4; i++) {
        DFS_CheckConex(c + dc[i], r + dr[i], visited, count);
    }
}

int Tema1::CheckConex() {
    int total_pieces = 0;
    int start_r = -1, start_c = -1;
    int rows = 9;
    int cols = 17;

    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (matrixGrid[c][r] > 0) {
                total_pieces++;
                if (start_c == -1) {
                    start_c = c;
                    start_r = r;
                }
            }
        }
    }

    if (total_pieces <= 1) {
        return 1;
    }

    bool visited[17][9] = {false};
    int visited_pieces = 0;

    DFS_CheckConex(start_c, start_r, visited, visited_pieces);

    return visited_pieces == total_pieces;
}

void Tema1::EditorGrid() {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 0);
    RenderMesh2D(meshes["RLineVer"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 180);
    RenderMesh2D(meshes["RLineHor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 360);
    RenderMesh2D(meshes["RLineHor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 540);
    RenderMesh2D(meshes["RLineHor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 25);
    RenderMesh2D(meshes["BLineVert"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1200, 25);
    RenderMesh2D(meshes["BLineVert"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 25);
    RenderMesh2D(meshes["BLineHor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 525);
    RenderMesh2D(meshes["BLineHor"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < spaceshipPieces; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(270 + i * 93, 600);
        RenderMesh2D(meshes["ProgressSquare"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridWidth; j++) {
            if (matrixGrid[i][j] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(330 + i * 50, 450 - (j * 50));
                RenderMesh2D(meshes["GridSquare"], shaders["VertexColor"], modelMatrix);
            }
        }

    }

    if (spaceshipPieces != 10 && CheckConex() == 1) {
        startButtonColor = glm::vec3(0, 1, 0);
        InitStartButton();
    } else {
        startButtonColor = glm::vec3(1, 0, 0);
        InitStartButton();
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1240, 630);
    RenderMesh2D(meshes["StartTriangle1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1240, 630);
    RenderMesh2D(meshes["StartTriangle2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1240, 630);
    RenderMesh2D(meshes["StartTriangle3"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderSingleBlock(float x, float y) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(meshes["SingleSquare"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderEngine(float x, float y) {
    float flameWidth = size_standard/4;

    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);

    RenderMesh2D(meshes["EngineSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(meshes["flame"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + flameWidth, y);
    RenderMesh2D(meshes["flame"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + 2 * flameWidth, y);
    RenderMesh2D(meshes["flame"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + 3 * flameWidth, y);
    RenderMesh2D(meshes["flame"], shaders["VertexColor"], modelMatrix);

}

void Tema1::RenderBumper(float x, float y) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + size_standard / 2, y + size_standard);
    modelMatrix *= transform2D::Scale(1, 0.65f);
    RenderMesh2D(meshes["BumperSemicircle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(meshes["BumperSquare"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderGun(float x, float y) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + size_standard / 2, y + size_standard * 0.9);
    RenderMesh2D(meshes["GunSemicircle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(meshes["GunSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y + size_standard);
    RenderMesh2D(meshes["GunSquare2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y + (2 * size_standard));
    RenderMesh2D(meshes["GunSquare2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x + size_standard * 0.1, y + size_standard * 2);
    modelMatrix *= transform2D::Translate(size_standard, size_standard);
    modelMatrix *= transform2D::Rotate(glm::pi<float>());
    modelMatrix *= transform2D::Scale(0.6, 1);
    RenderMesh2D(meshes["GunTrapeze"], shaders["VertexColor"], modelMatrix);
}

void Tema1::UpdateGrid () {
    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridWidth; j++) {
            if (matrixGrid[i][j] == 1) {
                RenderSingleBlock(328 + i * 50, 448 - (j * 50));
            } else if (matrixGrid[i][j] == 2) {
                RenderEngine(328 + i * 50, 448 - (j * 50));
            } else if (matrixGrid[i][j] == 3) {
                RenderGun(328 + i * 50, 448 - (j * 50));
            } else if (matrixGrid[i][j] == 4) {
                RenderBumper(328 + i * 50, 448 - (j * 50));
            }
        }
    }
}

void Tema1::EditorUpdate() {
    if (onMove) {
        if (objectOnMove == "SingleSquare") {
            RenderSingleBlock(objectMouseX - 23, objectMouseY - 23);
        }
        else if (objectOnMove == "Engine") {
            RenderEngine(objectMouseX - 23, objectMouseY - 23);
        }
        else if (objectOnMove == "Gun") {
            RenderGun(objectMouseX - 23, objectMouseY - 23);
        }
        else if (objectOnMove == "Bumper") {
            RenderBumper(objectMouseX - 23, objectMouseY - 23);
        }
    }
    UpdateGrid();
    EditorGrid();

    RenderSingleBlock(102, 67);
    RenderEngine(102, 270);
    RenderGun(102, 382);
    RenderBumper(102, 585);
}

void Tema1::AddSpaceshipInGame() {
    comps.clear();
    int min_x = gridLength;
    int max_x = 0;
    int min_y = gridWidth;
    int max_y = 0;

    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridWidth; j++) {
            if (matrixGrid[i][j] > 0) {

                if (i < min_x) min_x = i;
                if (i > max_x) max_x = i;
                if (j < min_y) min_y = j;
                if (j > max_y) max_y = j;

                spaceship_t curr = {};
                curr.x = i;
                curr.y = j;
                curr.type = matrixGrid[i][j];
                comps.push_back(curr);
            }
        }
    }

    int spaceshipWidthBlocks = max_x - min_x + 1;
    float spaceshipWidthPixels = spaceshipWidthBlocks * size_standard;

    SceneCenter = (1280.0f / 2.0f) - (spaceshipWidthPixels / 2.0f);

    for (auto i : comps) {

        paddleX = (i.x - min_x) * size_standard + SceneCenter + paddleMove;
        paddleY = (max_y - i.y) * size_standard;

        if (i.type == 1) {
            RenderSingleBlock(paddleX, paddleY);
        } else if (i.type == 2) {
            RenderEngine(paddleX, paddleY);
        } else if (i.type == 3) {
            RenderGun(paddleX, paddleY);
        } else if (i.type == 4) {
            RenderBumper(paddleX, paddleY);
        }
    }

    paddleLength = spaceshipWidthBlocks * size_standard;
    int spaceshipHeightBlocks = max_y - min_y + 1;

    if (startGame == 0) {
        posBallY = 10 + spaceshipHeightBlocks * size_standard;
    }
    paddleHeight = spaceshipHeightBlocks * size_standard;
}

void Tema1::GameUpdate(float deltaTimeSeconds) {
    AddSpaceshipInGame();
    std::string score_str = "Score: " + std::to_string(score);
    std::string lives_str = "Lives: " + std::to_string(lives);
    if (typeScreen == 1) {
        m_textRenderer->RenderText(score_str, 10.0f, 541.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
        m_textRenderer->RenderText(lives_str, 250.0f, 541.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
    } else {
        m_textRenderer->RenderText(score_str, 30.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        m_textRenderer->RenderText(lives_str, 1150.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 685);
    modelMatrix *= transform2D::Scale(1.5, 1);
    RenderMesh2D(meshes["BLineHor"], shaders["VertexColor"], modelMatrix);

    if (startGame == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posBallX, posBallY);
        RenderMesh2D(meshes["GameBall"], shaders["VertexColor"], modelMatrix);
    } else {
        posBallX += speed * cos(angleBall) * vBallX;
        posBallY += speed * sin(angleBall) * vBallY;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posBallX, posBallY);
        RenderMesh2D(meshes["GameBall"], shaders["VertexColor"], modelMatrix);

        float ballLeft = posBallX - ballRadius;
        float ballRight = posBallX + ballRadius;
        float ballTop = posBallY + ballRadius;
        float ballBottom = posBallY - ballRadius;

        float paddleLeft = SceneCenter + paddleMove;
        float paddleRight = paddleLeft + paddleLength;
        float paddleBottom = 0;
        float paddleTop = paddleHeight;

        if (ballRight >= highX || ballLeft <= lowX) {
            vBallX *= -1;
        }
        if (ballTop >= highY) {
            vBallY *= -1;
        }

        bool collisionDetected = false;

        if (ballRight > paddleLeft &&
            ballLeft < paddleRight &&
            ballTop > paddleBottom &&
            ballBottom < paddleTop &&
            vBallY < 0)
        {
            vBallY *= -1;
            posBallY = paddleTop + ballRadius;

            collisionDetected = true;

            float paddleCenter_X = paddleLeft + (paddleLength / 2.0f);
            float impactOffset = posBallX - paddleCenter_X;

            float normalizedImpact = impactOffset / (paddleLength / 2.0f);

            vBallX = normalizedImpact;
        }

        if (!collisionDetected && ballBottom <= lowY) {
            startGame = 0;
            lives--;

            if (lives == 0)
                InitGame = -1;

            posBallX = 640;
            posBallY = 40;
            vBallX = 1;
            vBallY = 1;
            paddleMove = 0;
        }

        if (posBallX <= blocksHighX - ballRadius && posBallX >= blocksLowX + ballRadius
            && posBallY <= blocksHighY - ballRadius && posBallY >= blocksLowY + ballRadius) {
                int x = posBallX / 107;
                int y = (blocksHighY - posBallY) / 52;
                if (matrixBlocks[y][x] > 0) {
                    matrixBlocks[y][x] --;
                    if (matrixBlocks[y][x] == 0)
                        blockCount++;
                    if (blockCount == 12 * 5)
                        InitGame = -1;
                    score++;
                    vBallY *= -1;
                }
            }
    }

    int blocksLength = 12;
    int blocksWidth = 5;
    for (int i = 0; i < blocksLength; i++) {
        for (int j = 0; j < blocksWidth; j++) {
            if (matrixBlocks[j][i] == 4) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(i * 107, 620 - (j * 52));
                modelMatrix *= transform2D::Scale(2.1, 1);
                RenderMesh2D(meshes["GameBlock4"], shaders["VertexColor"], modelMatrix);
            } else if (matrixBlocks[j][i] == 3) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(i * 107, 620 - (j * 52));
                modelMatrix *= transform2D::Scale(2.1, 1);
                RenderMesh2D(meshes["GameBlock3"], shaders["VertexColor"], modelMatrix);
            } else if (matrixBlocks[j][i] == 2) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(i * 107, 620 - (j * 52));
                modelMatrix *= transform2D::Scale(2.1, 1);
                RenderMesh2D(meshes["GameBlock2"], shaders["VertexColor"], modelMatrix);
            } else if (matrixBlocks[j][i] == 1) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(i * 107, 620 - (j * 52));
                modelMatrix *= transform2D::Scale(2.1, 1);
                RenderMesh2D(meshes["GameBlock1"], shaders["VertexColor"], modelMatrix);
            } else if (matrixBlocks[j][i] == 0) {
                blockScales[j][i] -= deltaTimeSeconds * 2.0f;
                if (blockScales[j][i] <= 0.0f) {
                    matrixBlocks[j][i] = -1;
                } else {
                    float blockWidth = 50.0f * 2.1f;
                    float blockHeight = 50.0f;

                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(i * 107, 620 - (j * 52));
                    modelMatrix *= transform2D::Translate(blockWidth / 2.0f, blockHeight / 2.0f);
                    modelMatrix *= transform2D::Scale(blockScales[j][i], blockScales[j][i]);
                    modelMatrix *= transform2D::Translate(-blockWidth / 2.0f, -blockHeight / 2.0f);
                    modelMatrix *= transform2D::Scale(2.1, 1);
                    RenderMesh2D(meshes["GameBlock1"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
    }

}

void Tema1::EndGame() {
    string end = "EndGame";
    string score_str = "Final score: " + std::to_string(score);
    if (typeScreen == 1) {
        m_textRenderer->RenderText(end, 110.0f, 600.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        m_textRenderer->RenderText(score_str, 70.0f, 630.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    } else {
        m_textRenderer->RenderText(end, 450.0f, 250.0f, 5.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        m_textRenderer->RenderText(score_str, 250.0f, 350.0f, 5.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}

void Tema1::Update(float deltaTimeSeconds) {
    if (InitGame == 0) {
        EditorUpdate();
    } else if (InitGame == 1){
        GameUpdate(deltaTimeSeconds);
    } else if (InitGame == -1) {
        EndGame();
    }

}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    float minPaddleMove = lowX - SceneCenter;
    float maxPaddleMove = highX - SceneCenter - paddleLength;

    if (window->KeyHold(263) && startGame == 1 ) {
        paddleMove = max(minPaddleMove,paddleMove - deltaTime * 500);
    }

    if (window->KeyHold(262) && startGame == 1) {
        paddleMove = min(maxPaddleMove, paddleMove + deltaTime * 500);
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_B) {
        InitGame = 0;
        size_standard = 50;
        InitSingleBlock();
        InitEngine();
        InitGun();
        InitBumper();
    }

    if (key == GLFW_KEY_SPACE && InitGame == 1) {
        startGame = 1;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    glm::ivec2 resolution = window->GetResolution();

    objectMouseX = (float)mouseX * macScale / (float)resolution.x * 1280.0f;

    float flippedMouseY = (float)(resolution.y - mouseY * macScale);
    objectMouseY = (flippedMouseY / (float)resolution.y) * 720.0f;

    // objectMouseX = (float)mouseX;
    // objectMouseY = (float)(resolution.y - mouseY);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (spaceshipPieces >= 0) {
            glm::ivec2 resolution = window->GetResolution();

            float worldX = (float)mouseX * macScale / (float)resolution.x * 1280.0f;
            float flippedMouseY = (float)(resolution.y - mouseY * macScale);
            float worldY = (flippedMouseY / (float)resolution.y) * 720.0f;
            float size = 50.0f;

            if (worldX >= 102 && worldX <= (102 + size) &&
                worldY >= 67 && worldY <= (67 + size)) {
                onMove = true;
                objectOnMove = "SingleSquare";
                objectMouseX= worldX;
                objectMouseY = worldY;
                }
            else if (worldX >= 102 && worldX <= (102 + size) &&
                     worldY >= 270 && worldY <= (270 + size)) {
                onMove = true;
                objectOnMove = "Engine";
                objectMouseX = worldX;
                objectMouseY = worldY;
                     }
            else if (worldX >= 79 && worldX <= (102 + size * 2) &&
                     worldY >= 382 && worldY <= (382 + size * 4)) {
                onMove = true;
                objectOnMove = "Gun";
                objectMouseX = worldX;
                objectMouseY = worldY;
                     }
            else if (worldX >= 56 && worldX <= (102 + size * 2) &&
                     worldY >= 585 && worldY <= (585 + size + 69)) {
                onMove = true;
                objectOnMove = "Bumper";
                objectMouseX = worldX;
                objectMouseY = worldY;
                     }
            else if (worldX > 1200 && worldX < 1270 && worldY > 600 && worldY < 660
                && startButtonColor == glm::vec3(0, 1, 0)) {
                InitGame = 1;
                size_standard *= 0.5;
                InitSingleBlock();
                InitEngine();
                InitGun();
                InitBumper();
                paddleMove = 0;
            }
        }
    }


    if (button == 2) {
        int x = (int)((objectMouseX - 330) / 50);
        int y = (int)((450 - (objectMouseY - 50)) / 50);
        if (matrixGrid[x][y]) {
            if (matrixGrid[x][y] == 1) {
                matrixGrid[x][y] = 0;
            } else if (matrixGrid[x][y] == 2) {
                for (int i = y + 1; i < 9; i++) {
                    matrixGrid[x][i] = 0;
                }
                matrixGrid[x][y] = 0;
            } else if (matrixGrid[x][y] == 3) {
                for (int i = y - 1; i >= 0; i--) {
                    matrixGrid[x][i] = 0;
                }
                matrixGrid[x][y] = 0;
            } else if (matrixGrid[x][y] == 4) {
                for (int i = y - 1; i >= 0; i--) {
                    for (int j = x + 1; j >= x - 1; j--) {
                        matrixGrid[j][i] = 0;
                    }
                }
                matrixGrid[x][y] = 0;
            }
            if (spaceshipPieces < 10)
            spaceshipPieces++;
        }

    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && onMove == true) {
        if (objectMouseX > 330 && objectMouseX < 1240 && objectMouseY > 0 && objectMouseY < 500) {
            int x = (int)((objectMouseX - 330) / 50);
            int y = (int)((450 - (objectMouseY - 50)) / 50);

            if (objectOnMove == "SingleSquare") {
                if (matrixGrid[x][y] == 0) {
                    matrixGrid[x][y] = 1;
                    spaceshipPieces--;
                }
            }
            else if (objectOnMove == "Engine") {
                if (y < 8) {
                        matrixGrid[x][y] = 2;
                        spaceshipPieces--;
                        for (int i = y + 1; i < 9; i++) {
                            matrixGrid[x][i] = -1;
                        }

                }
            }
            else if (objectOnMove == "Gun") {
                if (y > 1 && matrixGrid[x + 1][y] != 4 && matrixGrid[x - 1][y] != 4) {
                    matrixGrid[x][y] = 3;
                    spaceshipPieces--;
                    for (int i = y - 1; i >= 0; i--) {
                        matrixGrid[x][i] = -1;
                    }
                }
            }
            else if (objectOnMove == "Bumper") {
                if (y > 0 && x > 0 && x < 16 && matrixGrid[x + 1][y] != 4 && matrixGrid[x - 1][y] != 4) {
                    for (int i = y - 1; i >= 0; i--) {
                        for (int j = x + 1; j >= x - 1; j--) {
                            matrixGrid[j][i] = -1;
                        }
                    }
                    matrixGrid[x][y] = 4;
                    spaceshipPieces--;
                }
            }
        }

        onMove = false;
        objectOnMove = "";
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
    glm::ivec2 logicSize = window->GetResolution();
    if (logicSize.x > 4000)
        glViewport(0, 0, logicSize.x * 2, logicSize.y * 2);
}