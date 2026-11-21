#include "game.hpp"

Game::Game() {

    SetExitKey(KEY_NULL);

    data.readData(DataMapIndex::DEV_MAP);
}
 
// I should be revising than doing coding. LOL

Game::~Game() {

    // data.writeData(DataMapIndex::DEV_MAP);
}

void Game::handleUpdating() {

    BeginDrawing();
    {
        ClearBackground(BLACK);

        updateGame();
        applyFX();

#if ENABLE_RENDERDOC

        if(RendererDebugger::isRenderDocFrameCapturing())
            RendererDebugger::endRenderDocCapture();

#endif
        nkHandler.draw();
    }   
    EndDrawing();
}

void Game::gameLoop() {

    while(!WindowShouldClose()) {

        nkHandler.update();
        handleUpdating();
    }

    CloseWindow();
}

void Game::updateGame() {

    world.update(player.getCameraMovement());
    player.update();

    UI::drawBases({Utils::THE_DEBUG_RECT.x, Utils::THE_DEBUG_RECT.y}, {6, 3});

    button.active = button.getState(UI::Button_State::MOUSE_HOVER);
    button.update(Utils::THE_DEBUG_VECTOR);

    world.setpickedTile((TileType) Utils::selectedtileTypeIndex);
}

void Game::applyFX() {

    BeginBlendMode(BLEND_ADDITIVE);
    {
        
        DrawTextureV(classicImage, {1800, 100}, WHITE);
        renderer.drawResult();
    }
    EndBlendMode();

    renderer.beginTargetRender();
    {
        ClearBackground(BLACK);
        
        DrawTextureV(classicImage, {800, 800}, WHITE);
    }
    renderer.endTargetRender();

    renderer.setCurrentShader((ShaderIndex) Utils::shaderIndex);
    renderer.applyShader({player.getObject().x, GetScreenHeight() - player.getObject().y});
}
