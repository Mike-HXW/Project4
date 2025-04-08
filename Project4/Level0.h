#include "Scene.h"

class Level0 : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    int ENEMY_COUNT = 0;
    bool finish = false;

    // ————— DESTRUCTOR ————— //
    ~Level0();

    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program, int life) override;
};
