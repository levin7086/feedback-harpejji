#include "math.h"

class HighpassFilter
{
public:
    void init(float samplerate, float cutoff, int bufferLength)
    {
        this->bufferLength = bufferLength;
        this->samplerate = samplerate;
        Fc = cutoff;
    }

    float processSample(float in)
    {
        float b_0, b_1, b_2, a_0, a_1, a_2;
        cirBuffIn[buffPos % 4] = in;
        float Q = 1.22;
        float w0 = 2.f * M_PI * (Fc / samplerate);
        float cosW0 =  cos(w0);
        float alph = (sin(w0)) / (2.f * Q);

        a_0 = 1 + alph;
        b_0 = ((float (1 + cosW0)) / 2.f) / a_0;
        b_1 = (-1.f * (1.f + cosW0)) / a_0;
        b_2 = ((1.f + cosW0) / 2.f) / a_0;
        a_1 = (-2 * cosW0) / a_0;
        a_2 = (1 - alph) / a_0;

        float n_1 = cirBuffIn[(4 + buffPos - 1) % 4];
        float n_2 = cirBuffIn[(4 + buffPos - 2) % 4];
        float yn_1 = cirBuffOut[(4 + buffPos - 1) % 4];
        float yn_2 = cirBuffOut[(4 + buffPos - 2) % 4];

        float fltOut = in * b_0 + n_1 * b_1 + n_2 * b_2 - yn_1 * a_1 - yn_2 * a_2;
        cirBuffOut[buffPos % 4] = fltOut;
        buffPos++;
        if(buffPos == 4) {
            buffPos = 0;
        }
        return fltOut;
}
private:
    float cirBuffIn[4];
    float cirBuffOut[4];
    int buffPos = 0;
    int bufferLength;
    float samplerate;
    float Fc;
};

class LowpassFilter
{
public:
    void init(float samplerate, float cutoff, int bufferLength)
    {
        this->bufferLength = bufferLength;
        this->samplerate = samplerate;
        Fc = cutoff;
    }

    float processSample(float in)
    {
        float b_0, b_1, b_2, a_0, a_1, a_2;
        cirBuffIn[buffPos % 4] = in;
        float Q = 1.22;
        float w0 = 2.f * M_PI * (Fc / samplerate);
        float cosW0 =  cos(w0);
        float alph = (sin(w0)) / (2.f * Q);

        a_0 = 1 + alph;
        b_0 = ((float (1 - cosW0)) / 2.f) / a_0;
        b_1 = (1.f - cosW0) / a_0;
        b_2 = ((1.f - cosW0) / 2.f) / a_0;
        a_1 = (-2 * cosW0) / a_0;
        a_2 = (1 - alph) / a_0;

        float n_1 = cirBuffIn[(4 + buffPos - 1) % 4];
        float n_2 = cirBuffIn[(4 + buffPos - 2) % 4];
        float yn_1 = cirBuffOut[(4 + buffPos - 1) % 4];
        float yn_2 = cirBuffOut[(4 + buffPos - 2) % 4];

        float fltOut = in * b_0 + n_1 * b_1 + n_2 * b_2 - yn_1 * a_1 - yn_2 * a_2;
        cirBuffOut[buffPos % 4] = fltOut;
        buffPos++;
        if(buffPos == 4) {
            buffPos = 0;
        }
        return fltOut;
}
private:
    float cirBuffIn[4];
    float cirBuffOut[4];
    int buffPos = 0;
    int bufferLength;
    float samplerate;
    float Fc;
};