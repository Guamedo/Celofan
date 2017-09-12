#ifndef CELOFAN_TIMING_H
#define CELOFAN_TIMING_H

namespace Celofan{

    class FPSLimiter{
    public:
        FPSLimiter();
        void init(float maxFPS);

        void setMaxFPS(float maxFPS);

        void begin();
        float end();

    private:
        void calculateFPS();

        float _maxFPS;
        float _fps;
        float _frameTime;
        unsigned int _startTicks;
    };

}

#endif //CELOFAN_TIMING_H
