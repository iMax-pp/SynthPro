#include "testsampler.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/keyboard.h"
#include "abstraction/module/speaker.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>


void TestSampler::testSampler()
{
    QFile file("sampler.out");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    QFile bufferFile("buffer.out");
    bufferFile.open(QIODevice::WriteOnly);
    QTextStream bufferOut(&bufferFile);



    out << "start\n";
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Sampler* sampler = factory.createSampler(synth);
    Speaker* speaker = factory.createSpeaker(synth);
    Keyboard* keyboard = factory.createKeyboard(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(sampler->inports().first());
    keyboard->outports().at(1)->connect(sampler->inports().at(1));
    sampler->outports().first()->connect(speaker->inports().first());
    // initialization of the gate port

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    vco->process();
    sampler->process();

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;

    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; ++i) {
        out << i << " " <<  sampler->inports().first()->buffer()->data()[i]   << " " << sampler->outports().first()->buffer()->data()[i] << "\n";
    }

    for (int i = 0 ; i < sampler->sampleBuffer()->length() ; i++) {
        // bufferOut << i << " " << sampler->sampleBuffer()->data()[i] << "\n";
    }


    file.close();
    bufferFile.close();
}
