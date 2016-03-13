//
// Created by dar on 11/25/15.
//

#ifndef C003_CORE_H
#define C003_CORE_H
#pragma once

#include "map/entity/SimpleShape.h"
#include "map/Map.h"
#include "map/entity/EntityPlayer.h"

class Core {

public:
    Core(Map *map) : map(map) {
#ifdef __ANDROID__
        defaultBlockSize = blockSize = 96.0f;
#else
        defaultBlockSize = blockSize = 64.0f;
#endif //__ANDROID__
        if (this->player == nullptr) {
            for (Entity *e : map->getEntities()) {
                if (Player *p = dynamic_cast<Player *>(e)) {
                    this->player = p;
                    break;
                }
            }
        }
    }

    Map *getMap() const {
        return map;
    }

    double getCamX() const {
        return -camX;
    }

    void setCamX(double camX) {
        Core::camX = camX;
    }

    double getCamY() const {
        return -camY;
    }

    void setCamY(double camY) {
        Core::camY = camY;
    }

    bool isRunning() {
        return this->running;
    }

    void stop() {
        this->running = false;
    }

    Player *getPlayer() const {
        return player;
    }

    void setPlayer(Player *player) {
        Core::player = player;
    }

    double getGeneralScale() const {
        return generalScale;
    }

    void setGeneralScale(double generalScale) {
        Core::generalScale = generalScale;
    }

    double getDefaultBlockSize() const {
        return defaultBlockSize;
    }

    double getBlockSize() const {
        return blockSize;
    }

    void setBlockSize(double blockSize) {
        Core::blockSize = blockSize;
    }

private:
    bool running = true;
    Map *map;
    Player *player = nullptr;
    double camX = 0, camY = 0;
    double generalScale = 1.0;
    double defaultBlockSize;
    double blockSize;
};

#endif //C003_CORE_H
