#include "SoundManager.hpp"

SoundManager::SoundManager()
    : _context(lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo)),
      _previousVolume(1.0f),
      _muted(false) {
  _gain = std::make_shared<lab::GainNode>();
  _gain->gain()->setValue(1.0f);
}

void SoundManager::LoadClip(const std::string& filename) {
  _files[filename] = lab::MakeBusFromFile(filename, false);
  _samples[filename] = std::make_shared<lab::SampledAudioNode>();

  {
    lab::ContextRenderLock r(_context.get(), "SoundManager");
    _samples[filename]->setBus(r, _files[filename]);
  }

  _context->connect(_gain, _samples[filename]);
  _context->connect(_context->destination(), _gain, 0, 0);
}

void SoundManager::Play(const std::string& filename) {
  _samples[filename]->start(0.0f);
  _samples[filename]->setLoop(true);
}

void SoundManager::Mute() {
  {
    lab::ContextRenderLock r(_context.get(), "SoundManager");
    _previousVolume = _gain->gain()->value(r);
  }

  _gain->gain()->setValue(0.0f);
  _muted = true;
}
