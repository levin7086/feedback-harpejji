class FeedbackDelay 
{
public:

    void init(int delayLengthSamples)
    {
        this->circBuf = new float[delayLengthSamples];
        this->circBufPos = 0;
        this->delayLengthSamples = delayLengthSamples;
        for (int i = 0; i < delayLengthSamples; i++)
        {
                circBuf[i] = 0;
        }
    }

    float process(float sample)
    {
        int readFrom = (circBufPos + 1) % delayLengthSamples;
        float output = (1 - 0.4) * sample + 0.6 * circBuf[readFrom];
        circBuf[readFrom] = output;
        circBufPos = (circBufPos + 1) % delayLengthSamples;
        return output;
    }
private:
    float * circBuf;
    int circBufPos;
    int delayLengthSamples;
};
