#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8
#define LEVEL_NUM 2

constexpr char SPRITESHEET_FILEPATH[] = "assets/player.png",
ENEMY_FILEPATH[] = "assets/spinner.png",
FONTSHEET_FILEPATH[] = "assets/font1.png";

GLuint g_font_texture_id2;

unsigned int LEVELB_DATA[] =
{
    25,23,23,23,23,23,23,23,23,23,23,23,23,23,
    25,23,23,23,23,23,23,23,23,23,23,23,23,23,
    25,23,23,23,23,23,23,23,23,23,23,23,23,23,
    25,23,23,23,23,22,23,23,23,23,23,23,23,23,
    25,23,23,23,23,25,22,22,22,22,23,23,23,22,
    25,23,23,22,23,23,23,23,23,23,23,23,23,25,
    25,22,22,25,23,23,23,23,22,22,22,22,22,25,
    25,25,25,25,23,23,23,23,25,25,25,25,25,25
};

LevelB::~LevelB()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise()
{

    g_font_texture_id2 = Utility::load_texture(FONTSHEET_FILEPATH);

    GLuint map_texture_id = Utility::load_texture("assets/grasssheet.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 6, 7);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    int player_walking_animation[4][4] =
    {
        { 0, 3, 0, 6 },  // for George to move to the left,
        { 0, 3, 0, 6 }, // for George to move to the right,
        { 0, 3, 0, 6 }, // for George to move upwards,
        { 0, 3, 0, 6 }   // for George to move downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        1.5f,                      // speed
        acceleration,              // acceleration
        2.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        9,                         // animation column amount
        3,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
    
    m_game_state.player->set_position(glm::vec3(1.5f, 0.0f, 0.0f));

    // Jumping
    m_game_state.player->set_jumping_power(4.5f);
    
    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
    m_game_state.enemies[i] =  Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
    }


    m_game_state.enemies[0].set_position(glm::vec3(8.0f, -5.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));

    m_game_state.next_scene_id = 3;
    m_game_state.finish = false;
    m_game_state.restart = false;

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS("assets/bgm.wav");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(64.0f);
    
    m_game_state.jump_sfx = Mix_LoadWAV("assets/bounce.wav");
    m_game_state.die_sfx = Mix_LoadWAV("assets/die.wav");
    m_game_state.next_sfx = Mix_LoadWAV("assets/next.wav");
}

void LevelB::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    if (m_game_state.player->get_position().y < -7.0f && m_game_state.player->get_position().x > 7.0f)
    {
        m_game_state.finish = true;
    }

    if (m_game_state.player->check_collision(m_game_state.enemies) || (m_game_state.player->get_position().y < -7.0f && m_game_state.player->get_position().x <= 7.0f))
    {
        m_game_state.restart = true;
    }
}


void LevelB::render(ShaderProgram *g_shader_program, int life)
{
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    for (int i = 0; i < m_number_of_enemies; i++)
            m_game_state.enemies[i].render(g_shader_program);

    float offset = 0.0f;

    if (m_game_state.player->get_position().x > 5.0)
    {
        offset = m_game_state.player->get_position().x - 5.0f;
    }

    Utility::draw_text(g_shader_program, g_font_texture_id2, "Level " + std::to_string(LEVEL_NUM), 0.3f, 0.05f,
        glm::vec3(0.1f+offset, -0.3f, 0.0f));

    Utility::draw_text(g_shader_program, g_font_texture_id2, "Life " + std::to_string(life), 0.3f, 0.05f,
        glm::vec3(8.0f+offset, -0.3f, 0.0f));

    if (life == 0) {
        Utility::draw_text(g_shader_program, g_font_texture_id2, "You Lose", 0.5f, 0.05f,
            glm::vec3(3.0f+offset, -3.0f, 0.0f));
    }
}

