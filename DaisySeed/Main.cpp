#include "daisy_seed.h"
#include "Filter.cpp"
#include "daisysp.h"
#include "FeedbackDelay.cpp"

using namespace daisy;

DaisySeed hardware;
HighpassFilter hpFilter;
LowpassFilter lpFilter;
daisysp::Chorus chorus;
daisysp::Overdrive dist;
FeedbackDelay delay;

void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t                                size)
{
    for (size_t i = 0; i < size; i += 2)
    {
        float sample = in[i];
        sample += in[i + 1];
        sample /= 2;
        sample = hpFilter.processSample(sample);
        sample = lpFilter.processSample(sample);
        out[i] = sample;
        float fdbSample = dist.Process(sample);
        fdbSample = 0.6 * chorus.Process(fdbSample) + 0.4 * fdbSample;
        fdbSample = delay.process(fdbSample);
        out[i + 1] = fdbSample * 0.05;
    }
}

int main(void)
{
    hardware.Configure();
    hardware.Init();
    hardware.SetAudioBlockSize(4);
    float samplerate = hardware.AudioSampleRate();
    hardware.SetLed(true);
    hpFilter.init(samplerate,140 , 4);
    lpFilter.init(samplerate, 739, 4);
    chorus.Init(samplerate);
    chorus.SetLfoDepth(0.899);
    chorus.SetLfoFreq(2.34);
    chorus.SetFeedback(0.6);
    chorus.SetDelay(0.04);
    dist.SetDrive(0.3);
    delay.init(2048);
    hardware.StartAudio(AudioCallback);
    for(;;){
    }
}