#pragma once
class Spawner {
public:
    Spawner();

    void ReadConfig();
    void CreateEnemies(int p_iLevel, class GraphicObjects*** p_EnemiesArray, int* p_iNbEnemybyColorArray);
    void SpawnRandomBonus(Vector2 p_Position);
    void DefineBonusToGenerate();

};