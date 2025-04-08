/**
* Author: [Your name here]
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Level0.h"
#include "Utility.h"

#define LEVEL_WIDTH 1
#define LEVEL_HEIGHT 1
#define LEVEL_NUM 0

constexpr char SPRITESHEET_FILEPATH[] = "assets/george_0.png",
PLATFORM_FILEPATH[] = "assets/platformPack_tile027.png",
ENEMY_FILEPATH[] = "assets/soph.png",
FONTSHEET_FILEPATH[] = "assets/font1.png";

GLuint g_font_texture_id0;

unsigned int LEVEL0_DATA[] = {0};


Level0::~Level0()
{
    delete    m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void Level0::initialise()
{   
    g_font_texture_id0 = Utility::load_texture(FONTSHEET_FILEPATH);

    GLuint map_texture_id = Utility::load_texture("assets/tileset.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL0_DATA, map_texture_id, 1.0f, 4, 1);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    //int player_walking_animation[4][4] =
    //{
    //    { 1, 5, 9, 13 },  // for George to move to the left,
    //    { 3, 7, 11, 15 }, // for George to move to the right,
    //    { 2, 6, 10, 14 }, // for George to move upwards,
    //    { 0, 4, 8, 12 }   // for George to move downwards
    //};

    //glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    //m_game_state.player = new Entity(
    //    player_texture_id,         // texture id
    //    5.0f,                      // speed
    //    acceleration,              // acceleration
    //    2.0f,                      // jumping power
    //    player_walking_animation,  // animation index sets
    //    0.0f,                      // animation time
    //    4,                         // animation frame amount
    //    0,                         // current animation index
    //    4,                         // animation column amount
    //    4,                         // animation row amount
    //    1.0f,                      // width
    //    1.0f,                       // height
    //    PLAYER
    //);
    
    //m_game_state.player->set_position(glm::vec3(4.0f, 0.0f, 0.0f));

    //// Jumping
    //m_game_state.player->set_jumping_power(4.0f);
    //
    ///**
    // Enemies' stuff */
    //GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    //m_game_state.enemies = new Entity[ENEMY_COUNT];

    //for (int i = 0; i < ENEMY_COUNT; i++)
    //{
    //m_game_state.enemies[i] =  Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
    //}


    /*m_game_state.enemies[0].set_position(glm::vec3(7.0f, 0.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));*/

    m_game_state.next_scene_id = 1;

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS("assets/bgm.wav");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(64.0f);
    
    m_game_state.jump_sfx = Mix_LoadWAV("assets/bounce.wav");
    m_game_state.menu_sfx = Mix_LoadWAV("assets/menu.wav");
}

void Level0::update(float delta_time)
{
    //m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    //
    //for (int i = 0; i < ENEMY_COUNT; i++)
    //{
    //    m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    //}

    //if (m_game_state.player->get_position().y < -3.0f)
    //{
    //    finish = true;
    //}
}


void Level0::render(ShaderProgram *g_shader_program, int life)
{
    m_game_state.map->render(g_shader_program);
    //m_game_state.player->render(g_shader_program);
    //for (int i = 0; i < m_number_of_enemies; i++)
            //m_game_state.enemies[i].render(g_shader_program);

    Utility::draw_text(g_shader_program, g_font_texture_id0, "Press enter to start ", 0.4f, 0.05f,
        glm::vec3(-4.2f, 0.0f, 0.0f));
    
}

